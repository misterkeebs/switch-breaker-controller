#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#include <Colors.h>
#include <Gfx.h>
#include <Menu.h>

// Buttons - SD2 and SD3 (GPIOs 9 and 10)
#define BUT1 9
#define BUT2 10
#define BUT_DEBOUNCE 200

void displayLogo();
void checkButtons();
void handleButton(int num);
void draw();
void drawScreen();

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

void setup()
{
  // Serial.begin(9600);
  initScreen();

  // buttons
  pinMode(BUT1, INPUT_PULLUP);
  pinMode(BUT2, INPUT_PULLUP);

  displayLogo();
  clearScreen();
}

void loop() {
  checkButtons();
  draw();
}

void draw() {
  drawMenu();
}

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
    Serial.println("But1 Pressed");
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

void drawScreen() {
  writeSmall(getSelectedItem(), 0, 0, WHITE);
}


