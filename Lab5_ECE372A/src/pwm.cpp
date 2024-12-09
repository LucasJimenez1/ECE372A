
#include <avr/io.h>
#include <Arduino.h>
#include "pwm.h"

void initPWMTimer4(){
    //1. Set pin 8 as output
    DDRH |= (1 << DDH5);

    //2. Set Fast PWM (mode 15) to have TOP be a variable in order to change frequency
    //WGM43 = 1
    //WGM42 = 1
    //WGM41 = 1
    //WGM40 = 1
    TCCR4A |= (1 << WGM40) | (1 << WGM41);
    TCCR4B |= (1 << WGM42) | (1 << WGM43);

    //3. Set to clear OC4A on compare match and non-inverting mode
    TCCR4A |= (1 << COM4C1);
    TCCR4A &= ~(1 << COM4C0);

    //4. Set prescaler to 1 
    //CS42 = 0
    //CS41 = 0
    //CS40 = 1
    //TCCR4B &= ~((1 << CS42) | (1 << CS41));
    //TCCR4B |= (1 << CS40);
}



void changeFrequency(int frequency){
    OCR4AH = (16000000 / frequency) >> 8; //set high bits (9-16; hence right shift) of OCR4A
    OCR4AL = (16000000 / frequency); //set low bits (0-8) of OCR4A
    OCR4CH = OCR4AH >> 1; //half frequency (makes it louder?)
    OCR4CL = OCR4AL >>1; //half frequency
}


void alarmOn(){ //sets prescalar (turns on PWM)
    TCCR4B &= ~((1 << CS42) | (1 << CS41));
    TCCR4B |= (1 << CS40);
}

void alarmOff(){ //turns off prescalar (turns off pwm)
    TCCR4B &= ~((1 << CS42) | (1 << CS41) | (1 << CS40));

}

