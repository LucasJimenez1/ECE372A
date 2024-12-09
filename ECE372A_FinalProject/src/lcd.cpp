// Author: Lucas Jimenez Miranda
// Net ID: lucasjimenez
// Date: 10.8.2024
// Assignment: Lab 3
//----------------------------------------------------------------------//
#include "lcd.h"
#include "timer.h"
#include <util/delay.h>

/*
 * Initializes all pins related to the LCD to be outputs
 */

/*1. All functions provided must be used in the implementation of the LCD interface
according to their descriptions. Please read comments within the blank Lab 3 file

2. PORTA0, PORTA1, PORTA2, and PORTA3 must be used for the data pins on
the LCD with PORTA0 corresponding to the least significant bit

3. PORTB4 and PORTB6 must be used for the enable pin and RS pin, respectively.

4. When four bits need to be assigned to PORTA, it must be done in **one line of
code**. There are times where you need to send four bits twice, in this case, you
need two lines of code*/

void initLCDPins(){

  DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3); 
  /*2. PORTA0, PORTA1, PORTA2, and PORTA3 must be used for the data pins on 
  the LCD with PORTA0 corresponding to the least significant bit */
  
  DDRB |= (1 << DDB4) | (1 << DDB6); //3. PORTB4 and PORTB6 must be used for the enable(B4) pin and RS(B6) pin, respectively.
}



/* 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *      a. data is an unsigned char which has 8 bits. Therefore, you
 *         need assign the bottom 4 bits of "data" to the appropriate bits in
 *         PORTA
 *  2. This is a "command" signal, meaning RS should be Low
 *  3. Assert high on enable pin, delay, and asset low on enable pin
 *  4. delay the provided number in MICROseconds.
 */
void fourBitCommandWithDelay(unsigned char data, unsigned int delay){
  //1. Assert bits to pins connected to DB[7:4] on the LCD screen
  PORTA = (PORTA & 0XF0) | (data >> 4 & 0X0F);
  delayUs(5); //delay 5 microseconds

//2. This is a "command" signal, meaning RS should be Low
  PORTB &= ~(1 << PORTB6); //RS pin set to low

//3. Assert high on enable pin, delay, and asset low on enable pin
  PORTB |= (1 << PORTB4); //enable pin set to high
  delayUs(5); //delay 5 microseconds
  PORTB &= ~(1 << PORTB4); //enable pin set to low

//4. delay the provided number in MICROseconds.
  delayUs(delay);

}



/* Similar to fourBitCommandWithDelay except that now all eight bits of command are
 * sent.
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *       a. unlike fourBitCommandWithDelay, you need to send the TOP four bits of
 *          "command" first. These should be assigned to appropriate bits in PORTA
 * 2. This is a command signal, meaning RS should be low
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of command to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay the provided number in MICROseconds.
 */
void eightBitCommandWithDelay(unsigned char command, unsigned int delay){
  //1. Assert bits to pins connected to DB[7:4] on the LCD screen
  PORTA = (PORTA & 0xF0) | ((command >> 4) & 0x0F);

  //2. This is a command signal, meaning RS should be low
  PORTB &= ~(1 << PORTB6); //RS pin set to low

  //3. Assert high on enable pin, delay, and asset low on enable pin
  PORTB |= (1 << PORTB4); //enable pin set to high
  delayUs(5); //delay 5 microseconds
  PORTB &= ~(1 << PORTB4); //enable pin set to low

  //4. Now set the lower four bits of command to appropriate bits in PORTA
  PORTA = (PORTA & 0xF0) | (command & 0x0F);

  //5. Assert high on enable pin, delay, and asset low on enable pin
  PORTB |= (1 << PORTB4); //enable pin set to high
  delayUs(5); //delay 5 microseconds
  PORTB &= ~(1 << PORTB4); //enable pin set to low

  //6. delay the provided number in MICROseconds.
  delayUs(delay);


}



/* Similar to eightBitCommandWithDelay except that now RS should be high
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 * 2. This is a "data" signal, meaning RS should be high
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of character to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay is always 46 MICROseconds for a character write
 */
void writeCharacter(unsigned char character){
 //1. Assert bits to pins connected to DB[7:4] on the LCD screen
  PORTA = (PORTA & 0xF0) | ((character >> 4) & 0x0F);

 //2. This is a "data" signal, meaning RS should be high
  PORTB |= (1 << PORTB6); //RS pin set to high

 //3. Assert high on enable pin, delay, and asset low on enable pin
  PORTB |= (1 << PORTB4); //enable pin set to high
  delayUs(5); //delay 5 microseconds
  PORTB &= ~(1 << PORTB4); //enable pin set to low

 //4. Now set the lower four bits of character to appropriate bits in PORTA 
  PORTA = (PORTA & 0xF0) | (character & 0x0F);

 //5. Assert high on enable pin, delay, and asset low on enable pin 
  PORTB |= (1 << PORTB4); //enable pin set to high
  delayUs(5); //delay 5 microseconds
  PORTB &= ~(1 << PORTB4); //enable pin set to low

 //6. delay is always 46 MICROseconds for a character write
  delayUs(46);
}




/*
 * Writes a provided string such as "Hello!" to the LCD screen. You should
 * remember that a c string always ends with the '\0' character and
 * that this should just call writeCharacter multiple times.
 */
void writeString(const char *string){
    for (int i = 0; string[i] != '\0'; i++) {
        writeCharacter(string[i]);   // Write each character to the LCD
    }
  }



/*
 * This moves the LCD cursor to a specific place on the screen.
 * This can be done using the eightBitCommandWithDelay with correct arguments
 */
void moveCursor(unsigned char x, unsigned char y){
    unsigned char address;
    // Determine the address based on the row (y)
    if (y == 0) {
        address = x;          // Row 0 starts at 0x00
    } else if (y == 1) {
        address = 0x40 + x;   // Row 1 starts at 0x40
    }

    // Send the command to move the cursor to the calculated address
    eightBitCommandWithDelay(0x80 | address, 46);  // 0x80 sets DDRAM address
}



/* This is the procedure outline on the LCD datasheet page 4 out of 9.
 * This should be the last function you write as it largely depends on all other
 * functions working.
 */
void initLCDProcedure(){
  delayMs(15); // Delay 15 milliseconds

  // Write 0b0011 to DB[7:4] and delay 4100 microseconds (initialize 8-bit mode_)
  fourBitCommandWithDelay(0b0011, 4100);
  
  // Write 0b0011 to DB[7:4] and delay 100 microseconds
  fourBitCommandWithDelay(0b0011, 100);

  // The data sheet does not make this clear, but at this point you are issuing
  // commands in two sets of four bits. You must delay after each command
  // (which is the second set of four bits) an amount specified on page 3 of
  // the data sheet.
  // write 0b0011 to DB[7:4] and 100us delay
  fourBitCommandWithDelay(0b0011, 100);

  // write 0b0010 to DB[7:4] and 100us delay. (Switch to 4-bit mode)
  fourBitCommandWithDelay(0b0010, 100);

  // Function set in the command table with 53us delay
  eightBitCommandWithDelay(0b00101000, 53);

  // Display off in the command table with 53us delay
  eightBitCommandWithDelay(0b00001000, 53);

  // Clear display in the command table. Remember the delay is longer!!!
  eightBitCommandWithDelay(0b00000001, 3000);

  // Entry Mode Set in the command table.
  eightBitCommandWithDelay(0b00000110, 53);

  // Display ON/OFF Control in the command table. (Yes, this is not specified),
  // in the data sheet, but you have to do it to get this to work. Yay datasheets!)
  eightBitCommandWithDelay(0b00001100, 53);

}



/* Initializes Tri-state for LCD pins and calls initialization procedure.
* This function is made so that it's possible to test initLCDPins separately
* from initLCDProcedure which will likely be necessary.
*/
void initLCD(){
  initLCDPins();
  initLCDProcedure();
}

void clearLCD() {
    // Send the clear display command (0x01)
    eightBitCommandWithDelay(0x01, 3000); // Clear display, takes 3ms as per datasheet
}