// Arduino Program (Sender)
char speed = 120;          // Example speed (0-255)
char tempC = 25;           // Example temperature in Celsius (0-255)
char battery = 80;         // Example battery percentage (0-255)
char tempF = 77;           // Example temperature in Fahrenheit (0-255)

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Create an 8-byte message
  char message[8];
  
  message[0] = speed;    // Speed
  message[1] = tempC;    // Temperature in Celsius
  message[2] = battery;  // Battery percentage
  message[3] = tempF;    // Temperature in Fahrenheit
  message[4] = 0;        // Unused byte
  message[5] = 0;        // Unused byte
  message[6] = 0;        // Unused byte
  message[7] = 0;        // Unused byte

  // Send the 8-byte message via Serial
  Serial.write((byte*)message, 8);
  Serial.println(); 

  delay(1000);  // Send data every second
}
