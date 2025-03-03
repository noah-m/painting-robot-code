#include <AccelStepper.h>
#include <EEPROM.h>

#include <pins.h>
#include <driving.h>
#include <callibration.h>

// Robot states
enum ROBOT_STATES {CALLIBRATING, STATIONARY, PAINTING};
ROBOT_STATES robot_state = CALLIBRATING;

//Prototypes
void callibrate();

// Create an AccelStepper object in DRIVER mode (1 = driver mode)
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(3000);  // Steps per second
  stepper.setAcceleration(0); // Steps per second^2

  // Set the initial speed (positive for one direction, negative for the other)
  stepper.setSpeed(100); // Steps per second
}

void loop() {

  switch (robot_state) {
    case CALLIBRATING:
      callibrate();
      break;
    case STATIONARY:
      // stationary stuff
      break;
    case PAINTING:
      // painting stuff
      break;
  }
}

void callibrate() {
  

}