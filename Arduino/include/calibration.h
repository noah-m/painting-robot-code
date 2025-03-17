#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <AccelStepper.h>
#include <EEPROM.h>
#include "globals.h"

void pin_setup(void);
void calibrate();
void manualZeroing();
void retrievePositionFromEEPROM();
void moveToTop();
long findWallDistance();
long findTrimDistance();
void resetServo();
void savePositionToEEPROM(long position);
long getPositionFromEEPROM();
float servoToMillimeters(long servoDistance);
float stepperToMillimeters(long stepperDistance);

#endif // CALIBRATION_H
