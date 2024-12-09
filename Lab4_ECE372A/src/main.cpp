// Author: Group 5, Matthew Minear, Lucas Jimenez, & Aiden Tsingine      
//Date: Thu class 10/24/2024
/* Description: . This program takes an analog value from a potentiometer on ADC channel 7 and converts it to a digital value.  
                . A formula is applied to convert the digital value to a voltage.  
                       Voltage_k = k * (VHigh/# of levels)
                . the serial.print function to display the converted ADC number in volts
                          */
#include <Arduino.h>
#include <avr/io.h>
#include "adc.h"
#include "pwm.h"
#include "sevensegment.h"
#include "switch.h"
#include "timer.h"
#include <avr/interrupt.h> //sei();


typedef enum stateName{
    wait_press, debounce_press, wait_release, debounce_release
}   stateName;


// Initialize states.  Remember to use volatile 

  volatile  stateName state = wait_press;

int main() {
initPWMTimer3();
initPWMTimer4();
initEnablePin();
initADC0();
initTimer0();
initTimer1();
initSevenSegment();
initSwitchPD0();
sei();

  Serial.begin(9600);
 /* unsigned int result = 0;
  float voltage = 0;
*/ 
  while(1){
/*
      // print out ADC value
	// read in ADCL first then read ADCH
      result = ADCL;
      result += (ADCH) << 8;
      //Voltage_k = k * (VHigh/# of levels)
      voltage = result * (4.586/1024.0); // 5 v from your kit reads~4.586
      Serial.println(voltage,2);
      //countdown(); this was for testing
*/
changeDutyCycle(); //this is the function that allows us to control the speed and direction of the motor

//Switch Debouncing
switch (state){

            case wait_press:
                break;

            case debounce_press:
                delayMs(10); //delay the button to allow for debouncing
                state = wait_release;
                break;

            case wait_release:
                break;
            
            case debounce_release:
                delayMs(10); //delay the button to allow for debouncing

            
                EIMSK &= ~(1 << INT0); //turn off button so countdown can start & finish without interruption
                countdown();
                EIMSK |= (1 << INT0);  //turn the button back on so we can use it again

                state = wait_press; 
                break;
      
  }

  }
}

//interrupt service routine
ISR(INT0_vect){
    if(state == wait_press){
        state = debounce_press;
    }
    else if (state == wait_release){
        state = debounce_release;
    }
}