#ifndef globals_h
#define globals_h

// Global Variables and Objects

// Declare the stepper object as extern so it can be accessed from the main file
extern AccelStepper stepper;

// Define pin connections
#define STEP_PIN 3                  // Connect to PUL-
#define DIR_PIN 2                   // Connect to DIR-
#define VERT_LIMIT 30               // 
#define HORZ_LIMIT 32               //
#define ZERO_BUTTON 31              //
#define SERVO 25                    //

// Other definitions for constants 
#define EEPROM_POSITION_ADDR 0      //
#define MAX_STEPPER_POSITION 2000   //
#define MIN_SERVO_ANGLE 50          //
#define MAX_SERVO_ANGLE 205         //
#define DEFAULT_SPEED 100

// Assuming that push buttons are pulled up
#define PUSHED 0
#define NOT_PUSHED 1



#endif