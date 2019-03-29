#!/bin/bash

# arduino-cli is needed before to continue:
#
# Full instructions ..........: https://github.com/arduino/arduino-cli
# Direct download (Linux/64) .: https://downloads.arduino.cc/arduino-cli/arduino-cli-latest-linux64.tar.bz2
# Direct download (Linux/32) .: https://downloads.arduino.cc/arduino-cli/arduino-cli-latest-linux32.tar.bz2
# Direct download (Windows) ..: https://downloads.arduino.cc/arduino-cli/arduino-cli-latest-windows.zip
# 
# Cheatsheet:
# - arduino-cli core update-index
# - arduino-cli board list
# - arduino-cli core search esp
# - arduino-cli core install esp8266:esp8266
# - arduino-cli board listall (esp8266:esp8266:d1_mini is shown here)
# - arduino-cli compile --fqbn esp8266:esp8266:d1_mini sketch_name_here
# - arduino-cli upload -p /dev/ttyUSB0 --fqbn esp8266:esp8266:d1_mini sketch_name_here
# - arduino-cli lib search wifi101
# - arduino-cli lib install "WiFi101"
#

# $1 will be the sketch name
# $2 will be the serial port name

APP_PATH="$(dirname "$(readlink -f "$0")")"
APP_SCRIPT_NAME="$(basename "$(readlink -f "$0")")"

echo "APP_PATH .........: ${APP_PATH}"
echo "APP_SCRIPT_NAME ..: ${APP_SCRIPT_NAME}"

arduino-cli compile --verbose --warnings all --fqbn esp8266:esp8266:d1_mini "$1"
arduino-cli upload -p "$2" --fqbn esp8266:esp8266:d1_mini "$1"
