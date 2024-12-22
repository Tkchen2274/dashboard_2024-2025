#include <FlexCAN.h>

// Define the CAN bus settings
FlexCAN CANbus(500000);  // CAN bus speed: 500 kbps

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for Serial monitor to open
  Serial.println("Starting CAN Bus...");

  // Start the CAN bus
  CANbus.begin();
  Serial.println("CAN Bus initialized.");
}

void loop() {
  CAN_message_t rxMsg; // Message object to store received CAN data

  // Check if a new CAN message has been received
  if (CANbus.read(rxMsg)) {
    bool buzz = false;
    if (rxMsg[1] == 0x902) {
      buzz = true;
    }
    // sendResponse(rxMsg, rxMsg[1] == 0x902);
    sendResponse(rxMsg, buzz);
  }
}

// Function to send a response message
void sendResponse(CAN_message_t rxMsg, bool buzz) {
  CANbus.write(rxMsg);
  if (buzz) {
    int buzzer = 0x903; // or another number, unique for use
    CANbus.write(buzzer); // some code to make buzz
  }
}
