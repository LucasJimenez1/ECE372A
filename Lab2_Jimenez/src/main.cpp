#include <avr/io.h>
#include <Arduino.h>
#include <avr/interrupt.h>
#include "led.h"
#include "switch.h"
#include "timer.h"

#define SPEED_I 100 //default speed option
#define SPEED_II 200 //toggled speed option via switch / button 


    typedef enum stateName{
        wait_press, debounce_press, wait_release, debounce_release
    }   stateName;

    volatile  stateName state = wait_press;
    volatile int counter = 0;
    volatile int speed = SPEED_I;


int main(){
/*  1. A call to initLED() and initSwitchPB3() must be present in the main function.*/
    initLED(); //call to initLED()
    initSwitchPB3(); //call to initSwitchPB3
    initTimer0(); //call to initTimer0

    sei(); //enable the interrupt globally (<avr/interrupt.h>)

/*  2. An infinite while loop must be present.*/

    delayMs(speed);
    while (1){
        
        delayMs(speed);
        counter++;
        turnOnLEDWithChar(counter); //turns led on 

        switch (state){

            case wait_press:
                break;

            case debounce_press:
                state = wait_release;
                break;

            case wait_release:
                break;
            
            case debounce_release:
                if (speed == SPEED_I){
                    speed = SPEED_II;
                }
                else if (speed == SPEED_II){
                    speed = SPEED_I;
                }
                state = wait_press;
                break;
        }
    }
    return 0; //obligatory return 0 :P
}

ISR(PCINT0_vect){
    if(state == wait_press){
        state = debounce_press;
    }
    else if (state == wait_release){
        state = debounce_release;
    }
}