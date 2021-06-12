#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#include <Pinout.h>
#include <Motors.h>
#include <Credentials.h>
#include <Switch.h>
#include <WebServer.h>

IPAddress curIp;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting...");
  delay(1000);

  // motor driver
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_ENABLE1, OUTPUT);
  pinMode(MOTOR_ENABLE2, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);

  // wifi
  Serial.println("Connecting to WIFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  initWebServer();
}

void loop() {
  handleServer();

  IPAddress ip = WiFi.localIP();
  if (curIp != ip) {
    curIp = ip;
    Serial.print("Connected to: ");
    Serial.print(WIFI_SSID);
    Serial.print(" with IP: ");
    Serial.println(WiFi.localIP());
  }

  updateMotor();
  checkSwitch();
}
