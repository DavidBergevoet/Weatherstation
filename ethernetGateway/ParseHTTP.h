#ifndef PARSEHTTP_H
#define PARSEHTTP_H

#include <avr/pgmspace.h>
#include <SPI.h>
#include <Ethernet.h>
#include "Defines.h"
#include <Debug.h>

//PARSEMETHODS  ------------------------------------------------------------
String getBody(EthernetClient* client);

bool isValidNumber(const String& str);

#endif
