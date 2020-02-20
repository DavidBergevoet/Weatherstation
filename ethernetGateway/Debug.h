#ifndef DEBUG_H_
#define DEBUG_H_


#ifdef DEBUG_MODE

#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)

#else

#define debug(x)
#define debugln(x)

#endif DEBUG_MODE

#endif //DEBUG_H_
