#include <Arduino.h>
#include <Motors.h>
#include <Pinout.h>
#include <Switch.h>
#include <WebServer.h>

#define SWITCH_DEBOUNCE 100

int switchReading;
int curSwitchReading;
long switchLastTime = 0;
long clickCounter = 0;
long intervalClickCounter = 0;
long rpmCounter = 0;
long rpmLastTime = 0;
bool countingClicks = false;

void startCountingClicks() {
  countingClicks = true;
}

void stopCountingClicks() {
  countingClicks = false;
}

void setCountingClicks(bool enabled) {
  countingClicks = enabled;
}

void checkSwitch() {
  switchReading = digitalRead(SWITCH);
  if (curSwitchReading != switchReading) {
    curSwitchReading = switchReading;
    if (switchReading == LOW && millis() - switchLastTime > SWITCH_DEBOUNCE) {
      clickCounter += 1;
      intervalClickCounter += 1;
      switchLastTime = millis();
      Serial.print("MX Pressed ");
      Serial.println(clickCounter);
      notifyClient();
    }
  }
  updateRpm();
}

long getRpm() {
  return rpmCounter;
}

void updateRpm() {
  if (millis() - rpmLastTime > 1000) {
    rpmCounter = intervalClickCounter / 2 * 60;
    resetIntervalClicks();
    rpmLastTime = millis();
  }
}

long getClicks() {
  return clickCounter;
}

void resetClicks() {
  clickCounter = 0;
}

long getIntervalClicks() {
  return intervalClickCounter;
}

void resetIntervalClicks() {
  intervalClickCounter = 0;
}
