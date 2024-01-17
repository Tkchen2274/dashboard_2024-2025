// set this to the hardware serial port you wish to use
#define HWSERIAL Serial1
char c;
int x = 0;
int y = 100;
void setup() {
  Serial.begin(9600);
  HWSERIAL.begin(9600);
}

void loop() {
  c = HWSERIAL.read();
  Serial.print(c);
  int incomingByte;

  // y[,0,1,2,3]
  if (x == 0){ }
  else if(x == 1){ }
  else if(x == 2){ }
  else { }
  HWSERIAL.print("numspeed.txt=\"" + String(x) + "\"");
  HWSERIAL.write("\xFF\xFF\xFF");
  HWSERIAL.print("numbattery.txt=\"" + String(y) + "\"");
  HWSERIAL.write("\xFF\xFF\xFF");


  x++;
  y++;
  

//  if (Serial.available() > 0) {
//    incomingByte = Serial.read();
//    Serial.print("USB received: ");
//    Serial.println(incomingByte, DEC);
//    HWSERIAL.print("USB received:");
//    HWSERIAL.println(incomingByte, DEC);
//  }
  if (HWSERIAL.available() > 0) {
    incomingByte = HWSERIAL.read();
    Serial.print("UART received: ");
    Serial.println(incomingByte, HEX);
//    HWSERIAL.print("UART received:");
//    HWSERIAL.println(incomingByte, HEX);
    
    // trial
    //delay(100);
  }
}

//// set this to the hardware serial port you wish to use
//#define HWSERIAL Serial2
//
//void setup() {
//  Serial.begin(9600);
//  HWSERIAL.begin(9600);
//}
//
//void loop() {
//  int incomingByte;
//
//  if (Serial.available() > 0) {
//    incomingByte = Serial.read();
//    Serial.print("USB received: ");
//    Serial.println(incomingByte, DEC);
//    HWSERIAL.print("USB received:");
//    HWSERIAL.println(incomingByte, DEC);
//  }
//  if (HWSERIAL.available() > 0) {
//    incomingByte = HWSERIAL.read();
//    Serial.print("UART received: ");
//    Serial.println(incomingByte, DEC);
//    HWSERIAL.print("UART received:");
//    HWSERIAL.println(incomingByte, DEC);
//  }
//  HWSERIAL.write(0x65);
//  HWSERIAL.write(b);
//  HWSERIAL.write(0x00);
//  HWSERIAL.write(
//  
//}