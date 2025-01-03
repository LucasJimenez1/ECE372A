#include <Arduino.h>
#include <avr/io.h>

#include "rfid.h"
#include "spi.h"
#define UID_LIST_SIZE 2

int validUID[UID_LIST_SIZE] = {480, 407}; //fill with valid tag number (480 is Lucas' card, 407 is Lucas' tag)

void initRFID(){
    mfrc522.PCD_Init();// Init MFRC522
    delayMs(1); //one ms delay
    mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
}

int readRFID(){ //returns the RFID Unique ID (RFIDUID)

    if (!mfrc522.PICC_IsNewCardPresent()){ //no card present
        Serial.println("New card not present");
        return 0;
    }

    else if (!mfrc522.PICC_ReadCardSerial()){ //card present, RFID cannot read
        Serial.println("Error reading card");
        return 0;
    }
    // UID extraction: converting UID bytes to an integer for readability and ease of manipulation
    int num = 0;
    for (byte i = 0; i < mfrc522.uid.size; i++){
        num = num + mfrc522.uid.uidByte[i];
    }
    return num;
}

bool isAuthorized(int rfidUID){
    for (int i = 0; i < UID_LIST_SIZE; i++){
        if (rfidUID == validUID[i] && rfidUID != 0){
            return true;
        }
    }
    return false;
}