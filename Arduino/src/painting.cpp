#include <AccelStepper.h>
#include <EEPROM.h>
#include <Wire.h>

#include "globals.h"
#include "driving.h"
#include "calibration.h"
#include "painting.h"

void paint() {
    drive(INTO_WALL, 40, 55); // Start painting
}
