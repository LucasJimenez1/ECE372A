#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "switch.h"


#define SHORT_DELAY 100
#define LONG_DELAY 1000


int main(){

initLED(); //initialize LED
initSwitch(); //initialize switch (button)


//int delay;
unsigned  int LED;

while (1){ //indefinite loop to continuously run the LEDs

//if switch is pressed, use the long delay, else use the short delay (SHORT IS DEFAULT)
  if (switchONOFF() == 1){ 
    _delay_ms(LONG_DELAY);   
  }
  else{
    _delay_ms(SHORT_DELAY); 
  }

  //state machine:

  LED = 0; //led state 0 is leds located on pins 4 and 11
  runLED(LED); //led update function call

  //_delay_ms(delay); 

  if (switchONOFF() == 1){ 
    _delay_ms(LONG_DELAY);   
  }
  else{
    _delay_ms(SHORT_DELAY); 
  }

  LED = 1; 
  runLED(LED); //led update function call


  if (switchONOFF() == 1){ 
    _delay_ms(LONG_DELAY);   
  }
  else{
    _delay_ms(SHORT_DELAY); 
  }

  LED = 2; 
  runLED(LED); //led update function call

  //_delay_ms(delay);

    if (switchONOFF() == 1){ 
    _delay_ms(LONG_DELAY);   
  }
  else{
    _delay_ms(SHORT_DELAY); 
  }

  LED = 3; 
  runLED(LED); //led update function call


    if (switchONOFF() == 1){ 
    _delay_ms(LONG_DELAY);   
  }
  else{
    _delay_ms(SHORT_DELAY); 
  }

  LED = 4; 
  runLED(LED); //led update function call


    if (switchONOFF() == 1){ 
    _delay_ms(LONG_DELAY);   
  }
  else{
    _delay_ms(SHORT_DELAY); 
  }

  LED = 5; 
  runLED(LED); //led update function call
}

return 0; //obligatory return 0 
}