#ifndef DEFINES_H
#define DEFINES_H
// Enable debug prints to serial monitor
#define MY_DEBUG
#define DEBUG_MODE
// Enable and select radio type attached
#define MY_RADIO_RF24
#define MY_NODE_ID 2
#define MY_RF24_PA_LEVEL RF24_PA_MAX
#define MY_RF24_CHANNEL 4

#define MY_MESSAGE_STANDARD_VALUES 1,1

#define INIT_DELAY 500
#define SEND_MESSAGE_DELAY 10
#define _TEMP_DELAY 5000

#define CONNECT_DELAY 180011

#define TEMP_PIN A0
#define DELIMITER "|"
enum MESSAGE_TYPES {BROADCAST_CHAR = 'R',SEND_TEMP_CHAR = 'T',CONNECT_CHAR = 'A'};

#define ID "Binnen"

#define CORRECTION -2

#endif
