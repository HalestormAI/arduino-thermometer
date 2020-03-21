#ifndef ARDUINO_THERMOMETER_DISPLAY_H
#define ARDUINO_THERMOMETER_DISPLAY_H
#define byte uint8_t

#include <avr/io.h>
#include <binary.h>

#define DISPLAY_WIDTH 4u

// 0 - 9 based on bits for specific pinouts.
// Decimal place is LSB (see numToFourDigits)
const byte numbers[10] {
    B11111100,
    B01100000,
    B11011010,
    B11110010,
    B01100110,
    B10110110,
    B10111110,
    B11100000,
    B11111110,
    B11110110
};

struct DisplayPins {
    const uint8_t latch;
    const uint8_t clock;
    const uint8_t data;
    const uint8_t (&cathodes)[DISPLAY_WIDTH];
};


class Display {
public:
    Display(int decimalIndex, DisplayPins &pins);

    void outputNext();
    void initPinModes();
    void turnOff();

    void numToFourDigits(float num);

private:
    const DisplayPins &_pins;

    int _splitDigits[DISPLAY_WIDTH];

    int _decimalIndex;
    int _digitId;

    int _digitBuffer;
};


#endif //ARDUINO_THERMOMETER_DISPLAY_H
