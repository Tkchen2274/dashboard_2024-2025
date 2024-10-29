#include <Nextion.h>

// Define Nextion's RX/TX pins
#define NEXTION_TX_PIN 1  // Teensy TX to Nextion RX
#define NEXTION_RX_PIN 0  // Teensy RX to Nextion TX

// Nextion display setup
NexText t0 = NexText(0, 1, "t0");  // Display text component for speed
NexText t1 = NexText(0, 2, "t1");  // Display text component for Temp C
NexText t2 = NexText(0, 3, "t2");  // Display text component for Battery

const int rows = 1000;  // Array size for message logging
const int cols = 8;     // 8 bytes per message
char dataLog[rows][cols];  // 2D array to store received data
int dataIndex = 0;        // Index for logging data

void setup() {
  // Initialize USB Serial for receiving data from the PC
  Serial.begin(115200);

  // Initialize hardware serial for Nextion (via RX/TX pins)
  Serial1.begin(9600);  // Default baud rate for Nextion

  // Initialize Nextion display communication
  nexInit();

  // Set initial messages on the Nextion display
  t0.setText("Speed: ");
  t1.setText("Temp C: ");
  t2.setText("Battery: ");
}

void loop() {
  // Check if data is available on the USB serial from the PC
  if (Serial.available() >= 8) {
    // Read the 8-byte message
    byte message[8];
    Serial.readBytes(message, 8);

    // Store the received message into the 2D array
    for (int i = 0; i < 8; i++) {
      dataLog[dataIndex][i] = message[i];
    }

    // Print received data to the Serial Monitor for debugging
    Serial.print("Received Data: ");
    for (int i = 0; i < 8; i++) {
      Serial.print(dataLog[dataIndex][i]);
      Serial.print(" ");
    }
    Serial.println();

    // Update Nextion display with received data
    char buffer[32];
    
    snprintf(buffer, sizeof(buffer), "Speed: %d", dataLog[dataIndex][0]);
    t0.setText(buffer);  // Update speed on Nextion
    
    Serial.println();

    snprintf(buffer, sizeof(buffer), "Temp C: %d", dataLog[dataIndex][1]);
    t1.setText(buffer);  // Update temperature in Celsius on Nextion
    
    Serial.println();

    snprintf(buffer, sizeof(buffer), "Battery: %d", dataLog[dataIndex][2]);
    t2.setText(buffer);  // Update battery percentage on Nextion

    Serial.println();

    // Increment the data log index (check for overflow)
    dataIndex++;
    if (dataIndex >= rows) {
      dataIndex = 0;  // Reset index to prevent overflow
    }

    delay(500);  // Delay to avoid overwhelming Nextion and Serial output
  }
}

