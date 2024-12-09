//#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"


    //PORTB = 0xFF; //pull up resistor enabled

void initLED(){
    /*initalizing the LEDs, setting them as outputs.*/
    DDRB |= (1 << DDB5); //DDB5 - LED on pin 11
    DDRB |= (1 << DDB4); //DDB4 - LED on pin 10
    DDRH |= (1 << DDH6); //DDH6 - LED on pin 9
    DDRH |= (1 << DDH5); //DDH5 - LED on pin 8
    DDRH |= (1 << DDH4); //DDH4 - LED on pin 7
    DDRH |= (1 << DDH3); //DDH3 - LED on pin 6
    DDRE |= (1 << DDE3); //DDE3 - LED on pin 5
    DDRG |= (1 << DDG5); //DDG5 - LED on pin 4
}

void turnOnLED(unsigned int LED){ //function to turn ON each LED, to be called during loop to specify which LED to turn on
    switch (LED){

        case 4:
        PORTG |= (1 << PG5);
        break;

        case 5:
        PORTE |= (1 << PE3);
        break;

        case 6:
        PORTH |= (1 << PH3);
        break;

        case 7: 
        PORTH |= (1 << PH4);
        break;

        case 8:
        PORTH |= (1 << PH5);
        break;

        case 9:
        PORTH |= (1 << PH6);
        break;

        case 10:
        PORTB |= (1 << PB4);
        break;

        case 11:
        PORTB |= (1 << PB5);
        break;
    }
    

}

void turnOffLED(unsigned int LED){ //function to turn OFF each LED, to be called during loop to specify which LED to turn on
    switch (LED){

        case 4:
        PORTG &= ~(1 << PG5);
        break;

        case 5:
        PORTE &= ~(1 << PE3);
        break;

        case 6:
        PORTH &= ~(1 << PH3);
        break;

        case 7: 
        PORTH &= ~(1 << PH4);
        break;

        case 8:
        PORTH &= ~(1 << PH5);
        break;

        case 9:
        PORTH &= ~(1 << PH6);
        break;

        case 10:
        PORTB &= ~(1 << PB4);
        break;

        case 11:
        PORTB &= ~(1 << PB5);
        break;
    }    
    
    
}

void runLED(unsigned int LED){
    int state;
    if (LED == 0){
    state = 5;
    turnOffLED(state);
    state = 10;
    turnOffLED(state);

    state = 4;
    turnOnLED(state);
    state = 11;
    turnOnLED(state);
    }

    if (LED == 1){
    state = 4;
    turnOffLED(state);
    state = 11;
    turnOffLED(state); 

    state = 5;
    turnOnLED(state);
    state = 10;
    turnOnLED(state);    
    }

    if (LED == 2){
    state = 5;
    turnOffLED(state);
    state = 10;
    turnOffLED(state); 

    state = 6;
    turnOnLED(state);
    state = 9;
    turnOnLED(state);    
    }

    if (LED == 3){
    state = 6;
    turnOffLED(state);
    state = 9;
    turnOffLED(state); 

    state = 7;
    turnOnLED(state);
    state = 8;
    turnOnLED(state);    
    }

    if (LED == 4){
    state = 7;
    turnOffLED(state);
    state = 8;
    turnOffLED(state); 

    state = 6;
    turnOnLED(state);
    state = 9;
    turnOnLED(state);    
    }

    if (LED == 5){
    state = 6;
    turnOffLED(state);
    state = 9;
    turnOffLED(state); 

    state = 10;
    turnOnLED(state);
    state = 5;
    turnOnLED(state);    
    }

}


