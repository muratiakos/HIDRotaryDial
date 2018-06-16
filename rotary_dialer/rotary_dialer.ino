/* Skeleton for HID */
#include "USBKeyboard.h"

// Wired pins
// GND - ROTARY - White
const int debugPin =  2; //For serial debugging mode
const int dialerPin =  3; // ROTARY - GREEN
const int counterPin =  4; // ROTARY - BROWN

const int ledPin =  13;

byte window;
byte counter = 0;
byte last_counter_bit = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(debugPin, INPUT_PULLUP);
  pinMode(dialerPin, INPUT_PULLUP);
  pinMode(counterPin, INPUT_PULLUP);

  Keyboard.init();
  window = 0;
}

void loop() {
  delay(10);
  window++;

  // Read controls
  int isDebug = 1 - digitalRead(debugPin);
  int isDialing = 1 - digitalRead(dialerPin);
  int isCounting = digitalRead(counterPin);

  // Count the dials for the edges
  if (!isDialing) { // Reset counter
    counter = 0;
  }
  else if (isDialing && isCounting && (1-last_counter_bit)) {
    counter++;
  } 
  
  //Get debug info
  if (isDebug) {
    // Only show 
    if (isDialing) {
      Serial.print(window);
      Serial.print("\t");
      Serial.print(isDebug);
      Serial.print("\t");
      Serial.print(isDialing);
      Serial.print("\t");
      Serial.print(isCounting);
      Serial.print("\t");
      Serial.print(last_counter_bit);
      Serial.print("\t");
      Serial.print(counter);
      Serial.print("\n");
    }
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

  // Capture the last state
  last_counter_bit = isCounting;
}
