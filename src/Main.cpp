#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#include <Input.h>
#include <Colors.h>
#include <Gfx.h>
#include <Menu.h>

void draw();

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
