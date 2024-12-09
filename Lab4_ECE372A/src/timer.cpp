// Author: Group 5, Matthew Minear, Lucas Jimenez, & Aiden Tsingine      

#include <avr/io.h>
#include "timer.h"

void initTimer1() {
    //CTC mode for timer 1
    TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
    TCCR1B |= (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);
}

void delayS(unsigned int delay) {
    //1 second delay
    unsigned int count = 0;
    OCR1A = 15624; //prescalar of 1024
    TCCR1B |= (1 << CS10) | (1 << CS12);
    TCCR1B &= ~(1 << CS11);

while (count < delay) {
    TIFR1 |= (1 << OCF1A); //logic 1 is flag down
    TCNT1 = 0; //timer register is 0
    while(!(TIFR1 & (1 << OCF1A))); //!number is equivalent to number != 0
        //when while loop breaks, (0 & 1) = 0, which IS equal to 0.

        count++; //1 second delay as been achieved, go to second
}
 //turn timer off
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}

void initTimer0() {
    //CTC mode for timer 0
    TCCR0A &= ~(1 << WGM00); //Sets WGM00 bit to 0
    TCCR0A |= (1 << WGM01); //Sets WGM01 bit to 1
    TCCR0B &= ~(1 << WGM02);//Sets WGM02 bit to 0
}

void delayMs(unsigned int delay){
//clockFrequency = 16000000; //16MHZ

//turn on timer0 and enable prescalar of 64
TCCR0B |=(1 << CS00);
TCCR0B |=(1 << CS01);
TCCR0B &= ~(1 << CS02);

//delayCount = ((delay / 1000) * (16000000 / prescalar) - 1);
unsigned int delayCount = 0;

OCR0A=249; // (delay (1ms) * 16MHZ) / Prescalar (64)
TCNT0 = 0;

TIFR0 |= (1 << OCF0A); // set compare flag to start timer

while (delayCount < delay) {
if (TIFR0 & (1 << OCF0A)) { //increment only while flag is set
delayCount++;
TIFR0 |= (1 << OCF0A);
        }
    }


//turn off timer0
TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));
}