#include "calibration.h"
#include <AccelStepper.h>
#include <EEPROM.h>
#include "globals.h"

void calibrate() {

    // If zeroing button is pushsed on start-up, enter manual zeroing mode. Otherwise, use location from EEPROM.
    if (ZERO_BUTTON == PUSHED) {
      // Manual zeroing
      stepper.setSpeed(-DEFAULT_SPEED);
      while (ZERO_BUTTON == PUSHED)
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
      while (HORZ_LIMIT == NOT_PUSHED)
      {
      angle++;
      analogWrite(SERVO, angle);
      delay(100);
      }
      angle--;
      analogWrite(SERVO, angle);
      delay(500);
      if (HORZ_LIMIT == PUSHED)
      {
        break;
      }
    }
  
    // TODO: Convert angle to wall distance
  
    // Move back down until other limit switch hit
    stepper.setSpeed(-100);
    while (NOT_PUSHED)
    {
      stepper.runSpeed();
    }
    
  
    
    
    
  
    
  
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

