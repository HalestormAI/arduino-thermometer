# A quick and dirty Arduino Thermometer

This was a quick experiment to see if the parts I had lying around would make
a usable thermometer.

The answer is... just about..

## Parts
 * Arduino Mega 2560 (any sensible arduino would do - I might port this to my Teensy 3.1 at some point)
 * 4-Digit, 7 Segment Display
 * 74HC595 Shift Register
 * MF52 Thermistor with integrated 10K pull-up resistor
 * 4x 220Ohm resistors

## Setup
For the 7-segment display, I largely followed the guide here, and started out with the code therein,
but modified it for my needs.

https://osoyoo.com/2017/08/08/arduino-lesson-4-digit-7-segment-led-display/

The thermistor is a simple addition, connect to the 5v and ground rails, then send the data line to A0.

## Code
I hope it's fairly self explanatory.

Works from manual testing, but it needs automated tests...