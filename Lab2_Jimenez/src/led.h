#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef led_h
#define led_h


void initLED();
void turnOnLEDWithChar(unsigned char num);



#endif