#ifndef PWM_H
#define PWM_H

//buzzer control
void initPWMTimer4();
void changeFrequency(int frequency);
void alarmOn();
void alarmOff();

//servo control
void initPWMTimer3();
void servoLock();
void servoUnlock();

#endif