#include <Arduino.h>

// OLED Mapping
// GND - GND
// VCC - 3.3V
// SCK - D5
// SDA - D7
// RST - D2
// DC  - D1
// CS  - D8

// OLED
#define OLED_SCLK 14
#define OLED_MOSI 13
#define OLED_CS 15
#define OLED_RST 4
#define OLED_DC 5

// Potentiometer - A0
// MX Switch - D4
#define MX_PIN 2
#define MX_DEBOUNCE 100

// Motor Controller L293D
// Enable pins D0 and D3
// PWM pin SD2
#define MOTOR_ENABLE1 16
#define MOTOR_ENABLE2 0
#define MOTOR_PWM 10

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

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

Adafruit_SSD1331 display = Adafruit_SSD1331(OLED_CS, OLED_DC, OLED_RST);
unsigned long clickCounter = 0;
unsigned long intervalClicks = 0;
unsigned long rpmCounter;
int val = 0;
int perc = 0;
int curPerc = 0;

// redraw interval
long startTime = 0;
long curTime = 0;
long lastRpmCheck = 0;

// switch press
int state = LOW;
int reading;
int prevState = HIGH;
long lastTime = 0;

void updateRpm();
void updateClicks();
void checkSwitch();
void checkPotentiometer();
void updateClicks();
void updatePercentBar();

void setup()
{
  Serial.begin(9600);

  // potentiometer
  pinMode(A0, INPUT);

  // switch
  pinMode(MX_PIN, INPUT);

  // motor driver
  pinMode(MOTOR_ENABLE1, OUTPUT);
  pinMode(MOTOR_ENABLE2, OUTPUT);

  display.begin();
  display.fillScreen(BLACK);
  display.drawRect(0, 0, 96, 64, WHITE);

  display.setCursor(10, 5);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("Clicks:");

  display.setCursor(10, 15);
  display.setTextSize(1);
  display.print("Rpm:");

  updateClicks();
  updateRpm();
}

void loop()
{
  curTime = millis();

  if (curTime - startTime > 100)
  {
    checkPotentiometer();
    updatePercentBar();
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

  delay(10);
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

void checkPotentiometer()
{
  val = analogRead(A0);
  if (val < MIN_VAL)
  {
    val = MIN_VAL;
  }
  if (val > MAX_VAL)
  {
    val = MAX_VAL;
  }
  perc = (val - MIN_VAL) * 100 / (MAX_VAL - MIN_VAL);
}

void updatePercentBar()
{
  if (curPerc != perc)
  {
    curPerc = perc;
    display.fillRect(5, 30, 86, 10, BLACK);
    display.drawRect(5, 30, 86, 10, WHITE);
    display.fillRect(5, 30, 86 * ((float)perc / 100), 10, WHITE);
  }
}
