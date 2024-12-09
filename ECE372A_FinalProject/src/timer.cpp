#include <avr/io.h>
#include <Arduino.h>
#include "timer.h"


void initTimer0(){ //mS timer from lab 2
TCCR0A &=~(1 << WGM00);
TCCR0A |=(1 << WGM01);
TCCR0B &=~(1 << WGM02);
}
void delayMs(unsigned int delay){
unsigned int delayCount = 0;
//int prescalar = 64; //prescalar 64 for a resolution at Frequency of 16 MHz 
//int clockFrequency = 16000000; //16MHZ
TCCR0B |=(1 << CS00);
TCCR0B |=(1 << CS01);
TCCR0B &= ~(1 << CS02);

//delayCount = ((delay / 1000) * (16000000 / prescalar) - 1);
OCR0A=249; // (delay (1ms) * 16MHZ) / Prescalar (64)
TCNT0 = 0;

TIFR0 |= (1 << OCF0A); // set compare flag to start timer

while (delayCount < delay) {
if (TIFR0 & (1 << OCF0A)) { //increment only while flag is set
delayCount++;
TIFR0 |= (1 << OCF0A);
        }
    }
//turn off timer
TCCR0B &=~(1 << CS00);
TCCR0B &=~(1 << CS01);
TCCR0B |= (1 << CS02);

}

void initTimer1() { //Us timer
    //CTC mode for timer 1
    TCCR1A &= ~(1 << WGM10); //Sets WGM10 bit to 0
    TCCR1A &= ~(1 << WGM11); //Sets WGM11 bit to 0
    TCCR1B |= (1 << WGM12);//Sets WGM12 bit to 1
    TCCR1B &= ~(1 << WGM13); // WGM13 - 0

    OCR1A = 2;
}
void delayUs(unsigned int delay){
//clockFrequency = 16000000; //16MHZ

//turn on timer1 and enable prescalar of 8
TCCR1B &= ~(1 << CS10); //0
TCCR1B |=(1 << CS11);   //1
TCCR1B &= ~(1 << CS12); //0

//delayCount = ((delay / 1000) * (16000000 / prescalar) - 1);
unsigned int delayCount = 0;

OCR1A= 2; // (delay (1us) * 16MHZ) / Prescalar (8)
TCNT1 = 0;

TIFR1 |= (1 << OCF1A); // set compare flag to start timer

while (delayCount < delay) {
if (TIFR1 & (1 << OCF1A)) { //increment only while flag is set
delayCount++;
TIFR1 |= (1 << OCF1A);
        }
    }


//turn off timer1
TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
}


