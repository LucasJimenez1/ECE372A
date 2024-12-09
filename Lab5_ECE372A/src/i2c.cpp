#include <avr/io.h>
#include <Arduino.h>
#include "i2c.h"
#define wait_for_completion while(!(TWCR & (1 << TWINT)));
/* twea - enable acknowledge, twsr - status register, twcr - control register, twdr - data register, twbr - bit rate register, 
twint - interrupt flag, twen - enable I2c module, twsta - start bit, twps - prescalar
*/

void InitI2C(){


PRR0 &= ~(1 << PRTWI); //pg 236 datasheet - wake up 


TWSR |= (1 << TWPS0);
TWSR &= ~(1 << TWPS1);

//TWSR &= ~((1 << TWPS0) | (1 << TWPS1)); //prescalar of TWPS to 1

TWBR = 0xC6; //TWBR = 198, using 10kHz SCL clock, //set two wire interface bit rate register TWBR

TWCR = (1 << TWEN) | (1 << TWINT); //set enable bit to 1, flag to 1, to iniate the I2C interface


}
void StartI2C_Trans(unsigned char SLA){
TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTA)); //initiate enable, clear interrupt, initiate start condition

wait_for_completion;

TWDR = (SLA << 1) | 0x00;// data to send (address + write bit) //set two wire data register to the slave + write bit

TWCR = ((1 << TWINT) | (1 << TWEN));//trigger action: clear interrupt, and intiate enable

wait_for_completion;
}
void StopI2C_Trans(){
    TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWSTO));//trigger action + stop condition
}
void Write(unsigned char data){
    TWDR = data; //set two wire data register equal to incoming data

    TWCR = ((1 << TWINT) | (1 << TWEN));//trigger action

    wait_for_completion;
}
void Read_from(unsigned char SLA, unsigned char MEMADDRESS){ //this function sets up reading from SLA at the SLA MEMADDRESS
StartI2C_Trans(SLA); //start transmission to the slave

Write(MEMADDRESS); //write to memory address

TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); //restart to switch to read mode

wait_for_completion;

TWDR = (SLA << 1) | 0x01; //1 is the read bit, as opposed to 0 being the write bit

TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); //trigger action, with master sending ackknowledge bit

wait_for_completion;

TWCR = (1 << TWINT) | (1 << TWEN); //trigger action, master can send a nack now

wait_for_completion;

TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); //trigger action + stop condition

//after this function executes, the TWDR register has the data from slave that Master wants to read
//wait_for_completion;

//StopI2C_Trans();

}
unsigned char Read_data(){
    return TWDR;
}