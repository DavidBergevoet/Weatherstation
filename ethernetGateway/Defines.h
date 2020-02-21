#ifndef DEFINES_H
#define DEFINES_H
// Enable debug prints to serial monitor
//-----------------MY SENSORS DEBUG
//#define MY_DEBUG
//-----------------USER DEBUG
//#define DEBUG_MODE

// Enable and select radio type attached
#define MY_RADIO_RF24

// Set LOW transmit power level as default, if you have an amplified NRF-module and
// power your radio separately with a good regulator you can turn up PA level.
#define MY_RF24_PA_LEVEL RF24_PA_MAX
#define MY_RF24_CHANNEL 4

// Enable serial gateway
#define MY_GATEWAY_SERIAL

// Enable Soft SPI for NRF radio (note different radio wiring is required)
// The W5100 ethernet module seems to have a hard time co-operate with
// radio on the same spi bus.
#define MY_SOFTSPI
#define MY_SOFT_SPI_SCK_PIN 14
#define MY_SOFT_SPI_MISO_PIN 16
#define MY_SOFT_SPI_MOSI_PIN 15

// When W5100 is connected we have to move CE/CSN pins for NRF radio
#define MY_RF24_CE_PIN 5
#define MY_RF24_CS_PIN 6

#define MY_MESSAGE_STANDARD 1,1
#define DELIMITER '|'

enum MESSAGE_TYPES {TEMP_MESSAGE = 'T', CONNECT_MESSAGE = 'A',BROADCAST_MESSAGE = 'R'};

//Timers defines
#define REQUEST_DELAY uint32_t(10)
#define CHECK_DELAY uint32_t(1)
#define NR_OF_NODES 5
#define MULTIPLIER uint32_t(60000)
#define MAX_MILLIS_VALUE 4294967200

//INTERRUPTS
#define INTERRUPT_DELAY 1000
#define INTERRUPT_PIN 2


//LCD Defines
#define LCD_WIDTH 16
#define LCD_HEIGHT 2
#define RESET_MESSAGE "PLEASE PRESS BUTTON"


#define I2C_ADDR    0x27 
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define LCD_STARTMESSAGE "SETUP COMPLETE"
#define LCD_BACKLIGHT_START HIGH

//CLIENTPRINT Defines
#define MAC_ADDRESS 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
#define USERNAME "Bergevoet"
#define PASSWORD "Benji#123"
#define SERVER "dbergevoet.nl"
#define PORT 80
#define WEATHERSTATION_TARGET "/api/weerstation"
#define TIME_TARGET "/api/tijd"
#define CONTENT_TYPE "Content-Type: application/x-www-form-urlencoded"
#define RECEIVE_DELAY 750
#define GET_SERVER_TIME_ERROR F("-1")

#endif
