//
// Created by Ian Hales on 21/03/2020.
//
#include "Arduino.h"
#include "display.h"

Display::Display(int decimalIndex, DisplayPins &pins)
    : _decimalIndex(decimalIndex), _pins(pins), _digitId(0){

}

void Display::initPinModes() {
    for (uint8_t cathode : _pins.cathodes) {
        pinMode(cathode, OUTPUT);
    }
    pinMode(_pins.clock, OUTPUT);
    pinMode(_pins.latch, OUTPUT);
    pinMode(_pins.data, OUTPUT);
}

void Display::turnOff() {
    for (uint8_t cathode : _pins.cathodes) {
        digitalWrite(cathode, HIGH);
    }
}

void Display::numToFourDigits(float number) {
    int scaleFactor = int(pow(10, _decimalIndex+1));
    // Expecting to get a number between 10 and 99. Multiply by 100 to give between 1000 and 9999
    int num = int(number * scaleFactor);
    // then convert to int

    _digitBuffer = num / 1000;
    _splitDigits[0] = _digitBuffer;

    int first_left = num - (_digitBuffer * 1000);
    _digitBuffer = first_left / 100;
    _splitDigits[1] = _digitBuffer;
    int second_left = first_left - (_digitBuffer * 100);
    _digitBuffer = second_left / 10;
    _splitDigits[2] = _digitBuffer;
    _digitBuffer = second_left - (_digitBuffer * 10);
    _splitDigits[3] = _digitBuffer;

}

void Display::outputNext() { //scanning
    turnOff(); //black screen
    digitalWrite(_pins.latch, LOW); //put the shift register to read
    byte output = numbers[_splitDigits[_digitId]];

    // Add in the decimal place, by setting the LSB to 1 (i.e. adding 1 to the digit value)
    if (_digitId == _decimalIndex) {
        output += 1;
    }
    shiftOut(_pins.data, _pins.clock, LSBFIRST, output); //send the data
    digitalWrite(_pins.cathodes[_digitId], LOW); //turn on the relevent digit
    digitalWrite(_pins.latch, HIGH); //put the shift register to write mode
    _digitId = (_digitId + 1) % DISPLAY_WIDTH; //count up the digit
}