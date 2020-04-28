#include "WeatherStation.h"

unsigned long  _tempTimer = 0;

uint8_t tempPin = 0;

float temp = 0;
unsigned long long nrOfReadings = 0;

void setupSensor(uint8_t aTempPin) {
  tempPin = aTempPin;
}

float readTemp() {
  uint16_t rawTempRead = analogRead(tempPin);
  float Temp;
  float Rparallel = 10000;
  float coefficientA = 0.001129148;
  float coefficientB = 0.000234125;
  float coefficientC = 0.0000000876741;

  Temp = log(((1024 * Rparallel / rawTempRead) - Rparallel));
  Temp = 1 / (coefficientA + (coefficientB * Temp) + (coefficientC * Temp * Temp * Temp));

  float TempCelcius = Temp - 273.15 + CORRECTION;
  if(nrOfReadings < 10000)
  {
    temp += TempCelcius;
    nrOfReadings++;
  }
  return TempCelcius;
}

float getAvgTemp() {
  float avg = temp / nrOfReadings;
  return avg;
}

void resetAvg() {
  temp = 0;
  nrOfReadings = 0;
}

float readTempWithDelay() {
  if (millis() - _tempTimer >= _TEMP_DELAY) {
    _tempTimer = millis();
    debugln(F("Read the temperature"));
    float temp = readTemp();
    debugln(temp);
    return temp;
  }
}
