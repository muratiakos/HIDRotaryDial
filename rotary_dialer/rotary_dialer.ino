/* Skeleton for HID */
#include "USBKeyboard.h"

// Wired pins
// GND - ROTARY - White
const int debugPin =  2; //For serial debugging mode
const int dialerPin =  3; // ROTARY - GREEN
const int counterPin =  4; // ROTARY - BROWN
const int handlePin =  5; // HANDLE - YELLOW

const int ledPin =  13;

byte window = 0;
byte counter = 0;
byte last_counter_bit = 0;
byte last_dialer_bit = 0;
byte last_handle_bit = 0;

void setup() {
  window = 0;
  counter = 0;
  last_counter_bit = 0;
  last_dialer_bit = 0;
  last_handle_bit = 0;
  
  pinMode(ledPin, OUTPUT);
  pinMode(debugPin, INPUT_PULLUP);
  pinMode(dialerPin, INPUT_PULLUP);
  pinMode(counterPin, INPUT_PULLUP);
  pinMode(handlePin, INPUT_PULLUP);
  
  Keyboard.init();
}

void sendNumber(byte number) {
  Serial.print("Sending: ");
  if (number > 0) {
    Serial.print(number%10);
  } else {
    Serial.print("Nothing");
  }
  Serial.print("\n");
}

void sendHandleOff() {
  Serial.print("Handle: lifted\n");
}

void sendHandleOn() {
  Serial.print("Handle: put back\n");
}

void loop() {
  delay(10);

  // Read controls
  int isDebug = 1 - digitalRead(debugPin);
  int isDialing = 1 - digitalRead(dialerPin);
  int isCounting = digitalRead(counterPin);
  int isHandleOff = digitalRead(handlePin);

  if (isHandleOff && last_handle_bit == 0) {
    // Handle reset
    sendHandleOff();
  }
  else if (!isHandleOff && last_handle_bit) {
    // Handle reset
    sendHandleOn();
  }
  else if (!isDialing && last_dialer_bit) {
    // Count the dials for the edges
    sendNumber(counter);
  }
  // Reset counter
  else if (!isDialing) {
    counter = 0;
  }
  else if (isDialing && isCounting && (1-last_counter_bit)) {
    counter++;
  } 
  
  // Get debug info
  if (isDebug) {
    // Only show 
    if (isDialing) {
      Serial.print(window);
      Serial.print("\t");
      Serial.print(isDebug);
      Serial.print("\t");
      Serial.print(isDialing);
      Serial.print(" ");
      Serial.print(last_dialer_bit);
      Serial.print("\t");
      Serial.print(isCounting);
      Serial.print(" ");
      Serial.print(last_counter_bit);
      Serial.print("\t");
      Serial.print(counter);
      Serial.print("\t");
      Serial.print(isHandleOff);
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
  window++;
  last_handle_bit = isHandleOff;
  last_dialer_bit = isDialing;
  last_counter_bit = isCounting;
}
