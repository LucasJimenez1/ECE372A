// Author: Group 5, Matthew Minear, Lucas Jimenez, & Aiden Tsingine      

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPD0(){
  
  //pull up resistor is enabled with DDR to logic 0 and PORT to logic 1
  DDRD &= ~(1 << DDD0); //logic 0 
  PIND |= (1 << PORTD0); // pull up resistor

    //enable interrupt with a 3 bit register:
    EICRA |= (1 << ISC00); // enable pin change interrupt 
    EIMSK |= (1 << INT0); 
}