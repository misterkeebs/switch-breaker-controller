#include <Arduino.h>

#define NUMITEMS(arg) (sizeof(arg) / sizeof(arg[0]))

int displayMessage(String message, int returnTo);
String getMessage();
int getReturnTo();
String formatMillis(long millis);
