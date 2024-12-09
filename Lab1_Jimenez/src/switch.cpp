//#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include "switch.h"


/*
A function implementation that returns void and has no parameters called initSwitch must be present and is
used in the main function to initialize *pin 22* on the development board as an input
*/

void initSwitch() {
    /*PA0 refers to the physical *pin 22* on the board*/
    
    DDRA &= ~(1 << DDA0); // pin 22 as input
    PINA |= (1 << PORTA0); // enables pull-up reistor for pin 22 
}



//boolean function for status of button (1 = ON, 0 = OFF)
bool switchONOFF(){
   return !(PINA & (1 << PORTA0)); //returns 1 (true) if the button is pressed, if not it returns 0 (false)
}
