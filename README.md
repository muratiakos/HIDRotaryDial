# Rotary dial - USB HID device
Rotary dialer controller for old pulse-based analog phones phones to
send strokes as a USB Keyboard as a HID device.

Based on
 - http://mitchtech.net/arduino-usb-hid-keyboard/
Using firmware and sources from:
 - https://github.com/coopermaa/USBKeyboard 

## Setup dfu-programmer
sudo port install dfu-programmer


## Flash firmware
```bash
# Switch to serial mode for coding
sudo ./program_keyboard.sh

# Enable USB keyboard mode
sudo ./enable_keyboard.sh
```

## Android dialer
Under the `app` folder.
