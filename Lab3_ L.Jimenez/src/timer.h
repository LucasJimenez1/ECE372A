// Author: Lucas Jimenez Miranda
// Net ID: lucasjimenez
// Date: 10.8.2024
// Assignment:     Lab 3
//----------------------------------------------------------------------//

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer1();
void delayUs(unsigned int delay);
void initTimer0();
void delayMs(unsigned int delay); 

#endif
