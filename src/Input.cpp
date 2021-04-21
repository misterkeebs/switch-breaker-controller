#include <Arduino.h>

#include <Gfx.h>
#include <Input.h>
#include <Menu.h>
#include <Pinout.h>
#include <Screens.h>

// button presses
int but1State = LOW;
int but1Reading;
int but1PrevState = HIGH;
long but1LastTime = 0;
int but2State = LOW;
int but2Reading;
int but2PrevState = HIGH;
long but2LastTime = 0;
int but1Pressed = 0;
int but2Pressed = 0;

bool was1Pressed = false;
bool was2Pressed = false;

int potReading = 0;
int curPotReading = -1;

int mxReading;
long mxLastTime = 0;
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
  if (!countingClicks) return;
  mxReading = digitalRead(MX_PIN);
  if (mxReading == LOW && millis() - mxLastTime > MX_DEBOUNCE) {
    Serial.println("MX Pressed");
    clickCounter += 1;
    intervalClickCounter += 1;
    mxLastTime = millis();
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

void checkPotentiometer() {
  potReading = analogRead(A0);
}

int getPotReading() {
  return potReading;
}

void checkButtons()
{
  but1Reading = digitalRead(BUT1);
  but2Reading = digitalRead(BUT2);

  if (but1Reading == LOW && but1PrevState == HIGH && millis() - but1LastTime > BUT_DEBOUNCE)
  {
    if (but1Reading == LOW)
    {
      but1State = HIGH;
      but1Pressed = 1;
    }
    else
    {
      but1State = LOW;
    }
    but1LastTime = millis();
  }

  if (but2Reading == LOW && but2PrevState == HIGH && millis() - but2LastTime > BUT_DEBOUNCE)
  {
    if (but2Reading == LOW)
    {
      but2State = HIGH;
      but2Pressed = 1;
    }
    else
    {
      but2State = LOW;
    }
    but2LastTime = millis();
  }

  if (but1Pressed == 1)
  {
    but1Pressed = 0;
    handleButton(1);
    return;
  }

  if (but2Pressed == 1)
  {
    but2Pressed = 0;
    handleButton(2);
    return;
  }
}

bool wasAnyPuttonPressed() {
  return wasButton1Pressed() || wasButton2Pressed();
}

bool wasButton1Pressed() {
  if (was1Pressed) {
    was1Pressed = false;
    return true;
  }
  return false;
};

bool wasButton2Pressed() {
  if (was2Pressed) {
    was2Pressed = false;
    return true;
  }
  return false;
};

void handleButton(int num) {
  if (num == 1) was1Pressed = true;
  if (num == 2) was2Pressed = true;
}
