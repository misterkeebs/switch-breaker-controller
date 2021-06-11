// #ifndef SCREEN_MESSAGE
// #define SCREEN_MESSAGE

// #include <Arduino.h>
// #include <Input.h>
// #include <Motors.h>
// #include <Utils.h>
// #include <Screens.h>

// #include "Screen.cpp"

// class Message : public Screen
// {
// private:
//   bool init = false;

// public:
//   Message() : Screen() {
//   }

//   void reset() {
//     init = false;
//   }

//   int draw() override
//   {
//     if (!init)
//     {
//       init = true;
//       clearScreen();
//       box(0, 0, 96, 64, WHITE);
//       banner(getMessage(), 2, 15, 92, 12, 0, WHITE, BLACK);
//       banner("OK", 23, 35, 50, 12, 1, WHITE, RED);
//     }

//     if (wasAnyPuttonPressed()) {
//       reset();
//       return getReturnTo();
//     }

//     return SCR_MESSAGE;
//   }
// };

// #endif
