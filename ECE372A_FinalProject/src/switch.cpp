
  #include "switch.h"
  #include <avr/io.h>
  #include <avr/interrupt.h>

  /*
  * Initializes pull-up resistor on PD2 (physical pin 19) and sets it into input mode
  */
  void initSwitchPD2(){
    
    //pull up resistor is enabled with DDR to logic 0 and PORT to logic 1
    DDRD &= ~(1 << DDD2); //logic 0 
    PORTD |= (1 << PORTD2); // pull up resistor

  EIFR |= (1 << INTF2);
  EIMSK |= (1 << INT2);

  }