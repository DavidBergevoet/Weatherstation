#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include <Arduino.h>
#include "Defines.h"
#include "Debug.h"
#include <DHT.h>

void setupSensor(uint8_t aTempPin, uint8_t dhtPin);

float readTemp();

float getAvgTemp();

void resetAvg();

float readTempWithDelay();

float getHumidity();


#endif
