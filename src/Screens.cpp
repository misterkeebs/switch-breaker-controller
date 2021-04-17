#include <Arduino.h>

#include <Colors.h>
#include <Gfx.h>
#include <Menu.h>

void drawScreen() {
  writeSmall(0, 0, getSelectedItem(), WHITE);
}
