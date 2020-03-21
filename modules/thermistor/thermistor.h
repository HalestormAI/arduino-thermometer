//
// Created by Ian Hales on 21/03/2020.
//

#ifndef ARDUINO_THERMOMETER_THERMISTOR_H
#define ARDUINO_THERMOMETER_THERMISTOR_H


#include <avr/io.h>

#define KELVIN_TO_CELCIUS 273.15f

// Steinhart-Hart coefficients (Calculated according to datasheet) using
// https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
#define A 1.262545667e-03f
#define B 2.121841734e-04f
#define C 1.755783923e-07f

class Thermistor {
public:
    explicit Thermistor(uint8_t pinIn, float pullUpOhms = 10000);
    float read();

private:
    float _steninhart(float resistance) const;

    const uint8_t _pin;
    const float _pullUpOhms; // R1

    int32_t _v0;
    float _resistance;
};


#endif //ARDUINO_THERMOMETER_THERMISTOR_H
