#include "ParseHTTP.h"

//PARSEMETHODS  ------------------------------------------------------------


String getBody(EthernetClient* clnt) {
  char temp;
  while (true) {
    temp = clnt->read();
    if (temp == '\n') {
      temp = clnt->read();
      if (temp == '\r') {
        String tempString;
        clnt->read();
        while (true) {
          temp = clnt->read();
          if (temp != -1) {
            tempString += temp;
          } else {
            return tempString;
          }
        }
      }
    }
  }
}

bool isValidNumber(const String& str) {
  String tempString=str;
  tempString.remove(tempString.indexOf('.'),1);
  debug(F("Tempstring: -"));
  debug(tempString);
  debugln(F("-"));
  for (uint8_t i = 0; i < tempString.length(); i++)
  {
    if (!isDigit(tempString.charAt(i)) && tempString.charAt(i)!= '-') return false;
  }
  return true;
}
