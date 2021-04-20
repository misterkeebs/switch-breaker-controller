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
    long runningTime = 0;
    long elapsed;
    long lastCycle = 0;
    int curPotReading = -1;

  public:
    BreakIn() : Screen() {
      startTime = millis();
      lastCycle = millis();
    }

    int updateMotorStatus() {
      curMotorRunning = isMotorRunning();
      curMotorDirection = getMotorDirection();
      curMotorSpeed = getMotorSpeed();

      String info = curMotorDirection ? ">" : "<";
      info += " ";
      info += curMotorSpeed;

      banner(info, 5, 20, 86, 12, 0, YELLOW, BLACK);

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

      if (wasButton1Pressed()) {
        toggleMotor();
      }

      if (curPotReading != getPotReading()) {
        curPotReading = getPotReading();
        setMotorSpeed(map(curPotReading, 0, PWMRANGE, 0, 10));
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

      if (isMotorRunning()) {
        elapsed = millis() - lastCycle;
        runningTime += elapsed;
      }

      if (millis() - lastTime > 1000) {
        lastTime = millis();
        banner(formatMillis(runningTime), 5, 30, 86, 12, 0, YELLOW, BLACK);
      }

      lastCycle = millis();
      return SCR_BREAKIN;
    }
};
#endif
