// Cables
// GND - GND
// VCC - 3.3V
// SCK - D5 - 14
// SDA - D7 - 13
// RST - D2 - 4
// DC  - D1 - 5
// CS  - TX - 1
// Button 1 - RX - 3
// Button 2 - SD3 - 10
// MX Switch - D4 - 2
// Potentiometer - A0
// Motor Enable Pin1 - D0 - 16
// Motor Enable Pin2 - D3 - 0

// GPIOs
//  0 - D3  - Motor Enable 1
//  1 - TX  - OLED CS
//  2 - D4  - MX Switch
//  3 - RX  - Button 1
//  4 - D2  - OLED RST
//  5 - D1  - OLED DC
//  6 - ??  - Not found
//  7 - ??  - Not found
//  8 - ??  - Not found
//  9 - SD2 - Can't be used
// 10 - SD3 - Button 2
// 11 - ??  - Not found
// 12 - D6  - Unused
// 13 - D7  - OLED SDA
// 14 - D5  - OLED SCK
// 15 - D8  - Motor PWM
// 16 - D0  - Motor Enable 2

// Row 1                    Row 2
// Vin - +5V                D0  - Motor Enable 2
// GND - Common GND         D1  - OLED DC
// RST - Not Connected      D2  - OLED RST
// EN  - Not Connected      D3  - Motor Enable 1
// 3V3 - Not Connected      D4  - MX Switch
// GND - Common GND         3V3 - Not Connected
// CLK - Not Connected      GND - Common GND
// SD0 - Not Connected      D5  - OLED SCK
// CMD - Not Connected      D6  - Unused
// SD1 - Not Connected      D7  - OLED SDA
// SD2 - Not Connected      D8  - Motor PWM
// SD3 - Button 2           RX  - Button 1
// RSV - Not Connected      TX  - OLED CS
// RSV - Not Connected      3V3 - Not Connected

// Ribbon pinout
//  1 - OLED GND
//  2 - OLED VDD
//  3 - OLED SCK
//  4 - OLED SDA
//  5 - OLED RES
//  6 - OLED DC
//  7 - OLED CS
//  8 - Button 1
//  9 - Button 2
// 10 - Potentiometer

// OLED
#define OLED_SCLK 14 // SCK
#define OLED_MOSI 13 // SDA
#define OLED_RST 4   // RES
#define OLED_DC 5    // DC
#define OLED_CS 1    // CS

// Motor Controller L293D
#define MOTOR_ENABLE1 16
#define MOTOR_ENABLE2 0
#define MOTOR_PWM 15

// Buttons
#define BUT1 3
#define BUT2 10
#define MX_PIN 2
