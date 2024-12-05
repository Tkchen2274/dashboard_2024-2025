// #include <FlexCAN.h>
#include <FlexCAN.h>
/*
  12/02/24 Need to handle receive messages from can to update the dashboard

*/

// Define the CAN bus settings
FlexCAN CANbus(500000);  // CAN bus speed: 500 kbps

int i = 0;
int speed[5] = {1, 2, 3, 4, 5};
int bat[5] = {100, 99, 98, 97 ,96};
int temp[5] = {37, 38, 39, 40, 41};
int state;

// convention for CAN messages: source_dest_label
CAN_message_t dash_vcu_buzzPlayed;

// used to recieve the temp value
// you might need to change this in a fat 
// if loop to sift through the messages
CAN_message_t vcu_dash_playBuzz; 

void setup() {
  // Start serial communication with Nextion display
  // Serial.begin(9600);
  Serial2.begin(9600);    // RXTX

  // Can communication
  Serial.begin(115200);   // CAN communication
  while (!Serial); // Wait for Serial monitor to open
  Serial.println("Starting CAN Bus...");

  // Start the CAN bus
  CANbus.begin();
  Serial.println("CAN Bus initialized.");

  dash_vcu_buzzPlayed.id = 0x110;
  dash_vcu_buzzPlayed.buf[0] = 0x1;
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


  /* 
    Check if received the buzzer message from VCU 
    if so, then forward the state and call fxn:
    'sendResponse(blah,blah)'
  */
  if (CANbus.read(vcu_dash_playBuzz)) {
    if (vcu_dash_playBuzz.id == 0x109 && vcu_dash_playBuzz.buf[0] == 0x1) {
      state = vcu_dash_playBuzz.buf[1];  
      buzz_played_response(state);
    }
  }

  // Delay for a second
  // delay(1000);  delay used for dashboard refresh
}

/*
  ctof(): 
    celcius to farenheit 
  Args: 
    c (int): celcius input 
  Returns:
    float: gives back the farenheit value
*/

float ctof (int c) {
  return c*1.8 + 32;
}

/* 
  sendNumberToNextion(): 
    Function to send a number to a Nextion component

  Args: 
    component (String): first parameter
      specify which component you are sending to  
    value     (float) : second parameter
      value to show on display
  Returns:
    void 
*/

void sendNumberToNextion(String component, float value) {
  // Send the command to update the text component with the value
  Serial.println(value);        // Component name, e.g., "t0"
  Serial2.print(component);     // Component name, e.g., "t0"
  Serial2.print(".txt=\"");     // For a text field
  Serial2.print(value);         // Value to display
  Serial2.print("\"");          // End the string value

  sendEndCommand();
}

/* 
  buzz_played_response(): 
    Sends a message to the VCU that the buzzer has been played 

  Args: 
    state (int): first parameter
      takes the state of the recieved message and sends it back
  Returns:
    void 
*/

void buzz_played_response(int state) {
  dash_vcu_buzzPlayed.buf[1] = state;
  CANbus.write(dash_vcu_buzzPlayed); // some code to make buzz
  Serial.write("sent buzz message validation"); // Validation passed
  }

/* 
  sendEndCommand(): 
    Function to send the end command required by Nextion Protocol

  Args: 
    empty

  Returns:
    void 
*/

void sendEndCommand() {
  Serial.write(0xFF);  // End of command character (0xFF) sent three times
  Serial.write(0xFF);
  Serial.write(0xFF);

  Serial2.write(0xFF);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
}
