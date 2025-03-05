#include "calibration.h"
#include <AccelStepper.h>
#include <EEPROM.h>
#include "globals.h"

void calibrate() {
    if (ZERO_BUTTON == PUSHED) {
        manualZeroing();
    } else {
        retrievePositionFromEEPROM();
    }

    moveToTop();
    long wallDistance = findWallDistance();
    long trimDistnace = findTrimDistance();
    savePositionToEEPROM(stepper.currentPosition());
    resetServo();

    float wallDistanceMillimeters = servoToMillimeters(wallDistance);
    float trimDistanceMillimeters = stepperToMillimeters(trimDistnace);

    Serial.println("Calibration complete");
    Serial.print("Wall distance: ");
    Serial.println(wallDistance);
    Serial.print("Trim distance: ");
    Serial.println(trimDistnace);
}

void manualZeroing() {
    stepper.setSpeed(-DEFAULT_SPEED);
    while (ZERO_BUTTON == PUSHED) {
        stepper.runSpeed();
    }
    savePositionToEEPROM(0);
    stepper.setCurrentPosition(0);
}

void retrievePositionFromEEPROM() {
    stepper.setCurrentPosition(getPositionFromEEPROM());
}

void moveToTop() {
    stepper.moveTo(TOP_POSITION);
    stepper.runToPosition();
    savePositionToEEPROM(TOP_POSITION);
}

long findWallDistance() {
    int angle = MIN_SERVO_ANGLE;
    analogWrite(SERVO, angle);
    delay(SERVO_DELAY);

    while (true) {
        if (HORZ_LIMIT == NOT_PUSHED) {
            angle++;
            analogWrite(SERVO, angle);
            delay(SERVO_DELAY);
        } else {
            angle--;
            analogWrite(SERVO, angle);
            delay(SERVO_BACK_DELAY);
            if (HORZ_LIMIT == PUSHED) {
                break;
            }
        }
    }
    return angle;
}

long findTrimDistance() {
    stepper.setSpeed(DEFAULT_SPEED);
    while (NOT_PUSHED) {
        stepper.runSpeed();
    }
    return stepper.currentPosition();
}

void resetServo() {
    analogWrite(SERVO, MIN_SERVO_ANGLE);
    delay(SERVO_DELAY);
}

void savePositionToEEPROM(long position) {
    EEPROM.put(EEPROM_POSITION_ADDR, position);
    Serial.print("Position ");
    Serial.print(position);
    Serial.println(" saved to EEPROM");
}

long getPositionFromEEPROM() {
    long position;
    EEPROM.get(EEPROM_POSITION_ADDR, position);
    Serial.print("Position ");
    Serial.print(position);
    Serial.println(" retrieved from EEPROM");
    return position;
}

float servoToMillimeters(long servoDistance) {
    return servoDistance * 0.5;
    // this is fake code 
}

float stepperToMillimeters(long stepperDistance) {
    return stepperDistance * 0.5;
    // Also fake code 
}

