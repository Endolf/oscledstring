# OSC with FastLED
## Overview
This is a test for ESP32 controlling a string of LEDs using Open Sound Control. The ESP32 will create a WiFi Access Point.

## LEDs
The code as committed controls a string of 144 WS2813 LEDs. The LED count and type can be changed in `main.h`.

## Controls
There are 9 OSC controls implemeted. All OSC addresses for the commands are prefixed with a wildcard, so for testing any prefix will work.

### Solid Colours
There are 4 controls for displaying a solid colour. 1 that allows passing in an RGB `int` and 3 that allow a float defining in individual channel

`/OSCTest/solidColour` takes 1 32 bit unsigned integer parameter with an RGB colour code (so only 24 bits used), HTML colour codes can be passed in directly and the LED string will light with the passed in colour.

`/OSCTest/solidColourRed`, `/OSCTest/solidColourGreen` and `/OSCTest/solidColourBlue` take in a 32 bit float in the range of 0-1 that covers the percentage of that colour. The LED string will light with the combination of the last set colour and the new channel value.

### FastLED demos
Some of the FastLED demos have been imported and can be set with OSC

`/OSCTest/fire` runs the Fire2012 demo.

`/OSCTest/rainbow` runs the Rainbow pattern from Demo100

`/OSCTest/juggle` runs the Juggle pattern from Demo100

`/OSCTest/sinelon` runs the Sinelon pattern from Demo100

### Setting the brightness
The brightness can be overridden, it is reset with the pattern changes.

`/OSCTest/brightness` takes a 32 bit float in the range of 0-1 that sets the brightness percentage.

### WiFi
The ESP32 will create an access point with the name `OSCNet` and the password `oscnet1324`, these can be overridden in `main.cpp`.