// Author: Lucas Jimenez Miranda
// Net ID: lucasjimenez
// Date: 10.8.2024
// Assignment: Lab 3
//----------------------------------------------------------------------//

#include "timer.h"
//You many use any timer you wish for the microsecond delay and the millisecond delay


/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){ //0100 - CTC MODE
	TCCR1B &= ~(1 << WGM13); //0
    TCCR1B |= (1 << WGM12); //1
    TCCR1A &= ~(1 << WGM11); //0 
    TCCR1A &= ~(1 << WGM10); //0
}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
    //OCR1A = (1us * 16MHz) / (8)
    //OCR1A = 2 given a prescalar of 8 (lecture 7) ... OCR1AH = 0; OCR1AL = 2
    //also turns on timer 1
    TCCR1B &= ~(1 << CS12);
    TCCR1B |= (1 << CS11);
    TCCR1B &= ~(1 << CS10);

    OCR1A = 1;
    unsigned int count = 0;
    

    while (count < delay){
        TCNT1 = 0; //reset timer count

        // Wait for the compare match flag (OCF1A)
        while (!(TIFR1 & (1 << OCF1A)));

        //clear flag and increment timer
        TIFR1 |= (1 << OCF1A);
        count++;
        
    }

    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); //turns off timer.
}

/***************************************************************************************************************************/
/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
TCCR0A &=~(1 << WGM00); //0
TCCR0A |=(1 << WGM01); //1
TCCR0B &=~(1 << WGM02); //0
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
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