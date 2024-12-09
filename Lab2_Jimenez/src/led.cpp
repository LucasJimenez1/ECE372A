#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"


void initLED(){
/*A function implementation that returns void and has no parameters called initLED must be present 
and is used in the main function to initialize all LED pins as outputs*/

    //Pins named PA0, PA1, PA2, and PA3 must be used to control the LEDs
    DDRA |= (1 << PA0); //PA0 - LED on physical pin 22
    DDRA |= (1 << PA1); //PA1 - LED on physical pin 23
    DDRA |= (1 << PA2); //PA2 - LED on physical pin 24
    DDRA |= (1 << PA3); //PA3 - LED on physical pin 25
}

void turnOnLEDWithChar(unsigned char num){
/*A function implementation called turnOnLEDWithChar that returns void and has a parameter called 
num of type unsigned char must be present.*/

//The turnOnLEDWithChar function must be **one line of code.** See LED control section for more details.

/*# LED Control
The purpose of the function turnOnLEDWithChar is to practice a more advanced use of bit operations.
 We have covered how to manipulate a single bit at a time, however, there are times that are useful to 
manipulate several at a time.
Since the LEDs must be controled with PA0, PA1, PA2, and PA3, we can manipulate a single register and simulatenously 
manipulate several bits. The method to do this is to first "mask" these bits in a register by setting them to zero and 
then ORing them with the bits we want. An example of doing this in two steps is:
```
PORTA = PORTA & 0xF0; // sets the first four bits to zero.
PORTA = PORTA | (num & 0x0F); // sets the top four bits of num to zero. Then these bits are ORed with PORTA.
```
This can (and must for this lab) be done in one line of code.*/

//below is my single line of code :P
PORTA = (PORTA & 0XF0) | (num & 0x0F); 
}



