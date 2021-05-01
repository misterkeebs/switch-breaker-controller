#include <Arduino.h>
#include <Motors.h>
#include <Pinout.h>

#include <Gfx.h>
#include <Colors.h>

bool curMotorRunning = true;
bool motorRunning = false;

bool curMotorDirection = MOTOR_BACKWARD;
bool motorDirection = MOTOR_FORWARD;

int curMotorSpeed = -1;
int motorSpeed = 0; // 0-10

long programCycle = -1;

void updateMotor() {
  bool changed = false;

  if (curMotorRunning != motorRunning) {
    curMotorRunning = motorRunning;
    changed = true;
  }

  if (curMotorSpeed != motorSpeed) {
    curMotorSpeed = motorSpeed;
    changed = true;
  }

  if (curMotorDirection != motorDirection) {
    curMotorDirection = motorDirection;
    changed = true;
  }

  if (changed) {
    analogWrite(MOTOR_PWM, map(motorSpeed, 0, 10, PWMRANGE/2, PWMRANGE));
    applyMotorDirection();
  }
}

void applyMotorDirection() {
  if (motorRunning) {
    // banner("R+", 0, 0, 96, 12, 0, WHITE, BLACK);
    digitalWrite(MOTOR_ENABLE1, motorDirection ? HIGH : LOW);
    digitalWrite(MOTOR_ENABLE2, motorDirection ? LOW : HIGH);
  } else {
    // banner("R-", 0, 0, 96, 12, 0, WHITE, BLACK);
    digitalWrite(MOTOR_ENABLE1, LOW);
    digitalWrite(MOTOR_ENABLE2, LOW);
  }
}

bool isMotorRunning() {
  return motorRunning;
}

void startMotor() {
  motorRunning = true;
}

void stopMotor() {
  motorRunning = false;
}

void toggleMotor() {
  motorRunning = !motorRunning;
}

bool getMotorDirection() {
  return motorDirection;
}

void toggleMotorDirection() {
  motorDirection = !motorDirection;
}

int getMotorSpeed() {
  return motorSpeed;
}

void setMotorSpeed(int speed) {
  if (speed > 10) speed = 10;
  if (speed < 0) speed = 0;

  motorSpeed = speed;
}

void setProgramCycle(long keystrokes) {
  programCycle = keystrokes;
}

long getProgramCycle() {
  return programCycle;
}