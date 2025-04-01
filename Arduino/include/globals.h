#ifndef globals_h
#define globals_h

#include <AccelStepper.h>
#include <Servo.h>

// Define the robot states enum
enum ROBOT_STATES {DRIVING, CALIBRATING, PAINTING, STOPPED};

// Define movement states using an enum
enum MOVEMENT_STATES {
    STOP,
    FORWARD,
    BACKWARD,
    INTO_WALL,
    ROTATE_CW,
    ROTATE_CCW
};

// Declare the stepper object and robot state as extern so they can be accessed from other files
extern AccelStepper stepper;
extern AccelStepper paintStepper;
extern ROBOT_STATES robot_state;
extern Servo myservo;

// Define pin connections
#define UNO_ADDR 29  // Same I2C address used in Raspberry Pi code

#define ENA_NEG_PIN 22
#define ENA_POS_PIN 24
#define DIR_NEG_PIN 26
#define DIR_POS_PIN 28
#define PUL_NEG_PIN 30
#define PUL_POS_PIN 32

#define PAINT_ENA_NEG_PIN 23
#define PAINT_ENA_POS_PIN 25
#define PAINT_DIR_NEG_PIN 27
#define PAINT_DIR_POS_PIN 29
#define PAINT_PUL_NEG_PIN 31
#define PAINT_PUL_POS_PIN 33

#define LIMIT_GND_1_PIN 34
#define HORZ_LIMIT_PIN 36
#define VERT_LIMIT_PIN 38
#define LIMIT_GND_2_PIN 40
#define ZERO_BUTTON_PIN 42
#define SERVO_PIN 10

#define Motor1_In1 8 // motor 1
#define Motor1_In2 9 // motor 1
#define Motor2_In1 2 // motor 2
#define Motor2_In2 3 // motor 2
#define Motor3_In1 5 // motor 3
#define Motor3_In2 6 // motor 3
#define Motor4_In1 11 // motor 4
#define Motor4_In2 12 // motor 4

// Define constants for the stepper motor
#define MAX_SPEED 100000
#define MAX_ACCELERATION 500
#define SET_SPEED 2000

//***********************************************************************
#define PAINT_OFFSET 10000 // Offset for the linear actuator

// Other definitions for constants
#define EEPROM_POSITION_ADDR 0
#define MAX_STEPPER_POSITION 80000
#define MIN_SERVO_ANGLE 0 // Retracted state
#define MAX_SERVO_ANGLE 168
#define SERVO_DELAY 20
#define SERVO_BACK_DELAY 500

// Assuming that push buttons are pulled up
#define PUSHED 0
#define NOT_PUSHED 1

#endif