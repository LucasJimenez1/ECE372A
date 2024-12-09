#include <avr/io.h>
#include <Arduino.h>
#include "timer.h"

void initTimer1() {
    //CTC mode for timer 1
    TCCR1A &= ~(1 << WGM10); //Sets WGM10 bit to 0
    TCCR1A &= ~(1 << WGM11); //Sets WGM11 bit to 0
    TCCR1B |= (1 << WGM12);//Sets WGM12 bit to 1
    TCCR1B &= ~(1 << WGM13); // WGM13 - 0

}

void delayMs(unsigned int delay){
//clockFrequency = 16000000; //16MHZ

//turn on timer1 and enable prescalar of 64
TCCR1B |=(1 << CS10);
TCCR1B |=(1 << CS11);
TCCR1B &= ~(1 << CS12);

//delayCount = ((delay / 1000) * (16000000 / prescalar) - 1);
unsigned int delayCount = 0;

OCR1A=249; // (delay (1ms) * 16MHZ) / Prescalar (64)
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