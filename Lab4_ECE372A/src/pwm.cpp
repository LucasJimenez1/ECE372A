#include <avr/io.h>
#include <Arduino.h>
#include "pwm.h"

void initPWMTimer4(){
    //1. Set pin 6 as output
    DDRH |= (1 << DDH3);

    //2. Set Fast PWM (mode 15) to have TOP be a variable in order to change frequency
    //WGM43 = 1
    //WGM42 = 1
    //WGM41 = 1
    //WGM40 = 1
    TCCR4A |= (1 << WGM40) | (1 << WGM41);
    TCCR4B |= (1 << WGM42) | (1 << WGM43);

    //3. Set to clear OC4A on compare match and non-inverting mode
    TCCR4A |= (1 << COM4A1);
    TCCR4A &= ~(1 << COM4A0);

    //4. Set prescaler to 1 
    //CS42 = 0
    //CS41 = 0
    //CS40 = 1
    TCCR4B &= ~((1 << CS42) | (1 << CS41));
    TCCR4B |= (1 << CS40);

    //Because we're changing the frequency, we don't need to the set duty cycle as that'll be done in the changeFrequency() function
}

void changeFrequency(unsigned int frequency){
    OCR4A = 16000000 / frequency;
    OCR4AH = OCR4A >> 8;
    OCR4AL = OCR4A;
    OCR4AH = OCR4AH >> 1;
    OCR4AL = OCR4AL >> 1;
}

void turnOffBuzzer(){
    DDRH &= ~(1 << DDH3); //Disable pin 6
}