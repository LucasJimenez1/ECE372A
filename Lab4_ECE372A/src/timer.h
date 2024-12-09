// Author: Group 5, Matthew Minear, Lucas Jimenez, & Aiden Tsingine      

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer1();
void delayS(unsigned int delay);
void initTimer0();
void delayMs(unsigned int delay);

#endif