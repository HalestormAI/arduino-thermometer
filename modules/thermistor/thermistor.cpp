#include "Arduino.h"
#include "thermistor.h"


Thermistor::Thermistor(const uint8_t pinIn, float pullUpOhms)
        : _pin(pinIn), _pullUpOhms(pullUpOhms) {}

float Thermistor::read() {
    _v0 = analogRead(_pin);
    _resistance = _pullUpOhms * (1023.0 / (float) _v0 - 1.0);
    return _steninhart(_resistance);

}

float Thermistor::_steninhart(float resistance) const {
    float logResistance = log(resistance);
    float invT = A + B * logResistance + C * pow(logResistance, 3);
    return 1.0 / invT - KELVIN_TO_CELCIUS;
}