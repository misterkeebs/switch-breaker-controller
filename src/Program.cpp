#ifndef SCREEN_PROGRAM_H
#define SCREEN_PROGRAM_H

#include <Colors.h>
#include <Gfx.h>
#include <Input.h>
#include <Motors.h>
#include <Screens.h>
#include <Utils.h>

#include "Screen.cpp"

class Program : public Screen {
  private:
    bool init = false;
    int cycleAmount = 0;
    int curCycleAmount = -1;
    int curPotReading = -1;
  public:
    Program() : Screen() {
    }

    void reset() {
      init = false;
      cycleAmount = 0;
      curCycleAmount = -1;
      curPotReading = -1;
    }

    int draw() override {
      if (!init) {
        clearScreen();
        box(0, 0, 96, 64, WHITE);

        init = true;
        banner("O=Accpt", 2, 50, 46, 12, 1, DKGRAY, LTGRAY);
        banner("X=Back", 49, 50, 45, 12, 1, DKGRAY, LTGRAY);

        banner("Cycle length:", 5, 5, 86, 12, 0, YELLOW, BLACK);
        banner("x1000", 45, 25, 40, 12, 0, WHITE, BLACK);
      }

      if (wasButton2Pressed()) {
        reset();
        return SCR_BREAKIN;
      }

      if (wasButton1Pressed()) {
        setProgramCycle(cycleAmount * 1000);
        reset();
        return SCR_BREAKIN;
      }

      if (curPotReading != getPotReading()) {
        curPotReading = getPotReading();
        cycleAmount = map(curPotReading, 0, PWMRANGE, 0, 200);
      }

      if (curCycleAmount != cycleAmount) {
        curCycleAmount = cycleAmount;
        char amount[3];
        sprintf(amount, "%lu", cycleAmount);
        banner(amount, 15, 25, 30, 12, 1, WHITE, RED);
      }

      return SCR_PROGRAM;
    }
};

#endif
