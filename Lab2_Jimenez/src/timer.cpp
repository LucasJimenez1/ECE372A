#include <avr/io.h>
#include <Arduino.h>
#include <avr/interrupt.h>
#include "led.h"
#include "switch.h"
#include "timer.h"



void initTimer0(){
TCCR0A &=~(1 << WGM00);
TCCR0A |=(1 << WGM01);
TCCR0B &=~(1 << WGM02);

/* // sET THE BITS FOR THE prescaller
TCCR0B |=(1 << CS00);
TCCR0B |=(1 << CS01);
TCCR0B &= ~(1 << CS02);
*/
// CTC compare value
OCR0A=249;
TCNT0 = 0; //starting the timer at 0

}

void delayMs(unsigned int delay){

/*unsigned int delayCnt = 0;
TCNT0 = 0; //starting the timer at 0
TIFR0 |= (1 << OCF0A); // set compare flag to start timer

while (delayCnt < delay) {
if (TIFR0 & (1 << OCF0A)) { //increment only while flag is set, 
delayCnt += 5;
TIFR0 |= (1 << OCF0A);
//re-start timer. will go to 0 before reaching the if statement above
}
}*/


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
TCCR0B &=~(1 << CS00);
TCCR0B &=~(1 << CS01);
TCCR0B |= (1 << CS02);

}



