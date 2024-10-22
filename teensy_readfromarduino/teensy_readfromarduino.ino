

//-----------------------------------------------------------------

#include <ACAN_T4.h>

//-----------------------------------------------------------------

void setup () {
  pinMode (LED_BUILTIN, OUTPUT) ;
  Serial.begin (9600) ;
  while (!Serial) {
    delay (50) ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
  //Serial.println ("CAN1 loopback test") ;
  ACAN_T4_Settings settings (500 * 1000) ; // 125 kbit/s
  settings.mLoopBackMode = false ;
  settings.mSelfReceptionMode = true ;
  const uint32_t errorCode = ACAN_T4::can1.begin (settings) ;
  if (0 == errorCode) {
    Serial.println ("can1 ok") ;
  }else{
    Serial.print ("Error can1: 0x") ;
    Serial.println (errorCode, HEX) ;
  }
}

//-----------------------------------------------------------------

static uint32_t gBlinkDate = 0 ;
static uint32_t gSendDate = 0 ;
static uint32_t gSentCount = 0 ;
static uint32_t gReceivedCount = 0 ;
int datastore[10000][4]; // 0=speed, 1=temperature, 2=battery, 3=temperature or something else
// gReceivedCount would be maximum 9999 to avoid SEGFAULT

//-----------------------------------------------------------------

void loop () {
  if (gBlinkDate <= millis ()) {
    gBlinkDate += 500 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
  CANMessage message ;
  if (gSendDate <= millis ()) {
    message.id = 0x542 ;
    const bool ok = ACAN_T4::can1.tryToSend (message) ;
    if (ok) {
      //gSendDate += 2000 ;
      //gSentCount += 1 ;   only recieviing 

    }
  }
  if (ACAN_T4::can1.receive (message)) {
    
    // some soft of parsing
    datastore[gReceivedCount][0] = message.data[0];
    datastore[gReceivedCount][1] = message.data[1];
    datastore[gReceivedCount][2] = message.data[2];
    datastore[gReceivedCount][3] = message.data[3];
    Serial.print ("Received: ") ;
    Serial.println (gReceivedCount) ;
    for (int i = 0; i < 4; i++) {
      Serial.print(datastore[gReceivedCount][i]);
      Serial.print("  ");
    }
    Serial.println();
    gReceivedCount += 1 ;
  }
}