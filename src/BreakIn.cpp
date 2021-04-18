#ifndef SCREEN_BREAKIN_H
#define SCREEN_BREAKIN_H

#include <Colors.h>
#include <Gfx.h>
#include <Input.h>
#include <Motors.h>
#include <Screens.h>
#include <Utils.h>

#include "Screen.cpp"

class BreakIn : public Screen {
  private:
    long curRpm = 0;
    long curClicks = 0;
    long prevRpm = -1;
    long prevClicks = -1;
    long startTime;
    long lastTime = 0;
    bool init = false;
    bool curMotorRunning = false;
    int curMotorSpeed = -1;
    bool curMotorDirection = MOTOR_BACKWARD;

  public:
    BreakIn() : Screen() {
      startTime = millis();
    }

    int updateMotorStatus() {
      curMotorRunning = isMotorRunning();
      curMotorDirection = getMotorDirection();
      curMotorSpeed = getMotorSpeed();

      if (isMotorRunning()) {
        banner("O=Pause", 2, 50, 46, 12, 1, DKGRAY, LTGRAY);
        banner("X=Stop", 49, 50, 45, 12, 1, DKGRAY, LTGRAY);
      } else {
        banner("O=Start", 2, 50, 46, 12, 1, DKGRAY, LTGRAY);
        banner("X=Back", 49, 50, 45, 12, 1, DKGRAY, LTGRAY);
      }
    }

    int draw() override {
      if (!init) {
        init = true;
        box(0, 0, 96, 64, WHITE);
      }

      if (curMotorRunning != isMotorRunning()
          || curMotorDirection != getMotorDirection()
          || curMotorSpeed != getMotorSpeed()) {
        updateMotorStatus();
      }

      curRpm = getRpm();
      curClicks = getClicks();

      if (curRpm != prevRpm) {
        prevRpm = curRpm;
        char rpm[5];
        sprintf(rpm, "%lu", curRpm);
        banner(rpm, 9, 4, 30, 12, 1, WHITE, RED);
      }

      if (curClicks != prevClicks) {
        prevClicks = curClicks;
        char clicks[6];
        sprintf(clicks, "%lu", curClicks);
        banner(clicks, 45, 4, 45, 12, 1, BLACK, YELLOW);
      }

      if (millis() - lastTime > 1000) {
        lastTime = millis();
        banner(formatMillis(millis() - startTime), 5, 25, 86, 12, 0, YELLOW, BLACK);
      }

      return SCR_BREAKIN;
    }
};
#endif
