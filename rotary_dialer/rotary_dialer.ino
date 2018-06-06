/* Skeleton for HID */
#include "USBKeyboard.h"

const int ledPin =  13;


void setup() 
{
  pinMode(ledPin, OUTPUT);
  Keyboard.init();
}

void loop()
{
  uint8_t ledStatus;
  ledStatus = Keyboard.readLedStatus();

  if (ledStatus & LED_CAPSLOCK) {
    digitalWrite(ledPin, HIGH);      
  } else {
    digitalWrite(ledPin, LOW);
  } 

  delay(3000);
  Keyboard.print("Akos");
  Keyboard.sendKeyStroke(KEY_ENTER);     // Send keystroke
}
