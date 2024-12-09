#include <Arduino.h>
#include "rfid.h"
#include "spi.h"
#include "timer.h"
#include "pwm.h"
#include "lcd.h"

#define SS 53
#define RST_PIN 49


// Declare the MFRC522 object
MFRC522 mfrc522(SS, RST_PIN); // SS and RST_PIN should be defined based on your wiring.

void setup() {
    Serial.begin(9600); // Initialize serial communication
    initSPI();          // Initialize SPI communication
    initRFID();         // Initialize RFID module
    initTimer0();       // Initialize timer for delays
    initPWMTimer3();
    initLCD();
    Serial.println("initializations finished");

  moveCursor(0,0);
  writeString("hello world!");
  moveCursor(0, 1);
  writeString("KYS");
}

void loop() {
    //rfid
    int rfidUID = readRFID(); // Read the RFID card
    if (rfidUID > 0) {        // If a valid UID is detected
        Serial.print("Card Detected. UID: ");
        Serial.println(rfidUID); // Print the UID
        delayMs(1000);         // Wait for 2 seconds before checking again
    }
    

   
    Serial.println("locking"); // Print the UID
   servoLock();
   delayMs(2000);
    Serial.println("unlocking"); // Print the UID
   servoUnlock();
   
  


}
