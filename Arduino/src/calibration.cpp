#include <AccelStepper.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Servo.h>

#include "globals.h"

#include "driving.h"
#include "calibration.h"
#include "painting.h"

void calibrate() {

    Serial.println("Starting: AutoZero");

    //Bring stepper to top position via limit switch and set as position zero
    AutoZero(SET_SPEED);

    // Increment the servo angle until the wall is detected
    // and then decrement slightly to back off
    long wallDistance = findWallDistance();

    // Move the stepper motor until the limit switch is pushed
    // and return the current position as the trim distance
    long trimDistance = findTrimDistance();

    // Reset the servo to its initial position
    resetServo();

    //Let servo reset
    delay(1000);

    // Move paint assembly to painting position
    initiateOffset(-PAINT_OFFSET);

    // Print the wall distance and trim distance in millimeters
    float wallDistanceMillimeters = servoToMillimeters(wallDistance);
    float trimDistanceMillimeters = stepperToMillimeters(trimDistance);
    Serial.println("Calibration complete");
    Serial.print("Wall distance: ");
    Serial.println(wallDistance);
    Serial.print("Trim distance: ");
    Serial.println(trimDistance);
}

void AutoZero(int speed) {
    stepper.setSpeed(speed);
    while (digitalRead(ZERO_BUTTON_PIN) == NOT_PUSHED) {
        //Serial.println("Zero_Button_Pin Not Pushed");
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
    stepper.moveTo(MAX_STEPPER_POSITION);
    stepper.runToPosition();
    savePositionToEEPROM(MAX_STEPPER_POSITION);
}

long findWallDistance() {
    int angle = MIN_SERVO_ANGLE;
    myservo.write(angle); // Set the servo to its initial angle
    delay(SERVO_DELAY);

    // while (true) {
    //     if (digitalRead(HORZ_LIMIT_PIN) == NOT_PUSHED && angle < MAX_SERVO_ANGLE) {
    //         // Increment the servo angle and write it to the servo
    //         angle++;
    //         analogWrite(SERVO_PIN, angle);
    //         delay(SERVO_DELAY);
    //     } else {
    //         // Decrement the servo angle slightly to back off
    //         angle--;
    //         analogWrite(SERVO_PIN, angle);
    //         delay(SERVO_BACK_DELAY);

    //         // Break the loop if the limit switch is pushed
    //         if (digitalRead(HORZ_LIMIT_PIN) == PUSHED) {
    //             break;
    //         }
    //     }
    // }

    while (digitalRead(HORZ_LIMIT_PIN) == NOT_PUSHED && angle < MAX_SERVO_ANGLE) {
        // Increment the servo angle and write it to the servo
        angle++;
        myservo.write(angle); // Use Servo library to set angle
        delay(SERVO_DELAY);
    }

    // Return the final angle value
    return angle;
}

long findTrimDistance() {
    stepper.setSpeed(-SET_SPEED);
    while (digitalRead(VERT_LIMIT_PIN) == NOT_PUSHED) {
        stepper.runSpeed();
    }
    return stepper.currentPosition();
}

void resetServo() {
    myservo.write(MIN_SERVO_ANGLE); // Set the servo to its minimum angle
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
    return servoDistance * 1;
    // this is fake code 
}

float stepperToMillimeters(long stepperDistance) {
    return stepperDistance * 1;
    // Also fake code 
}

void initiateOffset(int offset) {
    stepper.move(offset);
    stepper.runToPosition();
}
