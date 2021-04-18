#ifndef SCREEN_LOGO_H
#define SCREEN_LOGO_H

#include <Arduino.h>
#include <Colors.h>
#include <Gfx.h>

#include <Screens.h>

#include "Screen.cpp"

class LogoScreen : public Screen {
  public:
    LogoScreen() : Screen() {

    }

    int draw() override {
      displayLogo();
      return SCR_MAINMENU;
    }
};

#endif
