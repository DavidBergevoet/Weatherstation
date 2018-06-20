#include "My_LCD.h"
LiquidCrystal_I2C  lcd = LiquidCrystal_I2C(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
uint8_t LCDCurrentBacklightState;
uint8_t LCDwidth;
uint8_t LCDheight;

void setupLCD(const uint8_t width, const uint8_t height) {
  LCDwidth=width;
  LCDheight=height;  
  LCDCurrentBacklightState=LCD_BACKLIGHT_START;
  lcd.begin(width, height);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(LCD_BACKLIGHT_START);
  lcd.home();
  lcd.print(F(LCD_STARTMESSAGE));
  debugln(F("LCD Setup Complete"));
}
void printLine(const uint8_t line, const String& content) {
  lcd.setCursor(0, line);
  //Clear the line for the message
  for (uint8_t i = 0; i <  LCDwidth; ++i) {
    lcd.print(" ");
  }
  lcd.setCursor(0,line);
  lcd.print(content);
}

void printLine(const uint8_t line,const IPAddress& ip){
  lcd.setCursor(0,line);
  for(uint8_t i=0;i<LCDwidth;++i){
    lcd.print(" ");
  }
  lcd.setCursor(0,line);
  lcd.print(ip);
}

void printLCD(const String& content){
  lcd.print(content);
}
void printLCD(const uint8_t content){
  lcd.print(content);
}

void clearLCD(){
  lcd.clear();
}

void switchBacklight() {
  if ( LCDCurrentBacklightState == HIGH) {
    LCDCurrentBacklightState = LOW;
  } else {
    LCDCurrentBacklightState = HIGH;
  }
  lcd.setBacklight(LCDCurrentBacklightState);
}

