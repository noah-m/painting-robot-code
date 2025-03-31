#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <AccelStepper.h>
#include <EEPROM.h>
#include "globals.h"

void calibrate();
void AutoZero(int speed);
void retrievePositionFromEEPROM();
void moveToTop();
long findWallDistance();
long findTrimDistance();
void resetServo();
void savePositionToEEPROM(long position);
long getPositionFromEEPROM();
float servoToMillimeters(long servoDistance);
float stepperToMillimeters(long stepperDistance);
void initiateOffset(int offset);

void receiveData(int byteCount);
void pin_setup(void);
void drive(int command, int speed_slower, int speed_faster);

#endif // CALIBRATION_H
