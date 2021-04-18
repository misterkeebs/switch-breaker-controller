// Motor Controller L293D
// Enable pins D0 and D3
// PWM pin SD2
#define MOTOR_ENABLE1 16
#define MOTOR_ENABLE2 0
#define MOTOR_PWM 15

#define MOTOR_FORWARD true
#define MOTOR_BACKWARD false

void updateMotor();
bool isMotorRunning();
void startMotor();
void stopMotor();
bool getMotorDirection();
void toggleMotorDirection();
int getMotorSpeed();
void setMotorSpeed(int speed);
