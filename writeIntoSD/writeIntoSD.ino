#include <SPI.h>
#include <SD.h>
#include <TimeLib.h>

// Define the chip select pin for the Teensy 4.1's built-in SD card
const int chipSelect = BUILTIN_SDCARD;

// Pin to read analog input (e.g., A0)
// For this test case is A5
const int analogPin = A5;
float previousValue = 0.0;

void setup() {
  // Start serial communication for debugging (real-time monitoring)
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for Serial port to open (for Leonardo or Teensy)
  }

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("Card initialized.");

  // Initialize the RTC (if not set, set it manually)
  if (rtc_get() == 0) {
    Serial.println("RTC not set, setting to compile time");
    setTime(1664470800);  // Replace with actual Unix timestamp if needed
  }

  // Open the file to log data
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // If the file is available, write headers
  if (dataFile) {
    dataFile.println("TIME OF CURRENT, VALUE OF VOLTAGE, CHANGE OF VALUE");
    dataFile.close();  // Close the file when done
  } else {
    Serial.println("Error opening datalog.txt");
  }
}

void loop() {
  // Read the analog value (0 to 1023 for Teensy)
  int analogValue = analogRead(analogPin);
  
  // Convert the analog value to voltage (assuming 3.3V reference voltage)
  float voltage = analogValue * (3.3 / 1023.0);

  // Calculate the change in value compared to the last reading
  float change = voltage - previousValue;

  // Get the formatted time string
  String timeString = getTimeString();

  // Open the file to append the new log entry
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // If the file is available, log the data to SD card
  if (dataFile) {
    dataFile.print(timeString);                 // Time of current
    dataFile.print(", ");                       
    dataFile.print(voltage, 3);                 // Voltage value (formatted to 3 decimal places)
    dataFile.print(", ");
    dataFile.println(change, 3);                // Change in value (formatted to 3 decimal places)
    dataFile.close();                           // Close the file when done
  } else {
    Serial.println("Error opening datalog.txt");
  }

  // Print the same data to the Serial Monitor for real-time monitoring
  Serial.print(timeString);                 // Time of current
  Serial.print(", ");
  Serial.print(voltage, 3);                 // Voltage value (formatted to 3 decimal places)
  Serial.print(", ");
  Serial.println(change, 3);                // Change in value (formatted to 3 decimal places)

  // Update the previous value
  previousValue = voltage;

  // Wait for a second before the next reading
  delay(1000);
}

// Function to get formatted time string (HH:MM:SS on YYYY/MM/DD)
String getTimeString() {
  char timeBuffer[32];
  snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d on %04d/%02d/%02d", 
           hour(), minute(), second(), year(), month(), day());
  return String(timeBuffer);
}
