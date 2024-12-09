// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB3(){
    DDRB &= ~(1 << PB3); // Switch attached to physical pin 50 and labled as input
    PINB |= (1 << PORTB3); // enables pull-up reistor for physical pin 50 

    //Pin-Change Interrupts must be enabled for pin in the main function
    PCICR |= (1 << PCIE0); //enable PCINT 0 - 7
    PCMSK0 |= (1 << PCINT3); //enable PCINT3

    EICRA |= (1 << ISC00); //enable PCINT 0 - 7
    EIMSK |= (1 << INT0); //enable PCINT3

    
}
