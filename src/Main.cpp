#include <Arduino.h>
#include <ArduinoOTA.h>
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
#include <Program.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting...");
  delay(1000);

  // wifi
  Serial.printf("Connecting to WIFI: %s...\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	while (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		Serial.println("Connection Failed! Rebooting...");
		delay(5000);
		// ESP.restart();
	}

  Serial.print("Connected to: ");
  Serial.print(WIFI_SSID);
  Serial.print(" with IP: ");
  Serial.println(WiFi.localIP());

  ArduinoOTA.onStart([]() {
    Serial.println("Starting OTA update...");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("OTA update finished");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // motor driver
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_ENABLE1, OUTPUT);
  pinMode(MOTOR_ENABLE2, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);

  initWebServer();
}

void loop() {
  ArduinoOTA.handle();

  updateMotor();
  checkSwitch();
  checkProgram();
}
