
#include <avr/io.h>
#include <Arduino.h>
#include "pwm.h"
#include "timer.h"

//BUZZER CONTROL
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

void alarmOff(){ //turns off prescalar (turns of pwm)
    TCCR4B &= ~((1 << CS42) | (1 << CS41) | (1 << CS40));

}

//SERVO CONTROL
void initPWMTimer3(){ //PE3 - pin 5 
    DDRE |= (1 << PE3); //set pe3 as output

    //Mode 14 ICR3 as TOP, allows us to control duty cycle (OCRnA) and period independently
    TCCR3A |= (1 << WGM31);
    TCCR3A &= ~(1 << WGM30);
    TCCR3B |= (1 << WGM32) | (1 << WGM33);


    // OCRnA non-inverting mode
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);

    //Prescalar = 8
    TCCR3B |= (1 << CS31);
    TCCR3B &= ~(1 << CS30);
    TCCR3B &= ~(1 << CS32);

    ICR3 = 40000; //Pulse-Width = (1.5ms / 20ms) * 40000

    //Set initial pulse width for neutral position (1.5ms)
    OCR3A = 3000; //Pulse-width = (1.5ms / 20ms) * 40000 = 3000
}

void servoLock(){ //turn servo 90 degrees to unlock box (90 degrees)
    OCR3A = 2000;
    delayMs(500); //allow time for the servo to move
}
void servoUnlock(){// turn servo 90 degrees back to lock box (0 degrees)
    OCR3A = 4000;
    delayMs(500); //allow time for the servo to move
}