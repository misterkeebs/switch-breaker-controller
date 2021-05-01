#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#include <Pinout.h>
#include <Input.h>
#include <Colors.h>
#include <Gfx.h>
#include <Menu.h>
#include <Motors.h>
#include <Screens.h>

#include "Screen.cpp"
#include "LogoScreen.cpp"

Screen *curScreen;

void draw();

void setup()
{
  Serial.begin(9600);
  delay(1000);

  initGPIOs();
  initScreen();

  curScreen = getScreen(SCR_BREAKIN);
  clearScreen();
}

void loop() {
  checkSwitch();
  checkButtons();
  checkPotentiometer();
  updateMotor();

  // Serial.println("Before drawing.");
  int newScreenId = curScreen->draw();
  // Serial.print("Loading newScreen: ");
  // Serial.print(newScreenId);
  // Serial.print("... ");
  curScreen = getScreen(newScreenId);
}
