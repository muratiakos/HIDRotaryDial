#!/bin/sh

echo "Please reset the device and then press [ENTER]"
read
ll /dev/tty.*

echo "Erasing.."
dfu-programmer atmega16u2 erase

echo "Flasing USB Serial"
dfu-programmer atmega16u2 flash --debug 1 ./firmware/Arduino-usbserial-uno.hex

echo "Resetting.."
dfu-programmer atmega16u2 reset