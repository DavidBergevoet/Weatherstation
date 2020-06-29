#include "ClientPrint.h"

void printHeader(EthernetClient* clnt, const uint8_t cLength, const String& target) {
  clnt->print(F("POST "));clnt->print(target); clnt->println(F(" HTTP/1.1"));
  clnt->print(F("Host: "));clnt->println(F(SERVER));
  clnt->println(F(CONTENT_TYPE));
  clnt->print(F("Content-length: "));
  clnt->println(cLength);
  clnt->println();
}

String printUrlenCoded(EthernetClient* clnt, const String& content,const String& target) {
  if (clnt->connect(SERVER, PORT)) {
    unsigned short cLength = content.length();
    printHeader(clnt, cLength,target);
    clnt->print(content);
    delay(RECEIVE_DELAY);
    String temp;
    uint8_t counter=0;
    while (clnt->available()&& counter <12) {
      counter++;
      char c = clnt->read();
      debug(c);
      if (c != '\r') {
        temp += c;
      } else {
        break;
      }
    }
    debugln();
    clnt->stop();
    if(counter==0){
      return F("NO RESPONSE");
    }
    debugln(temp);
    return temp;
  }
  return F("Cant connect");
}

String getServerTime(EthernetClient* clnt, const String& loginInfo) {
  unsigned short cLength = loginInfo.length();

  clnt->print(F("POST http://"));
  clnt->print(F(SERVER));
  clnt->print(F(TIME_TARGET));
  clnt->println(F(" HTTP/1.1"));
  clnt->println(F(CONTENT_TYPE));
  clnt->print(F("Content-Length: "));
  clnt->println(String(cLength));
  clnt->println();
  clnt->print(loginInfo);
  delay(RECEIVE_DELAY);

  String body = getBody(clnt);
  String temp;
  for (int i = body.indexOf('"') + 1; i < body.length(); ++i) {
    if (body.charAt(i) == '"') {
      clnt->stop();
      return temp;
    } else {
      temp += body.charAt(i);
    }
  }
  return GET_SERVER_TIME_ERROR;
}
