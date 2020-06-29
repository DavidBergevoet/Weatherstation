#ifndef CLIENTPRINT_H
#define CLIENTPRINT_H

#include "ParseHTTP.h"
#include "Defines.h"
#include "Debug.h"

String printUrlenCoded(EthernetClient* clnt, const String& content,const String& target);

String getServerTime(EthernetClient*clnt, const String& loginInfo);

#endif
