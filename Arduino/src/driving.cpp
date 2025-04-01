#include <AccelStepper.h>
#include <EEPROM.h>

#include "globals.h"

#include "driving.h"
#include "calibration.h"
#include "painting.h"

void drive(int command, int speed_slower, int speed_faster)
{
    int pin1[4];
    int pin2[4];

    switch(command){
        case STOP:
            for (int i =0; i<4; i++){
                pin1[i] = 0;
                pin2[i] = 0;
            }
            
            break;
    
        case FORWARD:
            for (int i =0; i<2; i++){ //m1 and m2 go fwd
                pin1[i] = 0;
                pin2[i] = speed_slower;
            }
            for (int i=2; i<4; i++){  //m3 and m4 go fwd
                pin1[i] = speed_slower;
                pin2[i] = 0;
            }
            
            break;
        
        case BACKWARD:
            for (int i =0; i<2; i++){ //m1 and m2 go bck
                pin1[i] = speed_slower;
                pin2[i] = 0;
            }
            for (int i=2; i<4; i++){  //m3 and m4 go bck
                pin1[i] = 0;
                pin2[i] = speed_slower;
            }
            
            break;
        
        case INTO_WALL: 
        // 1 and 4 go backwards
        // 2 and 3 go fwd and faster
            
          pin1[0] = speed_slower;
          pin2[0] = 0;

          pin1[1] = 0;
          pin2[1] = speed_faster;

          pin1[2] = speed_faster;
          pin2[2] = 0;

          pin1[3] = 0;
          pin2[3] = speed_slower;

          break;


        case ROTATE_CW: 
        //1 and 2 go backwards
        //3 and 4 go forwards
            
            for (int i =0; i<4; i++){
            pin1[i] = speed_slower;
            pin2[i] = 0;
            }
            Serial.println("rotate_cw");
            break;
        
        case ROTATE_CCW: 
        //1 and 2 go forwards
        //3 and 4 go backwards
            for (int i =0; i<4; i++){
            pin1[i] = 0;
            pin2[i] = speed_slower;
            }
            
            break;
    }

    analogWrite(Motor1_In1, pin1[0]);
    analogWrite(Motor1_In2, pin2[0]);

    analogWrite(Motor2_In1, pin1[1]);
    analogWrite(Motor2_In2, pin2[1]);

    analogWrite(Motor3_In1, pin1[2]);
    analogWrite(Motor3_In2, pin2[2]);    

    analogWrite(Motor4_In1, pin1[3]);
    analogWrite(Motor4_In2, pin2[3]);

    //Serial.println("command"); 
}