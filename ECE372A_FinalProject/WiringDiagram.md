# Wiring Diagram

## Battery to ATMEGA2560 Connections:

1. 9V battery *red* lead to **Vin**
2. 9v battery *black* lead to **GND**


## ATMEGA2560 to Breadboard Connections:

1. **5v** to **Positive Bus**
2. **GND** to **Negative/Ground Bus**

## Component Connections

### Passive Buzzer
1. **Positive Lead** to **PIN 8 (PH5 / PWM OC4C)**
2. **Negative Lead** to **Ground Bus**

### RFID Reader - RC522 - SPI Protocol
1. **SDA** to **PIN 53 (PB0 / SS)** //Slave Select
2. **SCK** to **PIN 52 (PB1 / SCK)** //Serial Clock (SPI)
3. **MOSI** to **PIN 51 (PB2 / MOSI)** //Master Out, Slave In
4. **MISO** to **PIN 50 (PB3 / MISO)** //Master In, Slave Out
5. **IRQ** **UNCONNECTED** //Interrupt
6. **GND** to **Ground Bus** //Ground
7. **3.3V** to **Positive Bus** //Vcc, please note that the module states 3.3V only; However, we could only get the module to work with 5V

### Accelerometer - MPU6050 - i2c Protocol
1. **FSYNC** **UNCONNECTED**
2. **NCS** **UNCONNECTED**
3. **AD0** **UNCONNECTED**
4. **ECL** **UNCONNECTED**
5. **EDA** **UNCONNECTED**
6. **SDA** to **PIN 20 (PD1 / SDA)** //Serial Data
7. **SCL** to **PIN 21 (PD0 / SCL)** //Serial Clock (i2c)
8. **GND** to **Ground Bus**
9. **Vcc** to **Positive Bus**

### Servo Motor
1. **Yellow Lead** to **PIN 5 (PE3 / PWM OC3A)**
2. **Red Lead** to **Positive Bus**
3. **Brown Lead** to **Ground Bus**

### LCD Potentiometer
1. **Pin 1** to **Positive Bus**
2. **Pin 2** to **V0**
3. **Pin 3** to **Ground Bus**

### LCD
1. **VSS** to **Ground Bus**
2. **VDD** to **Resistior** to **Positive Bus**
3. **V0** to **Pin 2** 
4. **RS** to **PIN 10 (PORTB4)**
5. **RW** to **Ground Bus**
6. **E** to **PIN 12 (PORTB6)**
7. **D0 - D3** **UNCONNECTED**
8. **D4** to **PIN 22 (PORTA0)** 
9. **D5** to **PIN 23 (PORTA1)**
10. **D6** to **PIN 24 (PORTA2)**
11. **D7** to **PIN 25 (PORTA3)**
12. **A** to **Resistor** to **Positive Bus**
13. **K** to **Ground Bus**

## Button
1. **Pin 1** to **Pin 19**
2. **Pin 4** to **Ground Bus**




