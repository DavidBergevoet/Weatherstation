#include "Defines.h"
#include <MySensors.h>
#include "WeatherStation.h"
#include "Debug.h"

MyMessage connect_msg(MY_MESSAGE_STANDARD_VALUES);
MyMessage msg(MY_MESSAGE_STANDARD_VALUES);

void setup() {
  setupSensor(TEMP_PIN);
  readTemp();
  delay(INIT_DELAY);//This delay is for setup for MySensors

  connect_msg.setSensor(CONNECT_CHAR);
  unsigned short nodeId = MY_NODE_ID;
  debugln(nodeId);
  send(connect_msg.set(MY_NODE_ID));
  debugln(connect_msg.getString());
  debugln(F("-----------------"));
}

void loop()
{
  readTempWithDelay();
  if(millis()%CONNECT_DELAY==0){
    send(connect_msg);
  }
}

void receive(const MyMessage &message) {
  debug(F("Sensor: "));
  debugln(char(message.sensor));
  debug(F("Message: "));
  debugln(message.getString());
  if (char(message.sensor) == BROADCAST_CHAR) {
    msg.setSensor(SEND_TEMP_CHAR);
    String message = String(MY_NODE_ID) + ID DELIMITER + String(getAvgTemp());
    debug(F("Message:"));
    debugln(message);
    char messageArr[message.length()];
    message.toCharArray(messageArr, message.length());
    msg.set(messageArr);
    resetAvg();
    send(msg);
    delay(SEND_MESSAGE_DELAY);
  }
}
