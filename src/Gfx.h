#include <Arduino.h>

// OLED Mapping
// GND - GND
// VCC - 3.3V
// SCK - D5 - 14
// SDA - D7 - 13
// RST - D2 - 4
// DC  - D1 - 5
// CS  - TX - 1

void initScreen();
void clearScreen();
void clearArea(int x, int y, int w, int h, int color);
void box(int x, int y, int w, int h, int color);
void displayLogo();
void writeSmall(int x, int y, String text, int color);
void banner(String text, int x, int y, int wx, int wy, int bold, int fgcolor, int bgcolor);
