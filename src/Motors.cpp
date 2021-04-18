#include <Arduino.h>
#include <Motors.h>

bool curMotorRunning = true;
bool motorRunning = false;

bool curMotorDirection = MOTOR_BACKWARD;
bool motorDirection = MOTOR_FORWARD;

int curMotorSpeed = -1;
int motorSpeed = 0; // 0-10

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
    digitalWrite(MOTOR_ENABLE1, motorDirection ? HIGH : LOW);
    digitalWrite(MOTOR_ENABLE2, motorDirection ? LOW : HIGH);
  }

  if (changed) {
    analogWrite(MOTOR_PWM, map(motorSpeed, 0, 10, PWMRANGE/2, PWMRANGE));
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
