// Buttons
#define BUT_DEBOUNCE 200

// Click counter - MX Switch - D4
#define MX_DEBOUNCE 200

void checkSwitch();
void startCountingClicks();
void stopCountingClicks();
void setCountingClicks(bool enabled);
long getClicks();
void resetClicks();
long getRpm();
void updateRpm();
void resetIntervalClicks();

void checkPotentiometer();
int getPotReading();

void checkButtons();
void handleButton(int num);
bool wasAnyPuttonPressed();
bool wasButton1Pressed();
bool wasButton2Pressed();
