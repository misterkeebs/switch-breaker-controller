#define MOTOR_FORWARD true
#define MOTOR_BACKWARD false

void updateMotor();
bool isMotorRunning();
void startMotor();
void stopMotor();
void toggleMotor();
bool getMotorDirection();
void setMotorDirection(boolean forward);
void toggleMotorDirection();
void applyMotorDirection();
int getMotorSpeed();
void setMotorSpeed(int speed);
void setProgramCycle(long keystrokes);
long getProgramCycle();
