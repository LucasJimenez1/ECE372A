#ifndef SPI_H
#define SPI_H
//reususe from lab 5
void initSPI();
void write_execute(unsigned char CMD, unsigned char data);
unsigned char read_execute(unsigned char reg_address);
void write_execute_bytes(unsigned char CMD, unsigned char count, unsigned char *values);

#endif