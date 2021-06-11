// #include <Arduino.h>
// #include <Adafruit_MCP23017.h>
// #include <Rotary.h>
// #include <RotaryEncOverMCP.h>

// #include <Gfx.h>
// #include <Input.h>
// #include <Menu.h>
// #include <Pinout.h>
// #include <Screens.h>

// // button presses
// int pushButState = LOW;
// int curPushButState = -1;
// int rotButState = LOW;
// int curRotButState = -1;
// int pushButPressed = 0;
// int rotButPressed = 1;
// int but1Pressed = 0;
// int but2Pressed = 0;

// int moveDelta = 0;

// bool was1Pressed = false;
// bool was2Pressed = false;

// int mxReading;
// long mxLastTime = 0;
// long clickCounter = 0;
// long intervalClickCounter = 0;
// long rpmCounter = 0;
// long rpmLastTime = 0;
// bool countingClicks = false;

// Adafruit_MCP23017 mcp;
// Adafruit_MCP23017 *mcpr = &mcp;
// RotaryEncOverMCP rotaryEncoder = RotaryEncOverMCP(&mcp, ROT_CLK, ROT_DT, &rotaryEncoderChanged);

// void initGPIOs() {
//   Wire.begin(D3, D2);
//   Wire.beginTransmission(0x20);
//   int res = Wire.endTransmission();
//   Serial.print("MCP Result: ");
//   Serial.println(res);

//   mcp.begin();
//   rotaryEncoder.init();

//   mcpr->pullUp(PUSH_BUT, 1);
//   mcpr->pinMode(PUSH_BUT, INPUT);
//   mcpr->pinMode(ROT_SW, INPUT);
// }

// void startCountingClicks() {
//   countingClicks = true;
// }

// void stopCountingClicks() {
//   countingClicks = false;
// }

// void setCountingClicks(bool enabled) {
//   countingClicks = enabled;
// }

// void checkSwitch() {
//   // if (!countingClicks) return;
//   // mxReading = digitalRead(MX_PIN);
//   // if (mxReading == LOW && millis() - mxLastTime > MX_DEBOUNCE) {
//   //   Serial.println("MX Pressed");
//   //   clickCounter += 1;
//   //   intervalClickCounter += 1;
//   //   mxLastTime = millis();
//   // }
//   // updateRpm();
// }

// long getRpm() {
//   return rpmCounter;
// }

// void updateRpm() {
//   if (millis() - rpmLastTime > 1000) {
//     rpmCounter = intervalClickCounter / 2 * 60;
//     resetIntervalClicks();
//     rpmLastTime = millis();
//   }
// }

// long getClicks() {
//   return clickCounter;
// }

// void resetClicks() {
//   clickCounter = 0;
// }

// long getIntervalClicks() {
//   return intervalClickCounter;
// }

// void resetIntervalClicks() {
//   intervalClickCounter = 0;
// }

// void checkButtons()
// {
//   rotaryEncoder.poll();
//   rotButState = mcpr->digitalRead(ROT_SW);
//   pushButState = mcpr->digitalRead(PUSH_BUT);

//   if (curRotButState != rotButState) {
//     curRotButState = rotButState;
//     if (curRotButState == 0) {
//       Serial.print("Rotary button status = ");
//       Serial.println(curRotButState);
//       rotButPressed = 1;
//     }
//   }

//   if (curPushButState != pushButState) {
//     curPushButState = pushButState;
//     if (curPushButState == 0) {
//       Serial.print("Push button status = ");
//       Serial.println(curPushButState);
//       pushButPressed = 1;
//     }
//   }

//   if (rotButPressed == 1)
//   {
//     rotButPressed = 0;
//     handleButton(1);
//     return;
//   }

//   if (pushButPressed == 1)
//   {
//     pushButPressed = 0;
//     handleButton(2);
//     return;
//   }
// }

// bool wasAnyPuttonPressed() {
//   return wasButton1Pressed() || wasButton2Pressed();
// }

// bool wasButton1Pressed() {
//   if (was1Pressed) {
//     was1Pressed = false;
//     return true;
//   }
//   return false;
// };

// bool wasButton2Pressed() {
//   if (was2Pressed) {
//     was2Pressed = false;
//     return true;
//   }
//   return false;
// };

// void handleButton(int num) {
//   if (num == 1) was1Pressed = true;
//   if (num == 2) was2Pressed = true;
// }

// void rotaryEncoderChanged(bool antiClock, int id)
// {
//   Serial.println("Encoder " + String(id) + ": " + (antiClock ? String("left") : String("right")));
//   moveDelta += antiClock ? -1 : 1;
// }

// int peekMoveDelta() {
//   return moveDelta;
// }

// int getMoveDelta() {
//   int ret = moveDelta;
//   moveDelta = 0;
//   return ret;
// }
