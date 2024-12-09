// Description: This file implements turnOnLED and initLED to control
// the LEDs.
//----------------------------------------------------------------------//


#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

/* Initialize PD0, PD1, PD2, and PD3 to outputs
*/
void initLED(){
    DDRD |= (1 << PD0); //physical pin 21
    DDRD |= (1 << PD1); //physical pin 20
    DDRD |= (1 << PD2); //physical pin 19
    DDRD |= (1 << PD3); //physical pin 18
 
}

/* This must be one line of code.
* In this function you will be giving a number "num" which will be represented
* in binary by four LEDs. You must effectively assign the lowest four bits of
* "num" to the appropriate bits of PORTD.
*/
void turnOnLEDWithChar(unsigned char num){
  PORTD = (PORTD & 0XF0) | (num & 0x0F); 
}
