#include <AccelStepper.h>
#include <EEPROM.h>

#include <pins.h>
#include <driving.h>
#include <callibration.h>

#define EEPROM_POSITION_ADDR 0
#define MAX_STEPPER_POSITION 2000
#define MIN_SERVO_ANGLE 50
#define MAX_SERVO_ANGLE 205

//Prototypes
void callibrate();
void savePositionToEEPROM(long);
long getPositionFromEEPROM(void);

// Create an AccelStepper object in DRIVER mode (1 = driver mode)
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// Robot states
enum ROBOT_STATES {CALLIBRATING, STATIONARY, PAINTING};
ROBOT_STATES robot_state;

void setup() {
  Serial.begin(9600);

  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(3000);  // Steps per second
  stepper.setAcceleration(0); // Steps per second^2

  // Set the initial speed (positive for one direction, negative for the other)
  stepper.setSpeed(100); // Steps per second

  // Set initial state
  robot_state = CALLIBRATING;
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

  // ## If zeroing button is pushsed on start-up, enter manual zeroing mode. Otherwise, use location from EEPROM.
  if (ZERO_BUTTON == LOW) {
    // Manual zeroing
    stepper.setSpeed(-100);
    while (ZERO_BUTTON == LOW)
    {
      stepper.runSpeed();
    }
    savePositionToEEPROM(0);
    stepper.setCurrentPosition(0);
  }
  else {
    // Retrieve position from EEPROM
    stepper.setCurrentPosition(getPositionFromEEPROM());
  }

  // Move carriadge to the top
  stepper.moveTo(2000);
  stepper.runToPosition();

  // Move limit switch assembly towards wall until first limit switch hit
  int angle = MIN_SERVO_ANGLE;
  while (true)
  {
    while (HORZ_LIMIT == HIGH)
    {
    angle++;
    analogWrite(SERVO, angle);
    delay(100);
    }
    angle--;
    analogWrite(SERVO, angle);
    delay(500);
    if (HORZ_LIMIT == LOW)
    {
      break;
    }
  }

  // TODO: Convert angle to wall distance

  // Move back down until other limit switch hit

  
  
  

  

}

void savePositionToEEPROM(long position) {
  // Automatically stores position over multiple memory cells starting from cell zero
  EEPROM.put(EEPROM_POSITION_ADDR, position);
  Serial.print("Position ");
  Serial.print(position);
  Serial.println(" saved to EEPROM");

}

long getPositionFromEEPROM(void) {
  // Automatically stores position over multiple memory cells specificed by input of type long starting from cell zero
  long position;
  EEPROM.get(EEPROM_POSITION_ADDR, position);
  Serial.print("Position ");
  Serial.print(position);
  Serial.println(" retrived from EEPROM");
  return position;
}