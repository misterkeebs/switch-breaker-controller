#include <Adafruit_SSD1331.h>

#include <Menu.h>
#include <Gfx.h>

#define NUMITEMS(arg) (sizeof(arg) / sizeof(arg[0]))

int activeItem = 0;
int curActiveItem = -1;
int curMenu = MENU_MAIN;

String menuItems[][3] = {
  { "Break In", "Setup", "About" },
  { "Manual", "Program Cycle", "< Back" },
  { "Motor", "< Back" }
};

String menuTitles[] = {
  "Main Menu", "Break In", "Setup"
};

void drawMenu() {
  if (curMenu < 0) return;
  if (curActiveItem == activeItem) return;
  if (activeItem < 0) activeItem = 0;

  clearArea(0, 0, 96, 15, BLACK);
  writeSmall(0, 0, menuTitles[curMenu], YELLOW);

  int y = 15;
  for (int i = 0; i < NUMITEMS(menuItems); i++) {
    banner(String(menuItems[curMenu][i]), 0, y, 96, 12, 0,
      activeItem == i ? BLACK : WHITE,
      activeItem == i ? WHITE : BLACK);
    y += 10;
  }

  curActiveItem = activeItem;
}

void resetMenu() {
  curActiveItem = -1;
}

String getSelectedItem() {
  return menuItems[curMenu][activeItem];
}

bool handleMenuSelection(int num) {
  if (curMenu < 0) return false;
  if (num == 1) {
    String item = getSelectedItem();
    if (item == "Break In") {
      activeItem = -1;
      curMenu = MENU_START;
      return true;
    }

    if (item == "Setup") {
      activeItem = -1;
      curMenu = MENU_SETUP;
      return true;
    }

    if (item == "< Back") {
      activeItem = -1;
      curMenu = MENU_MAIN;
      return true;
    }

    return false;
  }

  if (num == 2) {
    activeItem += 1;
    if (activeItem > NUMITEMS(menuItems)-1) {
      activeItem = 0;
    }
    return true;
  }
}

