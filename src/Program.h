#include <Arduino.h>

bool isProgrammed();
void startProgram(int size);
void pauseProgram();
void resumeProgram();
void stopProgram();
int getCyclePresses();
String getFormattedCycleDuration();
long getCycleDuration();
void checkProgram();
