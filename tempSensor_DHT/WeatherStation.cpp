#include "WeatherStation.h"

unsigned long  _tempTimer = 0;
unsigned long  _humTimer = 0;

uint8_t tempPin = 0;

float temp = 0;
float hum=0;

DHT* _dht;
unsigned long long nrOfTempReadings = 0;
unsigned long long nrOfHumReadings = 0;

void setupSensor(uint8_t aTempPin,uint8_t dhtPin) {
  tempPin = aTempPin;
  _dht = new DHT(dhtPin,DHT_TYPE);
  _dht->begin();
  
}

float readTemp() {
  float nTemp = _dht->readTemperature();
  float nHum = _dht->readHumidity();
  if(isnan(nTemp) || isnan(nHum))
  {
    return 0;
  }
  float TempCelcius = _dht->computeHeatIndex(nTemp,nHum,false);
  if(nrOfTempReadings < 10000)
  {
    temp += TempCelcius;
    nrOfTempReadings++;
  }
  return TempCelcius;
}

float getAvgTemp() {
  float avg = temp / nrOfTempReadings;
  return avg;
}

float getAvgHum() {
  float avg = hum/nrOfHumReadings;
  return avg;
}

void resetAvg() {
  temp = 0;
  nrOfTempReadings = 0;
  hum=0;
  nrOfHumReadings = 0;
}

float getHumidity()
{
  float nHum = _dht->readHumidity();
  
  if(isnan(nHum)){
    return 0;
  }
  if(nrOfHumReadings < 10000)
  {
    hum += nHum;
    nrOfHumReadings++;
  }
  return nHum;
}

float readTempWithDelay() {
  if (millis() - _tempTimer >= _MEASURE_DELAY) {
    _tempTimer = millis();
    debugln(F("Read the temperature"));
    float temp = readTemp();
    debugln(temp);
    return temp;
  }
}

float readHumWithDelay() {
  if (millis()- _humTimer >= _MEASURE_DELAY) {
    _humTimer = millis();
    debugln(F("Read the humidity"));
    float hum = getHumidity();
    debugln(hum);
    return hum;
  }
}
