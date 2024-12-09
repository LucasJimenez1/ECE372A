#include <avr/io.h>
#include <util/delay.h>
#ifndef led_h
#define led_h


void initLED();

void turnOnLED(unsigned int LED);
void turnOffLED(unsigned int LED);

void runLED(unsigned int LED); //call in main.cpp loop ! 


#endif
