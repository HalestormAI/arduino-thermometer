// https://playground.arduino.cc/Code/Timer/
#include <Timer/Timer.h>
#include <display/display.h>
#include <thermistor/thermistor.h>

Timer t;

int8_t timer_event = 0;

uint8_t pinThermistor = A0;
uint8_t pinClock = 6;
uint8_t pinLatch = 5;
uint8_t pinData = 4;
uint8_t cathodePins[DISPLAY_WIDTH] = {12, 11, 10, 9};

uint8_t decimalIndex = 1;

Thermistor thermistor = Thermistor(pinThermistor);

DisplayPins dp{
        pinLatch,
        pinClock,
        pinData,
        cathodePins
};

Display display = Display(decimalIndex, dp);

unsigned long measureInterval = 1000ul;
unsigned long measurementTimestamp = millis();

void setup() {
    Serial.begin(9600); //serial start and pin config
    display.initPinModes();
    display.turnOff();
}

void output() {
    display.outputNext();
}

void loop() {
    t.update();

    if (millis() - measurementTimestamp > measureInterval) {
        measurementTimestamp = millis();
        t.stop(timer_event);
        display.turnOff();
        float temp = thermistor.read();
        Serial.println(temp, 1);
        display.numToFourDigits(temp);
        timer_event = t.every(1, output);
    }
}
