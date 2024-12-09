#include <avr/io.h>
#include <Arduino.h>
#include "spi.h"
//note to self, there should only be writing info, reading info should be done my main and i2c

#define wait_for_completion while(!(SPSR & (1<<SPIF)));


void initSPI(){
// set the SS, MOSI, and SCLK pin as output
DDRB |= (1 << DDB2) | (1 << DDB1) | (1 << DDB0);
// set the MISO pin as input
DDRB &= ~(1 << DDB3); //eventhough this lab does not need a MISO, it can be used for later labs.
// set SS high at first
PORTB |= (1 << PORTB0);
// enable the interrupt, SPI, master mode, CPOL, CPHA, default clock, and fosc/128
//ADXL345 CPOL = 1, CPHA = 1
SPCR |=  (1 << SPE) | (1 << MSTR) | (1 << CPOL)| (1 << CPHA)| (1 << SPR1) | (1 << SPR0); //removed SPIE since its not used here

}

void spi_write(unsigned char regAddress, unsigned char value){
// set SS low to begin SPI frame
PORTB &= ~(1 << PORTB0);
SPDR = regAddress;
wait_for_completion;
SPDR = value;
wait_for_completion;
// set SS high to end SPI frame
PORTB |= (1 << PORTB0);
//_delay_ms(1000);
}

unsigned char smiley[8] = {
    0b00000000,  // Row 1 
    0b00100100,  // Row 2 
    0b00100100,  // Row 3 
    0b00100100,  // Row 4 
    0b00000000,  // Row 5 
    0b01000010,  // Row 6 
    0b00111100,  // Row 7 
    0b00000000   // Row 8 
};
void writeSmile(){
for (int i = 0; i < 8; i++){ //go through character smile and write it on to the matrix line by line
    unsigned char row = 0x01 + i;
    spi_write(row, smiley[i]);
}
}
unsigned char frown[8] = {
    0b00000000,  // Row 1 
    0b00100100,  // Row 2 
    0b00100100,  // Row 3 
    0b00100100,  // Row 4 
    0b00000000,  // Row 5 
    0b00111100,  // Row 6 
    0b01000010,  // Row 7 
    0b00000000   // Row 8 
};
void writeFrown(){ //go through character frown and write it on to the matrix line by line
for (int i = 0; i < 8; i++){
    unsigned char row = 0x01 + i;
    spi_write(row, frown[i]);
}
}