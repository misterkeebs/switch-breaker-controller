#ifndef SCREEN_MAINMENU_H
#define SCREEN_MAINMENU_H

#include <Arduino.h>
#include <Colors.h>
#include <Gfx.h>
#include <Input.h>

#include <Screens.h>

#include "Screen.cpp"

class MainMenu : public Screen {
  private:
    int curItem;
    int lastCurItem;

  public:
    MainMenu() : Screen() {
      curItem = 0;
      lastCurItem = -1;
    }

    int draw() override {
      if (wasButton1Pressed()) {
        Serial.println("Button 1 pressed");
        curItem++;
      }

      if (curItem != lastCurItem) {
        lastCurItem = curItem;
        String msg = "Item: ";
        msg += curItem;

        banner(msg, 0, 0, 96, 12, 0, BLACK, WHITE);

        if (curItem > 2) {
          curItem = 0;
          return SCR_LOGO;
        }
      }

      return SCR_MAINMENU;
    }
};
#endif
