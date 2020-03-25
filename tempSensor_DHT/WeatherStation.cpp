#include "WeatherStation.h"

unsigned long  _tempTimer = 0;

uint8_t tempPin = 0;

float temp = 0;

DHT* _dht;
unsigned long long nrOfReadings = 0;

void setupSensor(uint8_t aTempPin,uint8_t dhtPin) {
  tempPin = aTempPin;
  _dht = new DHT(dhtPin,DHT_TYPE);
  _dht->begin();
  
}

float readTemp() {
  float nTemp = _dht->readTemperature();
  float hum = _dht->readHumidity();
  if(isnan(nTemp) || isnan(hum))
  {
    return 0;
  }
  float TempCelcius = _dht->computeHeatIndex(nTemp,hum);
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

float getHumidity()
{
  return _dht->readHumidity();
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
