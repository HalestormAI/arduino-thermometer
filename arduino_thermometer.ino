// https://playground.arduino.cc/Code/Timer/
#include <Timer/Timer.h>
#include <thermistor/thermistor.h>

Timer t;

int first_digit = 0;
int second_digit = 0;
int third_digit = 0;
int fourth_digit = 0;

int8_t timer_event = 0;

uint8_t pinThermistor = A0;
uint8_t pinClock = 6;
uint8_t pinLatch = 5;
uint8_t pinData = 4;

int digits[4] ;
uint8_t CAS[4] = {12, 11, 10, 9};

//byte combinations for each number 0-9
byte numbers[10] {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110};

Thermistor thermistor = Thermistor(pinThermistor);

uint8_t decimalIndex = 1;
uint8_t count = 0;

void turnOff() { //turn off all 4 digits
    for (unsigned int i=0; i < 4; ++i) {
        digitalWrite(CAS[i], HIGH);
    }
}

void break_number(float temp, long scaleFactor) {

    // Expecting to get a number between 10 and 99. Multiply by 100 to give between 1000 and 9999
    int num = int(temp * scaleFactor);
    // then convert to int

    first_digit = num / 1000;
    digits[0] = first_digit;

    int first_left = num - (first_digit * 1000);
    second_digit = first_left / 100;
    digits[1] = second_digit;
    int second_left = first_left - (second_digit * 100);
    third_digit = second_left / 10;
    digits[2] = third_digit;
    fourth_digit = second_left - (third_digit * 10);
    digits[3] = fourth_digit;
}

void display_number() { //scanning

    turnOff(); //black screen
    digitalWrite(pinLatch, LOW); //put the shift register to read
    byte output = numbers[digits[count]];

    // Add in the decimal place
    if (count == decimalIndex) {
        output += 1;
    }
    shiftOut(pinData, pinClock, LSBFIRST, output); //send the data
    digitalWrite(CAS[count], LOW); //turn on the relevent digit
    digitalWrite(pinLatch, HIGH); //put the shift register to write mode
    count++; //count up the digit
    if (count == 4) { // keep the count between 0-3
        count = 0;
    }
}


void setup() {
    Serial.begin(9600); //serial start and pin config

    for (unsigned int i=0; i < 4; ++i) {
        pinMode(CAS[i], OUTPUT);
    }

    pinMode(pinClock, OUTPUT);
    pinMode(pinLatch, OUTPUT);
    pinMode(pinData, OUTPUT);

    turnOff();
}

int show = 0;
unsigned long measurement_timestamp = millis( );
void loop() {
    t.update(); //timer update

    if (show == 0) {
        t.stop(timer_event); //stop timer if anythign to read
        turnOff();
        float temp = thermistor.read();
        Serial.println( temp, 1 );
        break_number(temp, 100);
        timer_event = t.every(1, display_number); // start timer again
        show = 1;
    }

    /* Measure once every four seconds. */
    if(millis( ) - measurement_timestamp > 1000ul)
    {
        measurement_timestamp = millis();
        show = 0;
    }
}
