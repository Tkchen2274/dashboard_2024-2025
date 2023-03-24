#ifndef __IMXRT1062__
  #error "This sketch should be compiled for Teensy 4.x"
#endif

//-----------------------------------------------------------------

#include <ACAN_T4.h>
#include <USBHost_t36.h>

//-----------------------------------------------------------------

// initialization of output pins
// USBHost myusb;
// greenPin = 10;
// redPin = 3; 

IntervalTimer myTimer;
int greenPin =  2;
int redPin = 3;
int speakerPin = 12;
int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables

void setup () {
  pinMode (greenPin, OUTPUT) ;
  Serial.begin (9600) ;
  // testing 
  // myTimer.begin(blinkLED, 150000);  // blinkLED to run every 0.15 seconds
  
  while (!Serial) {
    delay (50) ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;

  // pin
  // pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  
  }
  Serial.println ("CAN1 loopback test") ;
  ACAN_T4_Settings settings (125 * 1000) ; // 125 kbit/s
  settings.mLoopBackMode = false ;
  settings.mSelfReceptionMode = false ;
  const uint32_t errorCode = ACAN_T4::can1.begin (settings) ;
  const uint32_t errorCode2 = ACAN_T4::can2.begin (settings) ;
  Serial.print ("Bitrate prescaler: ") ;
  Serial.println (settings.mBitRatePrescaler) ;
  Serial.print ("Propagation Segment: ") ;
  Serial.println (settings.mPropagationSegment) ;
  Serial.print ("Phase segment 1: ") ;
  Serial.println (settings.mPhaseSegment1) ;
  Serial.print ("Phase segment 2: ") ;
  Serial.println (settings.mPhaseSegment2) ;
  Serial.print ("RJW: ") ;
  Serial.println (settings.mRJW) ;
  Serial.print ("Triple Sampling: ") ;
  Serial.println (settings.mTripleSampling ? "yes" : "no") ;
  Serial.print ("Actual bitrate: ") ;
  Serial.print (settings.actualBitRate ()) ;
  Serial.println (" bit/s") ;
  Serial.print ("Exact bitrate ? ") ;
  Serial.println (settings.exactBitRate () ? "yes" : "no") ;
  Serial.print ("Distance from wished bitrate: ") ;
  Serial.print (settings.ppmFromWishedBitRate ()) ;
  Serial.println (" ppm") ;
  Serial.print ("Sample point: ") ;
  Serial.print (settings.samplePointFromBitStart ()) ;
  Serial.println ("%") ;
  if (0 == errorCode && 0 == errorCode2) {
    Serial.println ("can1, can2 ok") ;
  }else{
    Serial.print ("Error can1: 0x") ;
    Serial.println (errorCode, HEX) ;
    while (1) {
      delay (100) ;
      Serial.println ("Invalid setting") ;
      digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    }
  }
}

void blinkLED() {
  if (ledState == LOW) {
    ledState = HIGH;
    blinkCount = blinkCount + 1;  // increase when LED turns on
  } else {
    ledState = LOW;
  }
  digitalWrite(greenPin, ledState);
}
//-----------------------------------------------------------------

static uint32_t gBlinkDate = 0 ;
static uint32_t gSendDate = 0 ;
static uint32_t gSentCount = 0 ;
static uint32_t gReceivedCount = 0 ;

//-----------------------------------------------------------------
/*
 * Tests the communication of the CAN lines on the Teensy4.1
 * Bus1 will send messages while Bus2 will receive messages
 * If the bus line is correctly set up, the terminal will display
 * incrementing values for the gSend and gReceived counts.
 * The code is pretty self explanatory, but there are added 
 * comments to guide understanding
 */

int counter = 0;
bool yay = true;
bool startCount = false;
void loop () {

  
//  if(yay){
//    myTimer.begin(blinkLED, 150000);  // blinkLED to run every 0.15 seconds
//    startCount = true;
//    yay = false;
//  }
//  if(startCount = true){
//    counter++
//    if(counter == 100000){
//      
//    }
//  }
  // digitalWrite(2,HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(redPin, HIGH);
  digitalWrite(speakerPin, HIGH);

  
  if (gBlinkDate <= millis ()) {
    gBlinkDate += 500 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }

  
  // Initialize CAN message
  // The settings of the message are declared above
  // the loop()
  CANMessage message ;

  
  if (gSendDate <= millis ()) {
    
    // Declared message ID
    message.id = 0x542 ;
    
    // Attempts to send on bus 1
    const bool ok = ACAN_T4::can1.tryToSend (message) ;
    
    if (ok) {
      gSendDate += 2000 ;
      gSentCount += 1 ;
      
      // print to the terminal
      Serial.print ("Sent: ") ;
      Serial.println (gSentCount) ;
    }
  }
  // Attemtps to read on bus 2
  if (ACAN_T4::can2.receive (message)) {
    
    // increment received count
    gReceivedCount += 1 ;
    
    // print to the terminal
    Serial.print ("Received: ") ;
    Serial.println (gReceivedCount) ;
 
  }

}
