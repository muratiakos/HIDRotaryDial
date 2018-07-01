/* Skeleton for HID */
#include "USBKeyboard.h"

// Wired pins
// GND - ROTARY - White
const int debugPin =  2; //For serial debugging mode
const int dialerPin =  3; // ROTARY - GREEN
const int counterPin =  4; // ROTARY - BROWN
const int handlePin =  5; // HANDLE - YELLOW

const int ledPin =  13;

byte isDebug = 0;
byte window = 0;
byte counter = 0;
byte last_counter_bit = 0;
byte last_dialer_bit = 0;
byte last_handle_bit = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(debugPin, INPUT_PULLUP);
  pinMode(dialerPin, INPUT_PULLUP);
  pinMode(counterPin, INPUT_PULLUP);
  pinMode(handlePin, INPUT_PULLUP);
  
  Keyboard.init();
}

void log(char* text) {
  if (isDebug) Serial.print(text);
}

void log(int num) {
  if (isDebug) Serial.print(num);
}

void sendNumber(byte tick) {
  log("Sending: ");
  if (tick > 0) {
    byte number = tick%10;
    log(number);

    log(" = Keystroke Code: ");
    byte keystroke = KEY_0;
    if (number > 0) keystroke = KEY_Z + number;
    log(keystroke);
    
    if (!isDebug) Keyboard.sendKeyStroke(keystroke);
  } else {
    log("Nothing");
  }
  log("\n");
}

void sendHandleOff() {
  log("Handle: lifted\n");
  if (!isDebug) Keyboard.sendKeyStroke(KEY_SPACE);
}

void sendHandleOn() {
  log("Handle: put back\n");
  if (!isDebug) Keyboard.sendKeyStroke(KEY_ENTER);
}

void loop() {
  delay(10);

  // Read controls
  isDebug = 1 - digitalRead(debugPin);
  byte isDialing = 1 - digitalRead(dialerPin);
  byte isCounting = digitalRead(counterPin);
  byte isHandleOff = digitalRead(handlePin);

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
  
  // Only show 
  if (isDialing) {
    log(window);
    log("\t");
    log(isDebug);
    log("\t");
    log(isDialing);
    log(" ");
    log(last_dialer_bit);
    log("\t");
    log(isCounting);
    log(" ");
    log(last_counter_bit);
    log("\t");
    log(counter);
    log("\t");
    log(isHandleOff);
    log("\n");
  }
  
  //uint8_t ledStatus;
  //ledStatus = Keyboard.readLedStatus();
  // if (ledStatus & LED_CAPSLOCK) {
  //   digitalWrite(ledPin, HIGH);      
  // } else {
  //   digitalWrite(ledPin, LOW);
  // }

  // Capture the last state
  window++;
  last_handle_bit = isHandleOff;
  last_dialer_bit = isDialing;
  last_counter_bit = isCounting;
}
