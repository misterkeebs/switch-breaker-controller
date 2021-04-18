// Buttons - SD2 and SD3 (GPIOs 9 and 10)
#define BUT1 9
#define BUT2 10
#define BUT_DEBOUNCE 200

// Click counter - MX Switch - D4
#define MX_PIN 2
#define MX_DEBOUNCE 200

void checkSwitch();
long getClicks();
void resetClicks();
long getRpm();
void updateRpm();
void resetIntervalClicks();

void checkButtons();
void handleButton(int num);
bool wasAnyPuttonPressed();
bool wasButton1Pressed();
bool wasButton2Pressed();
