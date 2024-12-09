#include <avr/io.h>
#include <Arduino.h>
#include "spi.h"
//note to self, there should only be writing info, reading info should be done my main and i2c

#define wait_for_completion while(!(SPSR & (1<<SPIF)));
#define SS_PIN DDB0
#define MOSI_PIN DDB2
#define SCK_PIN DDB1
#define MISO_PIN DDB3


void initSPI(){
// set the SS, MOSI, and SCLK pin as output
DDRB |= (1 << SCK_PIN) | (1 << MOSI_PIN) | (1 << SS_PIN);
// set the MISO pin as input
DDRB &= ~(1 << MISO_PIN); //eventhough this lab does not need a MISO, it can be used for later labs.
// set SS high at first
PORTB |= (1 << PORTB0);
// enable the interrupt, SPI, master mode, CPOL, CPHA, default clock, and fosc/128
//ADXL345 CPOL = 1, CPHA = 1
SPCR |=  (1 << SPE) | (1 << MSTR) | (1 << CPOL)| (1 << CPHA)| (1 << SPR1) | (1 << SPR0); //removed SPIE since its not used here

}

void write_execute(unsigned char command, unsigned char value){
// set SS low to begin SPI frame
PORTB &= ~(1 << PORTB0);
SPDR = command;
wait_for_completion;
SPDR = value;
wait_for_completion;
// set SS high to end SPI frame
PORTB |= (1 << PORTB0);
//_delay_ms(1000);
}

void write_execute_bytes(unsigned char CMD, unsigned char count, unsigned char *values)
{

    PORTB &= ~(1 << PORTB0); //enable slave select bit to begin SPI frame
    SPDR = CMD;
    wait_for_completion; 
    for (unsigned char i = 0; i < count; i++)
    {
        SPDR = values[i];  //load the data into register
        wait_for_completion; 
    }
    PORTB |= (1 << PORTB0); // disable slave select to end SPI frame
}

unsigned char read_execute(unsigned char regAddress)
{
    write_execute(0x80 | regAddress, 0x00); 
    return SPDR;
}

