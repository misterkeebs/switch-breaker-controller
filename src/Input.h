// Buttons - SD2 and SD3 (GPIOs 9 and 10)
#define BUT1 9
#define BUT2 10
#define BUT_DEBOUNCE 200

void checkButtons();
void handleButton(int num);
bool wasAnyPuttonPressed();
bool wasButton1Pressed();
bool wasButton2Pressed();
