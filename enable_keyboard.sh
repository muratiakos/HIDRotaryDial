#!/bin/sh

echo "Please reset the device and then press [ENTER]"
read
ll /dev/tty.*

echo "Erasing.."
dfu-programmer atmega16u2 erase

echo "Flasing USB HID for keyboard"
#dfu-programmer atmega16u2 flash --debug 1 ./firmware/Arduino-usbserial-uno.hex
dfu-programmer atmega16u2 flash --debug 1 ./firmware/Arduino-keyboard-0.3.hex

echo "Resetting.."
dfu-programmer atmega16u2 reset

