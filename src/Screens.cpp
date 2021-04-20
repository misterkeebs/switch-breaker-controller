#include <Arduino.h>

#include <Screens.h>
#include <Screen.cpp>

#include <LogoScreen.cpp>
#include <BreakIn.cpp>
#include <BreakInMenu.cpp>

LogoScreen logo{};
BreakIn breakIn{};
BreakInMenu breakInMenu{};

Screen* getScreen(int id) {
  if (id == SCR_LOGO) {
    Serial.println("Returning logo...");
    return &logo;
  }
  if (id == SCR_BREAKIN) {
    return &breakIn;
  }
  if (id == SCR_BREAKIN_MENU) {
    return &breakInMenu;
  }
}
