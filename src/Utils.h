#include <Arduino.h>

#define NUMITEMS(arg) (sizeof(arg) / sizeof(arg[0]))

String formatMillis(long millis);
