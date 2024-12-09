#include <avr/io.h>
#include "switch.h"
#include <avr/interrupt.h>

void initSwitchPB3(){
/*  
1. A function implementation that returns void and has no parameters
called initSwitchPB3 must be present and is used to initialize the switch on the pin named *PB3*.
2. PB3 must be initialized with an input pull-up
3. Pin-Change Interrupts must be enabled for pin in the main function resistor PB3
*/

    DDRB &= ~(1 << PB3); // Switch attached to physical pin 50 and labled as input
    PINB |= (1 << PORTB3); // enables pull-up reistor for physical pin 50 

    //Pin-Change Interrupts must be enabled for pin in the main function
    PCICR |= (1 << PCIE0); //enable PCINT 0 - 7
    PCMSK0 |= (1 << PCINT3); //enable PCINT3



}


