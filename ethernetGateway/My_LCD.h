#ifndef MY_LCD_H
#define MY_LCD_H
#include <Wire.h>
//Using the Newliquidcrystal_1.3.5 library
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Ethernet.h>
#include "Defines.h"
#include "Debug.h"

void setupLCD(const uint8_t width,const uint8_t height);
void printLine(const uint8_t line, const String& content);
void printLine(const uint8_t line,const IPAddress& ip);
void printLCD(const String& content);
void printLCD(const uint8_t content);
void clearLCD();
void switchBacklight();
void setBacklight(bool state);

#endif
