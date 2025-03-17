#include "calibration.h"
#include <AccelStepper.h>
#include <EEPROM.h>
#include "globals.h"

void pin_setup(void) {
    Serial.begin(9600);
    pinMode(ENA_NEG_PIN, OUTPUT);
    pinMode(ENA_POS_PIN, OUTPUT);
    pinMode(DIR_NEG_PIN, OUTPUT);
    pinMode(DIR_POS_PIN, OUTPUT);
    pinMode(PUL_NEG_PIN, OUTPUT);
    pinMode(PUL_POS_PIN, OUTPUT);
    pinMode(LIMIT_GND_1_PIN, OUTPUT);
    pinMode(HORZ_LIMIT_PIN, INPUT_PULLUP);
    pinMode(VERT_LIMIT_PIN, INPUT_PULLUP);
    pinMode(LIMIT_GND_2_PIN, OUTPUT);
    pinMode(ZERO_BUTTON_PIN, INPUT_PULLUP);
    pinMode(SERVO_PIN, OUTPUT);

    digitalWrite(ENA_NEG_PIN, HIGH);  // LOW usually enables the TB6600, but HIGH does on ours!!
    digitalWrite(ENA_POS_PIN, HIGH);
    digitalWrite(DIR_POS_PIN, HIGH);
    digitalWrite(PUL_POS_PIN, HIGH);
    digitalWrite(LIMIT_GND_1_PIN, LOW);
    digitalWrite(LIMIT_GND_2_PIN, LOW);
}

void calibrate() {
    
    Serial.println("Starting: pin_setup");
    pin_setup();
    
    // if (ZERO_BUTTON_PIN == PUSHED) {
    //     manualZeroing();
    // } else {
    //     retrievePositionFromEEPROM();
    // }

    Serial.println("Starting: manualZeroing");
    manualZeroing();

    Serial.println("Starting: moveToTop");
    moveToTop();

    long wallDistance = findWallDistance();
    long trimDistnace = findTrimDistance();

    Serial.println("Starting savePositionToEEPROM");
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
    while (digitalRead(ZERO_BUTTON_PIN) == NOT_PUSHED) {
        Serial.println("Zero_Button_Pin Not Pushed");
        stepper.runSpeed();
    }
    Serial.println("Zero_Button_Pin Pushed");
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
    analogWrite(SERVO_PIN, angle);
    delay(SERVO_DELAY);

    while (true) {
        if (digitalRead(HORZ_LIMIT_PIN) == NOT_PUSHED && angle < MAX_SERVO_ANGLE) {
            angle++;
            analogWrite(SERVO_PIN, angle);
            delay(SERVO_DELAY);
        } else {
            angle--;
            analogWrite(SERVO_PIN, angle);
            delay(SERVO_BACK_DELAY);
            if (HORZ_LIMIT_PIN == PUSHED) {
                break;
            }
        }
    }
    return angle;
}

long findTrimDistance() {
    stepper.setSpeed(DEFAULT_SPEED);
    while (digitalRead(HORZ_LIMIT_PIN) == NOT_PUSHED) {
        stepper.runSpeed();
    }
    return stepper.currentPosition();
}

void resetServo() {
    analogWrite(SERVO_PIN, MIN_SERVO_ANGLE);
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

