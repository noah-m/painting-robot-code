#include <AccelStepper.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Servo.h>

#include "globals.h"
#include "driving.h"
#include "calibration.h"
#include "painting.h"

// Create an AccelStepper object in DRIVER mode (1 = driver mode)
AccelStepper stepper(AccelStepper::DRIVER, PUL_NEG_PIN, DIR_NEG_PIN);
AccelStepper paintStepper(AccelStepper::DRIVER, PAINT_PUL_NEG_PIN, PAINT_DIR_NEG_PIN);

// Create a Servo object to control the servo motor
Servo myservo;

// Robot states (declared in globals.h)
ROBOT_STATES robot_state;

void setup() {

    Serial.begin(9600);
    pin_setup();
    Wire.begin(UNO_ADDR);  
    Wire.onReceive(receiveData);  // Set callback function when data is received

    // Set the maximum speed and acceleration
    stepper.setMaxSpeed(MAX_SPEED);  // Steps per second
    stepper.setAcceleration(MAX_ACCELERATION); // Steps per second^2
    stepper.setSpeed(SET_SPEED); // Steps per second

    // Set initial state
    robot_state = DRIVING;

    // Reset servo to initial position
    //resetServo();
}

void loop() {

    switch (robot_state) {
        case DRIVING:
            Serial.println("Starting: Driving");
            while (true)
            {
              // Wait for the robot to receive commands from the Raspberry Pi
            }
            
            break;
        case CALIBRATING:
            Serial.println("Starting: Calibrate");
            calibrate();
            robot_state = PAINTING; // Change state to PAINTING after calibration
            break;
        case PAINTING:
            Serial.println("Starting: Painting");
            paint();
            break;
        case STOPPED:
            Serial.println("Starting: Stopped");
            //stop drive motors
            delay(100000000);
            break;
    }
}

void pin_setup(void) {
  Serial.println("Starting: pin_setup");
  pinMode(ENA_NEG_PIN, OUTPUT);
  pinMode(ENA_POS_PIN, OUTPUT);
  pinMode(DIR_NEG_PIN, OUTPUT);
  pinMode(DIR_POS_PIN, OUTPUT);
  pinMode(PUL_NEG_PIN, OUTPUT);
  pinMode(PUL_POS_PIN, OUTPUT);

  pinMode(PAINT_ENA_NEG_PIN, OUTPUT);
  pinMode(PAINT_ENA_POS_PIN, OUTPUT);
  pinMode(PAINT_DIR_NEG_PIN, OUTPUT);
  pinMode(PAINT_DIR_POS_PIN, OUTPUT);
  pinMode(PAINT_PUL_NEG_PIN, OUTPUT);
  pinMode(PAINT_PUL_POS_PIN, OUTPUT);

  pinMode(LIMIT_GND_1_PIN, OUTPUT);
  pinMode(HORZ_LIMIT_PIN, INPUT_PULLUP);
  pinMode(VERT_LIMIT_PIN, INPUT_PULLUP);
  pinMode(LIMIT_GND_2_PIN, OUTPUT);
  pinMode(ZERO_BUTTON_PIN, INPUT_PULLUP);
  myservo.attach(SERVO_PIN); // Attach the servo to the specified pin

  pinMode(Motor1_In1, OUTPUT);
  pinMode(Motor1_In2, OUTPUT);
  pinMode(Motor2_In1, OUTPUT);
  pinMode(Motor2_In2, OUTPUT);
  pinMode(Motor3_In1, OUTPUT);
  pinMode(Motor3_In2, OUTPUT);
  pinMode(Motor4_In1, OUTPUT);
  pinMode(Motor4_In2, OUTPUT);

  digitalWrite(ENA_NEG_PIN, HIGH); // LOW usually enables the TB6600, but HIGH does on ours!!
  digitalWrite(ENA_POS_PIN, HIGH);
  digitalWrite(DIR_POS_PIN, HIGH);
  digitalWrite(PUL_POS_PIN, HIGH);

  digitalWrite(PAINT_ENA_NEG_PIN, HIGH); // LOW usually enables the TB6600, but HIGH does on ours!!
  digitalWrite(PAINT_ENA_POS_PIN, HIGH);
  digitalWrite(PAINT_DIR_POS_PIN, HIGH);
  digitalWrite(PAINT_PUL_POS_PIN, HIGH);

  digitalWrite(LIMIT_GND_1_PIN, LOW);
  digitalWrite(LIMIT_GND_2_PIN, LOW);
}

void receiveData(int byteCount) {

  while (Wire.available()) {

    char command = Wire.read();  // Read the incoming byte

    if (command == 'S') {
      Serial.println("Stop command received");
      drive(STOP, 0, 0);
      robot_state = CALIBRATING;
    } 
    else if (command == 'F') {
      Serial.println("Forward command received");
      drive(FORWARD, 25, 0);
    }
    else if (command == 'P'){
      Serial.println("Paint command recieved");
      drive(INTO_WALL, 40, 50);
      robot_state = CALIBRATING;
    }
    else if (command == 'R'){
      Serial.println("Right adjustment recieved");
      drive(ROTATE_CW, 20, 0);
    }
    else if (command == 'L'){
      Serial.println("Left adjustment recieved");
      drive(ROTATE_CCW, 20, 0);
    }
  }
}

