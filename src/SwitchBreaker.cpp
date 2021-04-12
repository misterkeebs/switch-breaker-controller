#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#include <Credentials.h>

// OLED Mapping
// GND - GND
// VCC - 3.3V
// SCK - D5 - 14
// SDA - D7 - 13
// RST - D2 - 4
// DC  - D1 - 5
// CS  - D8 - 15

// OLED
#define OLED_SCLK 14
#define OLED_MOSI 13
#define OLED_RST 4
#define OLED_DC 5
#define OLED_CS 1

// Buttons - SD2 and SD3 (GPIOs 9 and 10)
#define BUT1 9
#define BUT2 10
#define BUT_DEBOUNCE 200

// MX Switch - D4
#define MX_PIN 2
#define MX_DEBOUNCE 100

// Motor Controller L293D
// Enable pins D0 and D3
// PWM pin SD2
#define MOTOR_ENABLE1 16
#define MOTOR_ENABLE2 0
#define MOTOR_PWM 15

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define CLK_X 60
#define CLK_Y 5
#define RPM_X 60
#define RPM_Y 15

#define MIN_VAL 3
#define MAX_VAL 1023

ESP8266WebServer server(80);
Adafruit_SSD1331 display = Adafruit_SSD1331(OLED_CS, OLED_DC, OLED_RST);
unsigned long clickCounter = 0;
unsigned long intervalClicks = 0;
unsigned long rpmCounter;
int val = 0;
int perc = 0;
int curPerc = 100;
int motorMode = 0;

// redraw interval
long startTime = 0;
long curTime = 0;
long lastRpmCheck = 0;
long lastMotorCheck = 0;

// switch press
int state = LOW;
int reading;
int prevState = HIGH;
long lastTime = 0;

// button presses
int but1State = LOW;
int but1Reading;
int but1PrevState = HIGH;
long but1LastTime = 0;
int but2State = LOW;
int but2Reading;
int but2PrevState = HIGH;
long but2LastTime = 0;

void updateRpm();
void updateClicks();
void checkSwitch();
void checkButtons();
void updateClicks();
void updateMotorSpeed();
void changeMotor();
void handleStatus();
void handleNotFound();

void setup()
{
  Serial.begin(19200);

  // switch
  pinMode(MX_PIN, INPUT);

  // buttons
  pinMode(BUT1, INPUT_PULLUP);
  pinMode(BUT2, INPUT_PULLUP);

  // motor driver
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_ENABLE1, OUTPUT);
  pinMode(MOTOR_ENABLE2, OUTPUT);

  display.begin();
  display.fillScreen(BLACK);
  display.setTextColor(WHITE);
  display.setTextSize(1);

  // wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  display.setCursor(10, 5);
  display.print(WIFI_SSID);
  display.setCursor(10, 15);
  display.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    display.setCursor(10, 15);
    display.print("Connecting   ");
    delay(250);
    display.setCursor(10, 15);
    display.print("Connecting...");
    delay(250);
  }

  display.fillScreen(BLACK);
  display.setCursor(10, 5);
  display.print("Connected:");
  display.setCursor(10, 15);
  display.print(WiFi.localIP());

  if (MDNS.begin("esp8266"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/status", handleStatus);
  server.onNotFound(handleNotFound);
  server.begin();

  delay(1000);

  display.fillScreen(BLACK);
  display.drawRect(0, 0, 96, 64, WHITE);

  display.setCursor(10, 5);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("Clicks:");

  display.setCursor(10, 15);
  display.setTextSize(1);
  display.print("Rpm:");

  display.setCursor(10, 50);
  display.print(WiFi.localIP());

  analogWrite(MOTOR_PWM, 0);
  digitalWrite(MOTOR_ENABLE1, HIGH);
  digitalWrite(MOTOR_ENABLE2, LOW);

  updateMotorSpeed();
  updateClicks();
  updateRpm();
}

void loop()
{
  server.handleClient();
  curTime = millis();

  if (curTime - startTime > 100)
  {
    updateMotorSpeed();
    startTime = millis();
  }

  if (millis() - lastRpmCheck > 1000)
  {
    rpmCounter = intervalClicks / 2 * 60;
    updateRpm();
    intervalClicks = 0;
    lastRpmCheck = millis();
  }

  checkSwitch();
  checkButtons();
  // changeMotor();

  // delay(10);
}

void changeMotor()
{
  Serial.println("Changing motor...");
  if (millis() - lastMotorCheck > 2000)
  {
    motorMode++;
    if (motorMode > 1)
      motorMode = 0;

    Serial.print("New motor mode: ");
    Serial.println(motorMode);
    if (motorMode == 0)
    {
      Serial.println("Dir");
      digitalWrite(MOTOR_ENABLE1, HIGH);
      digitalWrite(MOTOR_ENABLE2, LOW);
    }
    if (motorMode == 1)
    {
      Serial.println("Stop");
      digitalWrite(MOTOR_ENABLE1, LOW);
      digitalWrite(MOTOR_ENABLE2, LOW);
    }

    lastMotorCheck = millis();
  }
}

void updateRpm()
{
  display.fillRect(RPM_X, RPM_Y, 30, 10, BLACK);
  display.setCursor(RPM_X, RPM_Y);
  display.setTextColor(RED);
  char rpm[5];
  sprintf(rpm, "%lu", rpmCounter);
  display.print(rpm);
}

void updateClicks()
{
  display.fillRect(CLK_X, CLK_Y, 30, 10, BLACK);
  display.setCursor(CLK_X, CLK_Y);
  display.setTextColor(YELLOW);
  char clicks[5];
  sprintf(clicks, "%lu", clickCounter);
  display.print(clicks);
}

void checkSwitch()
{
  reading = digitalRead(MX_PIN);
  if (reading == LOW && prevState == HIGH && millis() - lastTime > MX_DEBOUNCE)
  {
    if (reading == LOW)
    {
      state = HIGH;
      Serial.println("Pressed");
      clickCounter += 1;
      intervalClicks += 1;
      updateClicks();
    }
    else
    {
      state = LOW;
    }
    lastTime = millis();
  }
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
    }
    else
    {
      but2State = LOW;
    }
    but2LastTime = millis();
  }

  if (but1State == HIGH)
  {
    Serial.println("But1 Pressed");
    perc = perc - 10;
    if (perc < 0)
      perc = 0;
    updateMotorSpeed();
    return;
  }

  if (but2State == HIGH)
  {
    Serial.println("but2 Pressed");
    perc = perc + 10;
    if (perc > 100)
      perc = 100;
    updateMotorSpeed();
    return;
  }
}

void updateMotorSpeed()
{
  if (curPerc != perc)
  {
    curPerc = perc;
    display.fillRect(5, 30, 86, 10, BLACK);
    display.drawRect(5, 30, 86, 10, WHITE);
    display.fillRect(5, 30, 86 * ((float)perc / 100), 10, WHITE);
    Serial.print("Setting PWM to ");
    Serial.println(PWMRANGE * ((float)perc / 100));
    analogWrite(MOTOR_PWM, PWMRANGE * ((float)perc / 100));
  }
}

void handleStatus()
{
  String message = "{";
  message += "\"rpm\":";
  message += rpmCounter;
  message += ",";
  message += "\"clicks\":";
  message += clickCounter;
  message += "}";
  server.send(200, "application/json", message);
}

void handleNotFound()
{
  server.send(404, "application/json", "{\"error\":\"Not found\"}");
}