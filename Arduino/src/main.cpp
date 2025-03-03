#include <AccelStepper.h>

// Define pin connections
#define STEP_PIN 3  // Connect to PUL-
#define DIR_PIN 2   // Connect to DIR-

// Create an AccelStepper object in DRIVER mode (1 = driver mode)
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(3000);    // Steps per second
  stepper.setAcceleration(200); // Steps per second^2

  // Set the initial speed (positive for one direction, negative for the other)
  stepper.setSpeed(-2000); // Steps per second
}

void loop() {
  // Continuously run the motor at the set speed
  stepper.runSpeed();
}

// comment ia m 