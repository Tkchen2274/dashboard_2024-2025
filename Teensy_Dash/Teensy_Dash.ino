// set this to the hardware serial port you wish to use
#define HWSERIAL Serial2
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
CAN_message_t msg;
CAN_message_t msg2;
char c;
int x = 0;
int y = 0;

void setup() {
  Serial.begin(9600);
  HWSERIAL.begin(9600);
  can1.begin();
  can1.setBaudRate(500000);
  can2.begin();
  can2.setBaudRate(500000);
  Serial.print("hi");
}

void loop() {

  // can1.write(msg);
  if(can1.read(msg)){
    Serial.print("CAN1 ");
    Serial.print("MB: "); Serial.print(msg.mb);
    Serial.print("  ID: 0x"); Serial.print(msg.id, HEX );
    Serial.print("  EXT: "); Serial.print(msg.flags.extended );
    Serial.print("  LEN: "); Serial.print(msg.len);
    Serial.print(" DATA: ");
    for ( uint8_t i = 0; i < 8; i++ ) {
      Serial.print(msg.buf[i]); Serial.print(" ");
    }
    Serial.print("  TS: "); Serial.println(msg.timestamp);
    HWSERIAL.print("numbattery.txt=\"" + String(msg.buf[0]) + "\""); //changes the speedometer 
    HWSERIAL.write("\xFF\xFF\xFF");
  }else{
    // Serial.print("no work can 1 \n");
  }
  if ( can2.read(msg2) ) {
    Serial.print("CAN2 ");
    Serial.print("MB: "); Serial.print(msg2.mb);
    Serial.print("  ID: 0x"); Serial.print(msg2.id, HEX );
    Serial.print("  EXT: "); Serial.print(msg2.flags.extended );
    Serial.print("  LEN: "); Serial.print(msg2.len);
    Serial.print(" DATA: ");
    for ( uint8_t i = 0; i < 8; i++ ) {
      Serial.print(msg2.buf[i]); Serial.print(" ");
    }
    Serial.print("  TS: "); Serial.println(msg2.timestamp);
    HWSERIAL.print("numspeed.txt=\"" + String(msg2.buf[0]) + "\""); //changes the speedometer 
    HWSERIAL.write("\xFF\xFF\xFF");
  }else{
    // Serial.print("no work can 2");
  }
}