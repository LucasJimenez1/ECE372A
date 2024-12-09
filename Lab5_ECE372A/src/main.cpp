// Authors: Lucas Jimenez, Matthew Minear, & Aiden Tsingine        
//Date:
/* Description: */
#include <Arduino.h>
#include <avr/io.h>
#include "pwm.h"
#include "switch.h"
#include "timer.h"
#include "spi.h"
#include "i2c.h"
#include <avr/interrupt.h> //sei();

//definitions from MPU data sheet
#define SLA 0x68
#define XOUT_HIGH 0x3B
#define XOUT_LOW 0x3C
#define YOUT_HIGH 0x3D
#define YOUT_LOW 0x3E
#define ZOUT_HIGH 0x3F
#define ZOUT_LOW 0x40


//state machine for switch debouncing
typedef enum {
    wait_press, debounce_press, wait_release, debounce_release
}   stateName;
// Initialize states.  Remember to use volatile 


typedef enum {
    smile, frown, smileBUZZ, frownBUZZ
} matrixState;


volatile int xpos = 0;
volatile int ypos = 0;
volatile int zpos = 0;

volatile  matrixState mState = smile;
volatile  stateName state = wait_press;
volatile int alarmState = 0;

int main() {
    Serial.begin(9600);
    
    //Serial.println("intializations");
    InitI2C();
    initTimer1();
    initSPI();
    initPWMTimer4();
    initSwitchPD2();

/*
    //TESTING FOR ALARM FUNCTIONS
    delayMs(2000);
    alarmOff();
    delayMs(2000);
    alarmOn();
*/
    
    sei();//global interrupts

    StartI2C_Trans(SLA);
    Write(0x6B); //power management
    Write(0); //wake MPU 6050 from sleep
    StopI2C_Trans();

    
//Matrix testing:
  //Matrix brightness control
  spi_write(0x0A, 0x03);
  //Scan all rows and columns
  spi_write(0x0B, 0x07);
  //Set shutdown register to normal operation
  spi_write(0x0C, 0x01);
  //Set test register to normal operation
  spi_write(0x0F, 0x00);



    while (1){ //indefinite while loop

/*
Serial.print("PD3 State: ");
Serial.println(PIND & (1 << PD3) ? "HIGH" : "LOW");
delay(10); 
*/
    for (int i = 1500; i < 3000; i++){ //changing the ranges of 'i' gives us different chirps (ie. different pitches/delays sort of)
      changeFrequency(i);  
    }



    //read x position
    Read_from(SLA, XOUT_HIGH);
    xpos = Read_data();
    Read_from(SLA, XOUT_LOW);
    xpos = (xpos << 8) | Read_data(); //shift high value left, fill rest of values with low values
    Serial.println("xpos: ");
    Serial.println(xpos);

    //read y position
    Read_from(SLA, YOUT_HIGH);
    ypos = Read_data();
    Read_from(SLA, YOUT_LOW);
    ypos = (ypos << 8) | Read_data(); //shift high value left, fill rest of values with low values
    Serial.println("ypos: ");
    Serial.println(ypos);
   

    //read z position
    Read_from(SLA, ZOUT_HIGH);
    zpos = Read_data();
    Read_from(SLA, ZOUT_LOW); 
    zpos = (zpos << 8) | Read_data(); //shift high value left, fill rest of values with low values
    Serial.println("zpos: ");   
    Serial.println(zpos);


if ((xpos >= 8000) || (xpos <= -8000) || (ypos >= 8000) || (ypos <= -8000)){ //if MPU out of 45 degrees, turn on alarm and write a frown
        alarmOn();
      writeFrown();
    }
    else{ //if MPU in range, write a smile to the matrix
      writeSmile();
    }


//Switch Debouncing
switch (state){

  case wait_press:
    Serial.println("wait press ");
    Serial.flush(); 
    break;


  case debounce_press://when button is pressed turn the alarm off (line 141)
    Serial.println("debounce press ");
    Serial.flush();
   delayMs(1); //delay to allow for debouncing
    alarmOff(); 
    
   
    state = wait_release;
    break;



  case wait_release: //when button is pressed turn the alarm off (line 153) - this could be redundant 
    Serial.println("wait release ");
    Serial.flush();  
    delayMs(1); //delay to allow for debouncing
    alarmOff();
    
    state = debounce_release;
    break;
            
  case debounce_release:
    Serial.println("debounce release ");
    Serial.flush();  
    delayMs(1); //delay the button to allow for debouncing
    state = wait_press; 
    break;

    default:
    break;
      
  } //end of switch state machine



switch (mState) {
    case smile:
        Serial.println("Smile State ");
        alarmOff();    
        if ((xpos >= 8000) || (xpos <= -8000) || (ypos >= 8000) || (ypos <= -8000)){ //if out of range, write a frown
            mState = frownBUZZ;
        }


        break;

    case smileBUZZ:
            Serial.println("Smile BUZZ State ");

        if ((xpos >= 8000) || (xpos <= -8000) || (ypos >= 8000) || (ypos <= -8000)){ //if out of range, write a frown
            alarmOn();
            mState = frownBUZZ;
        }
        break;

    case frown: //not used
        alarmOff();
        Serial.println("Frown State ");
        if ((xpos >= 8000) || (xpos <= -8000) || (ypos >= 8000) || (ypos <= -8000)){
            mState = smile;

        }
        break;

    case frownBUZZ:
    alarmOn();
             Serial.println("Frown BUZZ State ");            
   
        if ((xpos >= 8000) || (xpos <= -8000) || (ypos >= 8000) || (ypos <= -8000)){ /*if out of range, go to smile state, and in 
        smile state if still out of range, go back to this state with the frown face, smile will NOT draw until normal conditions*/
            alarmOn();
            mState = smileBUZZ;
        }
        break;

    default:
    break;

  }


    } //end of while loop
    StopI2C_Trans();
}






//interrupt service routine (from previous lab)
ISR(PCINT2_vect){
    if(state == wait_press){
        state = debounce_press;
    }
    else if (state == wait_release){
        alarmOff();
        state = debounce_release;
    }
}