/* Skeleton for HID */
#include "USBKeyboard.h"

// Wired pins - White - Ground
const int debugPin =  2; //For serial debugging mode
const int dialerPin =  3; // Green-rotary 
const int counterPin =  4; //Brown-rotary

const int ledPin =  13;

byte counter;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(debugPin, INPUT);
  pinMode(dialerPin, INPUT);
  pinMode(counterPin, INPUT);

  Keyboard.init();
  counter = 0;
}

void loop() {
  delay(10);

  // Read controls
  int isDebug = digitalRead(debugPin);
  int isDialing = digitalRead(dialerPin);
  int isCounting = digitalRead(counterPin);
  
  if (1 || isDebug) {
    counter++;
    Serial.print(counter);
    Serial.print("\t");
    Serial.print(isDebug);
    Serial.print("\t");
    Serial.print(isDialing);
    Serial.print("\t");
    Serial.print(isCounting);
    Serial.print("\n");
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
