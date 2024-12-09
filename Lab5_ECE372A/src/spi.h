#ifndef SPI_H
#define SPI_H

void initSPI();
void spi_write(unsigned char regAddress, unsigned char value);
void writeSmile();
void writeFrown();

#endif
