#include <Arduino.h>
#include <Colors.h>

#define MENU_MAIN 0
#define MENU_START 1
#define MENU_SETUP 2

void drawMenu();
void resetMenu();
String getSelectedItem();
bool handleMenuSelection(int num);
void setMainMenu();
void showMenu(int menu);
