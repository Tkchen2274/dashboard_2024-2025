#include <FlexCAN.h>

// Define the CAN bus settings
FlexCAN CANbus(500000);  // CAN bus speed: 500 kbps

int i = 0;
int speed[5] = {1, 2, 3, 4, 5};
int bat[5] = {100, 99, 98, 97 ,96};
int temp[5] = {37, 38, 39, 40, 41};

void setup() {
  // Start serial communication with Nextion display
  //Serial.begin(9600);
  Serial2.begin(9600);    // RXTX

  // Can communication
  Serial.begin(115200);   // CAN communication
  while (!Serial); // Wait for Serial monitor to open
  Serial.println("Starting CAN Bus...");

  // Start the CAN bus
  CANbus.begin();
  Serial.println("CAN Bus initialized.");
}

void loop() {
  i++;
  if (i == 5) {
    i = 0;
  }

  // Send the number to a text component (e.g., "t0" on the Nextion)
  sendNumberToNextion("t0", 666);
  sendNumberToNextion("numbattery", bat[i]);
  sendNumberToNextion("numspeed", speed[i]);
  sendNumberToNextion("numtemp", temp[i]);
  sendNumberToNextion("t4", ctof(temp[i]));

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

  // Delay for a second
  //delay(1000);  delay used for dashboard refresh
}

float ctof (int c) {
  return c*1.8 + 32;
}

// Function to send a number to a Nextion component
void sendNumberToNextion(String component, float value) {
  // Send the command to update the text component with the value
  Serial.println(value);     // Component name, e.g., "t0"

  Serial2.print(component);     // Component name, e.g., "t0"
  Serial2.print(".txt=\"");     // For a text field
  Serial2.print(value);         // Value to display
  Serial2.print("\"");          // End the string value

  sendEndCommand();
}

void sendResponse(CAN_message_t rxMsg, bool buzz) {
  CANbus.write(rxMsg);
  if (buzz) {
    int buzzer = 0x903; // or another number, unique for use
    CANbus.write(buzzer); // some code to make buzz
    Serial.write(Buzzed); // Validation passed
  }
}

// Function to send the end command required by Nextion
void sendEndCommand() {
  Serial.write(0xFF);  // End of command character (0xFF) sent three times
  Serial.write(0xFF);
  Serial.write(0xFF);

  Serial2.write(0xFF);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
}