#ifndef RFID_H
#define RFID_H

#include <mfrc522.h>
extern MFRC522 mfrc522;

void initRFID(); //initialization
int readRFID(); //reading
bool isAuthorized(int numID); //authorization function


#endif