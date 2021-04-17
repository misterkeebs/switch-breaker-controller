#include <Arduino.h>

#include <Gfx.h>
#include <Input.h>
#include <Menu.h>
#include <Screens.h>

// button presses
int but1State = LOW;
int but1Reading;
int but1PrevState = HIGH;
long but1LastTime = 0;
int but2State = LOW;
int but2Reading;
int but2PrevState = HIGH;
long but2LastTime = 0;
int but1Pressed = 0;
int but2Pressed = 0;

void checkButtons()
{
  but1Reading = digitalRead(BUT1);
  but2Reading = digitalRead(BUT2);

  if (but1Reading == LOW && but1PrevState == HIGH && millis() - but1LastTime > BUT_DEBOUNCE)
  {
    if (but1Reading == LOW)
    {
      but1State = HIGH;
      but1Pressed = 1;
    }
    else
    {
      but1State = LOW;
    }
    but1LastTime = millis();
  }

  if (but2Reading == LOW && but2PrevState == HIGH && millis() - but2LastTime > BUT_DEBOUNCE)
  {
    if (but2Reading == LOW)
    {
      but2State = HIGH;
      but2Pressed = 1;
    }
    else
    {
      but2State = LOW;
    }
    but2LastTime = millis();
  }

  if (but1Pressed == 1)
  {
    but1Pressed = 0;
    handleButton(1);
    return;
  }

  if (but2Pressed == 1)
  {
    but2Pressed = 0;
    handleButton(2);
    return;
  }
}

void handleButton(int num) {
  if (!handleMenuSelection(num)) {
    clearScreen();
    resetMenu();
    drawScreen();
  }
}
