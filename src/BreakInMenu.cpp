#include <Input.h>
#include <Motors.h>
#include <Utils.h>
#include <Screens.h>

#include "Screen.cpp"

class BreakInMenu : public Screen
{
private:
  int selectedItem = 0;
  int curSelectedItem = -1;
  bool init = false;
  String items[3] = {"Reverse", "Program", "< Back"};

public:
  BreakInMenu() : Screen()
  {
  }

  void reset() {
    init = false;
    selectedItem = 0;
    curSelectedItem = -1;
  }

  int draw() override
  {
    if (!init)
    {
      init = true;
      clearScreen();
      writeSmall(0, 0, "Break In Menu", YELLOW);
    }

    if (wasButton1Pressed()) {
      if (selectedItem == 0) {
        toggleMotorDirection();
      }
      if (selectedItem == 1) {
        return SCR_PROGRAM;
      }
      reset();
      return SCR_BREAKIN;
    }

    if (wasButton2Pressed()) {
      selectedItem++;
      if (selectedItem > 2) selectedItem = 0;
    }

    if (curSelectedItem == selectedItem) return SCR_BREAKIN_MENU;

    int y = 15;
    for (int i = 0; i < NUMITEMS(items); i++) {
      banner(String(items[i]), 0, y, 96, 12, 0,
        selectedItem == i ? BLACK : WHITE,
        selectedItem == i ? WHITE : BLACK);
      y += 10;
    }

    curSelectedItem = selectedItem;
    return SCR_BREAKIN_MENU;
  }
};
