#ifndef SCREENS_H
#define SCREENS_H

#include <Arduino.h>
#include <Screen.cpp>

#define SCR_LOGO 1
#define SCR_MAINMENU 2

Screen* getScreen(int id);

#endif
