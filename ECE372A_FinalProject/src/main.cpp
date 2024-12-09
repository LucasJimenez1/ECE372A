// Authors: Lucas Jimenez, Matthew Minear, & Aiden Tsingine        
//Date:
/* Description: RFID-enabled lockbox with a buzzer alarm*/

//Libraries
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h> 

//Header files
#include "i2c.h"
#include "lcd.h"
#include "MFRC522.h"
#include "pwm.h"
#include "rfid.h"
#include "switch.h"
#include "timer.h"
#include "spi.h"

//Definitions
//definitions from MPU data sheet
#define SLA 0x68
#define XOUT_HIGH 0x3B
#define XOUT_LOW 0x3C
#define YOUT_HIGH 0x3D
#define YOUT_LOW 0x3E
#define ZOUT_HIGH 0x3F
#define ZOUT_LOW 0x40

//mapping definitions
#define RST_PIN 49
#define SS_PIN 53  // slave-select pin for spi


//state machine for switch debouncing
typedef enum {
    wait_press, debounce_press, wait_release, debounce_release
}   stateName;

typedef enum {
    state_1, state_2, state_3, state_4
}   mainStateName;

//volatile variables
volatile int xpos = 0;
volatile int ypos = 0;
volatile int zpos = 0;
volatile stateName state = wait_press;
volatile mainStateName mainState = state_1;

//other globals
int activeRFID = 0; //this is the RFID number that will open the lock 


MFRC522 mfrc522(SS_PIN, RST_PIN); //Create MFRC522 instance




int main() {
    Serial.begin(9600); //testing/debugging
   /* delayMs(1000);
    Serial.println("First serial comment ");
    Serial.flush();
    delayMicroseconds(1000);
    Serial.println("Second serial comment ");
    Serial.flush();*/




    //initializations
    initTimer0(); //timers must initialize first
    initTimer1();
    Serial.println("I2C initialize"); Serial.flush();
    InitI2C();
    Serial.println("I2C itialized"); Serial.flush();
    Serial.println("LCD initialize"); Serial.flush();

    initLCD();
    Serial.println("LCD initialized"); Serial.flush();
    //moveCursor(0,0);
    //writeString("Unlocked");
    //moveCursor(0,1);
    //writeString("Alarm Off");

    Serial.println("PWM-3 Intialize"); Serial.flush();
    initPWMTimer3(); //PWMTimer3 is initally on; However, the servo is in the neutral/unlock state; nothing should happen
    Serial.println("PWM-3 Intialized"); Serial.flush();

    Serial.println("PWM-4 Intialize"); Serial.flush();
    initPWMTimer4();
    Serial.println("PWM-4 Intialized"); Serial.flush();

    Serial.println("SPI Intialize"); Serial.flush();
    initSPI();
    Serial.println("SPI Intialized"); Serial.flush();
    Serial.println("Switch Intialize"); Serial.flush();
    initSwitchPD2();
    Serial.println("Switch Intialized"); Serial.flush();
    Serial.println("sei Intialize"); Serial.flush();
    Serial.println("RFID Intialize"); Serial.flush();
    initRFID(); //has to occur after SPI init
    Serial.println("RFID Intialized"); Serial.flush();
    //global interrupt
    //sei(); turned on state_1
    Serial.println("sei Intialized"); Serial.flush();

    //i2C functionallity
    StartI2C_Trans(SLA);
    Write(0x6B); //power management
    Write(0); //wake MPU 6050 from sleep
    StopI2C_Trans();


    
    //indefinite while loop
    while(1){
        

        /* this may or may not be used
        //grab the activeRFID:
        while (activeRFID == 0){
        //LCD print: "Present Active RFID"
        activeRFID = readRFID();
        }*/
        

        //buzzer pitches
        for (int i = 500; i < 1600; i++){ //changing the ranges of 'i' gives us different chirps (ie. different pitches/delays sort of)
      changeFrequency(i);
      delayUs(20);
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
   


//this if-else statement might be redundant
/*
if ((xpos >= 8000) || (xpos <= -8000) || (ypos >= 8000) || (ypos <= -8000)){ //if MPU out of 45 degrees, turn on alarm and write a frown
        alarmOn();
        Serial.println("Alarm on");
    }
    else{ //if MPU in range, do nothing?
    }
*/


switch (mainState){
    case state_1:
    sei(); //turn on button
    Serial.println("state_1"); Serial.flush();
    servoUnlock();    Serial.println("Servo Unlocked"); Serial.flush();
    alarmOff(); //alarm should not ring in this state
    //print "Unlocked" on LCD
    clearLCD();
    moveCursor(0, 0); // moves the cursor to 0,0 position
    writeString("Unlocked");
    moveCursor(0, 1);
    writeString("Press to lock");
    //turn button on
    //go to state 2 once lock is enabled


    break;

    case state_2:
    cli();    //turn button off (cli();)
    Serial.println("state_2"); Serial.flush();

    //lock servo
    servoLock();
    //print "Locked" on line 1 of LCD
    clearLCD();
    moveCursor(0, 0); // moves the cursor to 0,0 position
    writeString("Locked");
    //print "Present RFID on LCD"
    moveCursor(0, 1); // moves the cursor to bottom line
    writeString("Present RFID");

    activeRFID = readRFID(); //reading RFID
    delayMs(1000); //1 second delay - might be removed

    if (isAuthorized(activeRFID)){ //if RFID is authorized go to state 4
        mainState = state_1;
    }

    else if (!(isAuthorized(activeRFID))){ //incorrect alarm presented
        mainState = state_4;
    }
        
    else if ((xpos >= 8000) || (xpos <= -8000) || (ypos >= 8000) || (ypos <= -8000)){ //motion detected, activate alarm
        mainState = state_3;
        alarmOn();
    }

    break;
    case state_3: //this might be a redundant state
    Serial.println("state_3"); Serial.flush();
    alarmOn(); //could be redundant
    //LCD Print (line 1) "Alarm Activated!"
    clearLCD();
    moveCursor(0, 0); // moves the cursor to 0,0 position
    writeString("Alarm Activated");    
    //LCD Print (line 2) "Present RFID"
    moveCursor(0, 1); // moves the cursor to 0,0 position
    writeString("Present RFID");      

    activeRFID = readRFID(); //reading RFID
    delayMs(1000); //1 second delay - might be removed

    if (isAuthorized(activeRFID)){ //if RFID is authorized go to state 1
        mainState = state_1;
    }

    else if (!(isAuthorized(activeRFID))){ //if an incorrect RFID is presented, go to state 4
        mainState = state_3;
    }    
    break;

    case state_4:
    //alarmOn();
    Serial.println("state_4"); Serial.flush();
    //LCD Print (line 1) "Unauthorized RFID"
    clearLCD();
    moveCursor(0, 0); // moves the cursor to 0,0 position
    writeString("Invalid RFID");      
    //LCD Print (line 2) "Present RFID"
    moveCursor(0, 1); // moves the cursor to 0,1 position
    writeString("Present RFID");  

if ((xpos >= 8000) || (xpos <= -8000) || (ypos >= 8000) || (ypos <= -8000)){ //if MPU out of 45 degrees, turn on alarm and write a frown
        alarmOn();
        mainState = state_3;
    }


    activeRFID = readRFID(); //reading RFID
    delayMs(1000); //1 second delay - might be removed

    if (isAuthorized(activeRFID)){ //if RFID is authorized go to state 1
        mainState = state_1;
    }

    else if (!(isAuthorized(activeRFID))){ //if an incorrect RFID is presented, go to state 4
        mainState = state_4;
    }    
    break;

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
    
    mainState = state_2; //lock is activated
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


    } //end while loop


} //end main 


//interrupt service routine (from lab 5)
ISR(INT2_vect){
    if(state == wait_press){
        state = debounce_press;
    }
    else if (state == wait_release){
        state = debounce_release;
    }
}