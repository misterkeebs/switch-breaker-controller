#include <Arduino.h>

#include <Screens.h>
#include <Screen.cpp>

#include <LogoScreen.cpp>
#include <MainMenu.cpp>
#include <BreakIn.cpp>

LogoScreen logo{};
MainMenu mainMenu{};
BreakIn breakIn{};

Screen* getScreen(int id) {
  if (id == SCR_LOGO) {
    Serial.println("Returning logo...");
    return &logo;
  }
  if (id == SCR_MAINMENU) {
    Serial.println("Returning MainMenu...");
    return &mainMenu;
  }
  if (id == SCR_BREAKIN) {
    return &breakIn;
  }
}
