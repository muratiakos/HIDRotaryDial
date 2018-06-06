/* Arduino USB Keyboard HID demo */
/* Send and 'a' to computer through USB every 3 seconds */
#include "USBKeyboard.h"

void setup() 
{
  Keyboard.init();
}

void loop() 
{
  delay(3000);
  Keyboard.sendKeyStroke(KEY_A);     // Send keystroke
  Keyboard.sendKeyStroke(KEY_K);     // Send keystroke
  Keyboard.sendKeyStroke(KEY_O);     // Send keystroke
  Keyboard.sendKeyStroke(KEY_S);     // Send keystroke
}
