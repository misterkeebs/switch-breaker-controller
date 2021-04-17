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

void initScreen();
void clearScreen();
void clearArea(int x, int y, int w, int h, int color);
void displayLogo();
void writeSmall(int x, int y, String text, int color);
void banner(String text, int x, int y, int wx, int wy, int bold, int fgcolor, int bgcolor);
