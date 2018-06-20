#ifndef CLIENTPRINT_H
#define CLIENTPRINT_H

#include "ParseHTTP.h"
#include "Defines.h"
#include <Debug.h>

String printUrlenCoded(EthernetClient* clnt, const String& content);

String getServerTime(EthernetClient*clnt, const String& loginInfo);

#endif
