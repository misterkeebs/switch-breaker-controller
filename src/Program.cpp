#include <Arduino.h>
#include <Motors.h>
#include <Switch.h>
#include <Utils.h>

int cyclePresses = 0;
long programStarted = -1;
String message;

String getMessage() {
  return message;
}

void setMessage(String msg) {
  message = msg;
}

bool isProgrammed() {
  return cyclePresses > 0;
}

void startProgram(int size) {
  resetClicks();
  programStarted = millis();
  cyclePresses = size;
  startMotor();
}

void pauseProgram() {
  stopMotor();
}

void resumeProgram() {
  startMotor();
}

void stopProgram() {
  stopMotor();
  resetClicks();
  programStarted = -1;
  cyclePresses = 0;
}

int getCyclePresses() {
  return cyclePresses;
}

String getFormattedCycleDuration() {
  if (!isProgrammed()) return "";
  return formatMillis(millis() - programStarted);
}

long getCycleDuration() {
  if (!isProgrammed()) return -1;
  return millis() - programStarted;
}

void checkProgram() {
  if (!isProgrammed()) return;
  if (!isMotorRunning()) return;

  int curPresses = getClicks();
  if (curPresses >= cyclePresses) {
    String message = "Program of ";
    message += cyclePresses;
    message += " presses finished in ";
    message += formatMillis(getCycleDuration());
    setMessage(message);
    programStarted = -1;
    cyclePresses = 0;
    stopMotor();
  }
}
