//The includes/libraries
#include "Defines.h"
#include <MySensors.h>
#include "ClientPrint.h"
#include "ParseHTTP.h"
#include "My_LCD.h"

//Global classes
EthernetClient client;
MyMessage msg(MY_MESSAGE_STANDARD);

//Timers
uint32_t requestTimer = 0;
uint32_t Time = 0;
uint32_t previousInterrupt = 0;

//Routing variables
uint8_t connectedNodes[NR_OF_NODES];
bool messagesSend[NR_OF_NODES];
bool messagesReceived[NR_OF_NODES];

//Switching variables
bool backlightSwitch = false;
bool checked = false;

//Authentication to the server
const String loginInfo = "username=" USERNAME "&password=" PASSWORD;

void setup()
{
  setupLCD(LCD_WIDTH, LCD_HEIGHT);
  byte mac[] = {MAC_ADDRESS};
  Ethernet.begin(mac);
  debug(F("My IP-Adress is: ")); debugln(Ethernet.localIP());
  printLine(0, Ethernet.localIP());
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), interrupt, RISING);
}

void interrupt() {
  if (millis() - previousInterrupt >= INTERRUPT_DELAY) {
    debugln(F("INTERRUPT"));
    previousInterrupt = millis();
    backlightSwitch = true;
  }
}

void loop()
{
  Time = millis();
  if ((Time - requestTimer) % (MULTIPLIER * CHECK_DELAY) == 0 && Time - requestTimer < MULTIPLIER * REQUEST_DELAY && !checked) {
    checked = true;
    debugln(F("Check for messages"));
    for (uint8_t i = 0; i < NR_OF_NODES; ++i) {
      if (messagesSend[connectedNodes[i]] && !messagesReceived[connectedNodes[i]]) {
        debug(F("Send to node id "));
        debugln(connectedNodes[i]);
        send(msg.setDestination(connectedNodes[i]).setSensor(BROADCAST_MESSAGE));
      }
    }
  }
  if ((Time - requestTimer) % (MULTIPLIER * CHECK_DELAY) != 0) {
    checked = false;
  }
  if (millis() - requestTimer >= MULTIPLIER * REQUEST_DELAY) {
    requestTimer = Time;
    debugln(F("Sending messages"));
    for (uint8_t i = 0; i < NR_OF_NODES; ++i) {
      if (connectedNodes[i] != 0) {
        msg.setDestination(connectedNodes[i]);
        msg.setSensor(BROADCAST_MESSAGE);

        debug(F("Send request to: "));
        debugln(connectedNodes[i]);
        send(msg);
        messagesSend[connectedNodes[i]] = true;
        messagesReceived[connectedNodes[i]] = false;
      }
    }
  }
  if (backlightSwitch) {
    backlightSwitch = false;
    switchBacklight();
  }
  if (Time >= MAX_MILLIS_VALUE) {
    clearLCD();
    setBacklight(true);
    printLine(0, RESET_MESSAGE);
    while (true){
      setBacklight(false);
      delay(1000);
      setBacklight(true);
      delay(1000);
    }
  }
}
void receive(const MyMessage &message) {
  switch (message.sensor) {
    case TEMP_MESSAGE:
      {
        String id;
        String temp;
        String nodeId = String(message.getString()[0]);
        debug(F("Received from "));
        debugln(nodeId.toInt());
        messagesReceived[nodeId.toInt()] = true;
        messagesSend[nodeId.toInt()] = false;
        for (uint8_t i = 1; i < String(message.getString()).length(); ++i) {
          if (String(message.getString()).charAt(i) == DELIMITER) {
            id = temp;
            temp = "";
          } else {
            temp += String(message.getString()).charAt(i);
          }
        }
        if (isValidNumber(temp)) {
          debug(F("Write temperature to site From id: "));
          debugln(id);
          printLine(0, F("N: "));
          printLCD(nodeId);
          printLCD(F(" T: "));
          printLCD(temp);
          String returnCode = printUrlenCoded(&client, loginInfo + "&id=" + id +  "&temp=" + temp);
          printLine(1, returnCode);
        } else {
          debug(F("Temp isnt valid: "));
          debugln(temp);
          printLine(1, String(temp) + " isn't valid");
        }
        break;
      }
    case CONNECT_MESSAGE:
      {
        if (message.getInt() < NR_OF_NODES) {
          connectedNodes[message.getInt()] = message.getInt();
          debug(F("Connected to "));
          debugln(message.getInt());
          printLine(1, F("Connected to "));
          printLCD(message.getInt());
        }
        break;
      }
  }
}

