#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef timer_h
#define timer_h

void initTimer0();
void delayMs(unsigned int total_delay);


#endif