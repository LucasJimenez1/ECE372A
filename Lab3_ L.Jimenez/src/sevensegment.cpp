#include <avr/io.h>
#include <util/delay.h>
#include "sevensegment.h"
#include "timer.h"


void initSevenSegment(){
    DDRC |= (1 << PC0); //A
    DDRC |= (1 << PC1); //B
    DDRC |= (1 << PC2); //C
    DDRC |= (1 << PC3); //D
    DDRC |= (1 << PC4); //E
    DDRC |= (1 << PC5); //F
    DDRC |= (1 << PC6); //G
}

void countdown(){
    //9
    PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC5) | (1 << PC6);
    //delayS
    //8
    PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC5) | (1 << PC6) | (1 << PC4);
    //delayS
    //7
    PORTC &= ~(1 << PC4) | (1 << PC3) | (1 << PC6);
    //delayS
    //6
    PORTC |= (1 << PC3) | (1 << PC4) | (1 << PC6);
    PORTC &= ~(1 << PC5);
    //delayS
    //5
    PORTC |= (1 << PC5);
    PORTC &= ~(1 << PC1) | (1 << PC4);
    //delayS
    //4
    PORTC &= ~(1 << PC4) | (1 << PC0) | (1 << PC3);
    PORTC |= (1 << PC1);
    //delayS
    //3
    PORTC &= ~(1 << PC5);
    PORTC |= (1 << PC3);
    //delayS
    //2
    PORTC &= ~(1 << PC2);
    PORTC |= (1 << PC4);
    //delayS
    //1
    PORTC &= ~(1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5) | (1 << PC6);
    PORTC |= (1 << PC1) | (1 << PC2);
    //delayS
    //0
    PORTC |= (1 << PC0)| (1 << PC3) | (1 << PC4) | (1 << PC5);


}


