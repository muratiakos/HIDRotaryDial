/* Skeleton for HID */
#include "USBKeyboard.h"

// Wired pins - White - Ground
const int debugPin =  0; //For serial debugging mode
const int dialPin =  0; // Green-rotary 
const int counterPin =  0; //Brown-rotary

const int ledPin =  13;

void setup() {
  //pinMode(ledPin, OUTPUT);
  pinMode(debugPin, INPUT);
  Keyboard.init();
}

void loop() {
  delay(500);
  
  // Read controls
  int isDebug = 1 - digitalRead(debugPin);
  int isDialing = digitalRead(dialPin);
  int isCounting = digitalRead(counterPin);
  
  if (isDebug) {
    Serial.println("DEBUG=1");
  }
  
  //uint8_t ledStatus;
  //ledStatus = Keyboard.readLedStatus();

  // if (ledStatus & LED_CAPSLOCK) {
  //   digitalWrite(ledPin, HIGH);      
  // } else {
  //   digitalWrite(ledPin, LOW);
  // } 

  
  //Keyboard.print("Akos");
  //Keyboard.sendKeyStroke(KEY_ENTER);     // Send keystroke
}
