#include "Defines.h"
#include <MySensors.h>
#include "WeatherStation.h"
#include <Debug.h>

MyMessage msg(MY_MESSAGE_STANDARD_VALUES);

void setup() {
  setupSensor(TEMP_PIN);
  readTemp();
  delay(INIT_DELAY);//This delay is for setup for MySensors

  msg.setSensor(CONNECT_CHAR);
  unsigned short nodeId = MY_NODE_ID;
  debugln(nodeId);
  send(msg.set(MY_NODE_ID));
  debugln(msg.getString());
  debugln(F("-----------------"));
}

void loop()
{
  readTempWithDelay();
}

void receive(const MyMessage &message) {
  debug(F("Sensor: "));
  debugln(char(message.sensor));
  debug(F("Message: "));
  debugln(message.getString());
  if (char(message.sensor) == BROADCAST_CHAR) {
    msg.setSensor(SEND_TEMP_CHAR);
    String message = String(MY_NODE_ID) + ID DELIMITER + String(getAvgTemp());
    char messageArr[message.length()];
    message.toCharArray(messageArr, message.length());
    msg.set(messageArr);
    resetAvg();
    send(msg);
    delay(SEND_MESSAGE_DELAY);
  }
}



