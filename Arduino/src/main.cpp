#include <AccelStepper.h>
#include <EEPROM.h>

#include "globals.h"
#include "driving.h"
#include "calibration.h"

//Prototypes
void callibrate();
void savePositionToEEPROM(long);
long getPositionFromEEPROM(void);

// Create an AccelStepper object in DRIVER mode (1 = driver mode)
AccelStepper stepper(AccelStepper::DRIVER, PUL_NEG_PIN, DIR_NEG_PIN);

// Robot states
enum ROBOT_STATES {CALIBRATING, STATIONARY, PAINTING};
ROBOT_STATES robot_state;

void setup() {
  Serial.begin(9600);

  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(3000);  // Steps per second
  stepper.setAcceleration(400); // Steps per second^2

  // Set the initial speed (positive for one direction, negative for the other)
  stepper.setSpeed(100); // Steps per second

  // Set initial state
  robot_state = CALIBRATING;
}

void loop() {

  switch (robot_state) {
    case CALIBRATING:

      pin_setup();

      if (digitalRead(ZERO_BUTTON_PIN) == PUSHED) {
        Serial.println("Pushed");
      }
      else {
        Serial.println("Not Pushed");
      }

      delay(100);

      

      //Serial.println("Starting: Calibrate");
      //calibrate();
      break;
    case STATIONARY:
      // stationary stuff
      break;
    case PAINTING:
      // painting stuff
      break;
  }


  //Serial.println("END");
  //delay(10000000);
}

