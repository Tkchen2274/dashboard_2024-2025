#include <SPI.h>
#include <mcp_can.h>

#define CAN_CS 10  // Chip Select pin for MCP2515

MCP_CAN CAN(CAN_CS);

float a = 0, b = 100, c = 1000, d = 10;

void setup() {
    Serial.begin(115200);
    // while (!Serial);

    // if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    //     Serial.println("CAN Module Initialized Successfully!");
    // } else {
    //     Serial.println("Error Initializing CAN Module!");
    //     while (1);
    // }

    CAN.setMode(MCP_NORMAL); // Set normal mode to start sending
}

void loop() {
    int randomNumber = random(1, 9);  // Generate random number from 1 to 8
    byte data[8] = { 1, 2, 3, 4, ++a, ++b, ++c, ++d };  // Prepare data

    Serial.print("Sent: ");
    for (int i = 0; i < 8; i++) {
      Serial.print(data[i]);
      Serial.print(" ");
    }

    if (CAN.sendMsgBuf(0x203, 0, 1, data) == CAN_OK) { // Send CAN message with ID 0x100
        Serial.println("Send Success!");
    } else {
        Serial.println("Error sending message!");
    }

    delay(10); // Send every 1 second
}
