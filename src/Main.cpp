#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#include <Pinout.h>
#include <Motors.h>
#include <Credentials.h>
#include <Switch.h>

ESP8266WebServer server(80);
IPAddress curIp;

void handleIndex() {
  Serial.println("GET /");

  if (server.args() > 0) {
    String cmd = server.arg("cmd");
    Serial.print("Command: ");
    Serial.println(cmd);
    if (cmd == "start") {
      startMotor();
    }
    if (cmd == "stop") {
      stopMotor();
    }
    if (cmd == "faster") {
      setMotorSpeed(getMotorSpeed() + 1);
    }
    if (cmd == "slower") {
      setMotorSpeed(getMotorSpeed() - 1);
    }
    if (cmd == "direction") {
      toggleMotorDirection();
    }
    if (cmd == "reset") {
      stopMotor();
      resetClicks();
    }
    server.sendHeader("Location", String("/"), true);
    server.send(302, "text/plain", "");
    return;
  }

  String message = "";
  if (isMotorRunning()) {
    message += "<a href=\"/?cmd=stop\">Stop</a> | ";
  } else {
    message += "<a href=\"/?cmd=start\">Start</a> | ";
  }
  message += "<a href=\"/?cmd=reset\">Reset</a> | ";
  message += "<a href=\"/?cmd=direction\">Direction</a> | ";
  message += "<a href=\"/?cmd=faster\">Faster</a> | ";
  message += "<a href=\"/?cmd=slower\">Slower</a> | ";
  message += "<a href=\"/status\">Status</a>";
  message += "<p>Motor running: ";
  message += isMotorRunning() ? "Yes" : "No";
  message += "<br/>Motor speed: ";
  message += getMotorSpeed();
  message += "<br/>Direction: ";
  message += getMotorDirection() == MOTOR_BACKWARD ? "backward" : "forward";
  message += "<br/>Presses: ";
  message += getClicks();
  message += "<br/>RPM: ";
  message += getRpm();
  message += "</p>";
  server.send(200, "text/html", message);
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting...");
  delay(1000);

  // motor driver
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_ENABLE1, OUTPUT);
  pinMode(MOTOR_ENABLE2, OUTPUT);
  pinMode(SWITCH, INPUT);

  // wifi
  Serial.println("Connecting to WIFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  server.on("/", handleIndex);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop() {
  server.handleClient();

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
