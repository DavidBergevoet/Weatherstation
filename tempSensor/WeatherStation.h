#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include <Arduino.h>
#include "Defines.h"
#include "Debug.h"

void setupSensor(uint8_t aTempPin);

float readTemp();

float getAvgTemp();

void resetAvg();

float readTempWithDelay();


#endif
