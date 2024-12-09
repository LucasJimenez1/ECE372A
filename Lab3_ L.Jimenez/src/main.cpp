// Author: Lucas Jimenez Miranda
// Net ID: lucasjimenez
// Date: 10.8.2024
// Assignment:     Lab 3
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//





#include <avr/io.h>
#include <avr/interrupt.h> //sei();
#include "led.h"
#include "switch.h"
#include "timer.h"
#include "lcd.h"

// defines
#define SPEED_I 200 //default speed option
#define SPEED_II 100 //toggled speed option via switch / button 


/*
 * Define a set of states that can be used in the state machine using an enum.
 */
// typedef enum .......
    typedef enum stateName{
        wait_press, debounce_press, wait_release, debounce_release
    }   stateName;


// Initialize states.  Remember to use volatile 

    volatile  stateName state = wait_press;
    volatile int counter = 0;
    volatile int speed = SPEED_I;




int main(){

  initTimer1(); //timer1 used for microseconds (uS)
  initLCD();
  initSwitchPB3();
  initLED();
  initTimer0(); //timer0 usef for milliseconds (mS) - code used from lab 2
  sei(); // Enable global interrupts.

  moveCursor(0, 0); // moves the cursor to 0,0 position
  writeString("Current mode: ");
  moveCursor(0, 1);  // moves the cursor to 0,1 position
  writeString("Slow");
  moveCursor(10, 1);
// writing special character
    unsigned char ArrayCh[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x1D, 0x1F}; //snail
    writeCharacter(0x00);
    setCGRAM(0X40);
    for (int i = 0; i < 8; i++){
        writeCharacter(ArrayCh[i]);
    }


// while loop
  while (1){
        
        delayMs(speed);
        counter++;
        turnOnLEDWithChar(counter); //turns led on 

        switch (state){

            case wait_press:
                break;

            case debounce_press:
                delayMs(10); //gotta let the button do its thing fr
                state = wait_release;
                break;

            case wait_release:
                break;
            
            case debounce_release:
                delayMs(10); //gotta let the button do its thing fr
                if (speed == SPEED_I){
                    speed = SPEED_II; //fast speed
                    moveCursor(0, 1); //move cursor to the beginning
                    writeString("Fast");
                      moveCursor(10, 1);
                        // writing special character
                        unsigned char ArrayCh[]={0x00, 0x01, 0x02, 0x04, 0x02, 0x04, 0x08, 0x00}; //lightning bolt
                        writeCharacter(0x00);
                        setCGRAM(0X40);
                        for (int i = 0; i < 8; i++){
                        writeCharacter(ArrayCh[i]);
                        }
                }

                else if (speed == SPEED_II){
                    speed = SPEED_I;//slow speed
                    moveCursor(0, 1); //move cursor to the beginning                    
                    writeString("Slow");
                      moveCursor(10, 1);
                        // writing special character
                        unsigned char ArrayCh[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x1D, 0x1F}; //snail
                        writeCharacter(0x00);
                        setCGRAM(0X40);
                        for (int i = 0; i < 8; i++){
                        writeCharacter(ArrayCh[i]);
                        }
                }
                state = wait_press;
                break;
        }
  }



  return 0;
}

/* Implement an Pin Change Interrupt which handles the switch being
* pressed and released. When the switch is pressed and released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.
*/

ISR(INT0_vect){
    if(state == wait_press){
        state = debounce_press;
    }
    else if (state == wait_release){
        state = debounce_release;
    }
}