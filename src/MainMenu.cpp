#ifndef SCREEN_MAINMENU_H
#define SCREEN_MAINMENU_H

#include <Arduino.h>
#include <Colors.h>
#include <Gfx.h>
#include <Input.h>

#include <Screens.h>

#include "Screen.cpp"

#define NUMITEMS(arg) (sizeof(arg) / sizeof(arg[0]))

class MainMenu : public Screen {
  private:
    int curItem;
    int prevItem;
    int lastItem;
    String menuItems[3] = { "Break In", "Setup", "About" };

  public:
    MainMenu() : Screen() {
      curItem = 0;
      prevItem = -1;
      lastItem = NUMITEMS(menuItems)-1;
    }

    int draw() override {
      if (wasButton2Pressed()) {
        curItem++;
        if (curItem > lastItem) {
          curItem = 0;
        }
      }

      if (curItem != prevItem) {
        if (prevItem == -1) {
          clearScreen();
        }

        prevItem = curItem;
        String msg = "Item: ";
        msg += menuItems[curItem];

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
