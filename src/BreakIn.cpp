// #ifndef SCREEN_BREAKIN_H
// #define SCREEN_BREAKIN_H

// #include <Colors.h>
// #include <Gfx.h>
// #include <Input.h>
// #include <Motors.h>
// #include <Screens.h>
// #include <Utils.h>

// #include "Screen.cpp"

// class BreakIn : public Screen {
//   private:
//     long curRpm = 0;
//     long curClicks = 0;
//     long prevRpm = -1;
//     long prevClicks = -1;
//     long startTime;
//     long lastTime = 0;
//     bool init = false;
//     bool curMotorRunning = false;
//     int curMotorSpeed = -1;
//     bool curMotorDirection = MOTOR_BACKWARD;
//     long runningTime = 0;
//     long elapsed;
//     long lastCycle = 0;
//     int rotReading = 0;
//     int curRotReading = -1;
//     long lastDisplayToggle = -1;
//     long forceClickDisplay = false;
//     bool displayPercent = false;

//   public:
//     BreakIn() : Screen() {
//       startTime = millis();
//       lastCycle = millis();
//     }

//     void reset() {
//       Serial.println("Reset");
//       setProgramCycle(-1);
//       resetClicks();

//       curRpm = 0;
//       curClicks = 0;
//       prevRpm = -1;
//       prevClicks = -1;
//       startTime;
//       lastTime = 0;
//       init = false;
//       curMotorRunning = false;
//       curMotorSpeed = -1;
//       curMotorDirection = MOTOR_BACKWARD;
//       runningTime = 0;
//       elapsed;
//       lastCycle = 0;
//       curRotReading = -1;
//       lastDisplayToggle = -1;
//       forceClickDisplay = false;
//       displayPercent = false;
//     }

//     int updateMotorStatus() {
//       curMotorRunning = isMotorRunning();
//       curMotorDirection = getMotorDirection();
//       curMotorSpeed = getMotorSpeed();

//       setCountingClicks(isMotorRunning());

//       String info = curMotorDirection ? ">" : "<";
//       info += " ";
//       info += curMotorSpeed;

//       banner(info, 5, 20, 86, 12, 0, YELLOW, BLACK);

//       if (isMotorRunning()) {
//         banner("O=Pause", 2, 50, 46, 12, 1, DKGRAY, LTGRAY);
//         banner("X=Menu", 49, 50, 45, 12, 1, DKGRAY, LTGRAY);
//       } else {
//         banner("O=Start", 2, 50, 46, 12, 1, DKGRAY, LTGRAY);
//         banner("X=Menu", 49, 50, 45, 12, 1, DKGRAY, LTGRAY);
//       }
//     }

//     int draw() override {
//       if (!init) {
//         clearScreen();
//         box(0, 0, 96, 64, WHITE);
//       }

//       if (wasButton2Pressed()) {
//         init = false;
//         return SCR_BREAKIN_MENU;
//       }

//       if (wasButton1Pressed()) {
//         toggleMotor();
//       }

//       curRotReading = getMoveDelta();
//       if (!init || curRotReading != 0) {
//         setMotorSpeed(getMotorSpeed() + curRotReading);
//       }

//       if (!init || curMotorRunning != isMotorRunning()
//           || curMotorDirection != getMotorDirection()
//           || curMotorSpeed != getMotorSpeed()) {
//         updateMotorStatus();
//       }

//       curRpm = getRpm();
//       curClicks = getClicks();

//       if (curRpm != prevRpm || !init) {
//         prevRpm = curRpm;
//         char rpm[5];
//         sprintf(rpm, "%lu", curRpm);
//         banner(rpm, 9, 4, 30, 12, 1, WHITE, RED);
//       }

//       if (getProgramCycle() > -1 && (millis() - lastDisplayToggle) > (displayPercent ? 2000 : 5000)) {
//         lastDisplayToggle = millis();
//         forceClickDisplay = true;
//         displayPercent = !displayPercent;
//       }

//       if (curClicks != prevClicks || !init || forceClickDisplay) {
//         forceClickDisplay = false;
//         prevClicks = curClicks;
//         char clicks[6];
//         int perc = getProgramCycle() > -1
//           ? ((int) (curClicks / (float) getProgramCycle() * 100))
//           : 0;
//         if (displayPercent) {
//           sprintf(clicks, "%lu%%", perc);
//         } else {
//           sprintf(clicks, "%lu", curClicks);
//         }
//         bannerPerc(perc, clicks, 45, 4, 45, 12, 1, BLACK, RED, YELLOW);
//       }

//       if (isMotorRunning()) {
//         elapsed = millis() - lastCycle;
//         runningTime += elapsed;
//       }

//       if (millis() - lastTime > 1000 || !init) {
//         lastTime = millis();
//         banner(formatMillis(runningTime), 5, 30, 86, 12, 0, YELLOW, BLACK);
//       }

//       if (getProgramCycle() > -1 && curClicks >= getProgramCycle()) {
//         stopMotor();
//         reset();
//         curClicks = 0;
//         return displayMessage("Program Done!", SCR_BREAKIN);
//       }

//       lastCycle = millis();
//       init = true;
//       return SCR_BREAKIN;
//     }
// };
// #endif
