#ifndef globals_h
#define globals_h

// Global Variables and Objects

// Declare the stepper object as extern so it can be accessed from the main file
extern AccelStepper stepper;

// Define pin connections

#define ENA_NEG_PIN 22
#define ENA_POS_PIN 24
#define DIR_NEG_PIN 26
#define DIR_POS_PIN 28
#define PUL_NEG_PIN 30
#define PUL_POS_PIN 32

#define LIMIT_GND_1_PIN 34
#define HORZ_LIMIT_PIN 36               //
#define VERT_LIMIT_PIN 38               //
#define LIMIT_GND_2_PIN 40
#define ZERO_BUTTON_PIN 42              //
#define SERVO_PIN 44                    //

// Other definitions for constants 
#define EEPROM_POSITION_ADDR 0      //
#define MAX_STEPPER_POSITION 80000   //
#define MIN_SERVO_ANGLE 58          //
#define MAX_SERVO_ANGLE 255         //
#define DEFAULT_SPEED 1000

// Assuming that push buttons are pulled up
#define PUSHED 0
#define NOT_PUSHED 1

#define TOP_POSITION 2000
#define SERVO_DELAY 20
#define SERVO_BACK_DELAY 500

#endif