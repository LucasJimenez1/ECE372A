// Author: Group 5, Matthew Minear, Lucas Jimenez, & Aiden Tsingine      

#include <avr/io.h>
#include <Arduino.h>
#include <util/delay.h>
#include "sevensegment.h"
#include "timer.h"


void initSevenSegment(){
    DDRC |= (1 << PC0); //G
    DDRC |= (1 << PC1); //F
    DDRC |= (1 << PC2); //A
    DDRC |= (1 << PC3); //B
    DDRC |= (1 << PC4); //E
    DDRC |= (1 << PC5); //D
    DDRC |= (1 << PC6); //C
}

int display (int num){
    PORTC = 0x00; //clear display
    switch (num) { //switch case statment to tell which number to display on the seven segment display
        case 0:
            PORTC |= (1 << PC4) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC5) | (1 << PC6); // 0
            break;
        case 1:
            PORTC |= (1 << PC3) | (1 << PC6); // 1
            break;
        case 2:
            PORTC |= (1 << PC2) | (1 << PC3) | (1 << PC0) | (1 << PC4) | (1 << PC5); // 2
            break;
        case 3:
            PORTC |= (1 << PC2) | (1 << PC3) | (1 << PC0) | (1 << PC6) | (1 << PC5); // 3
            break;
        case 4:
            PORTC |= (1 << PC1) | (1 << PC0) | (1 << PC3) | (1 << PC6); // 4
            break;
        case 5:
            PORTC |= (1 << PC2) | (1 << PC1) | (1 << PC0) | (1 << PC6) | (1 << PC5); // 5
            break;
        case 6:
            PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC4) | (1 << PC5) | (1 << PC6); //6
            break;
        case 7:
            PORTC |= (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC6); // 7
            break;
        case 8:
            PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5) | (1 << PC6); // 8
            break;
        case 9:
            PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC5) | (1 << PC6); // 9
            break;
        default:
            break;
    }
    }

void countdown(){
    //turn off enable pin, enable pin basically acts as a master switch for the H-Bridge (L293D) so here it turns OFF the motor
    PORTB &= ~(1 << PB0);
    Serial.println("Enable Off"); //debugging
    for (int i = 9; i >= 0; i--) { // Loop from 9 to 0
        display(i);
        delayS(1); // Wait 1 second
    }
     PORTC = 0x00;   //clear display
    
    //turn on enable, enable pin basically acts as a master switch for the H-Bridge (L293D) so here it turns ON the motor
    PORTB |= (1 << PB0);
    Serial.println("Enable On"); //debugging
}