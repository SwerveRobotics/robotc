#ifndef MOTORS_C
#define MOTORS_C

#include "../controllers/controller.c"

//Sets the minimums and maximums of motor powers and joystick values.
const float JOY_MAX = 128.0;
const float MOTOR_MIN = 20.0;
const float MOTOR_MAX = 100.0;

//Sets the slope and y-intercept of the function to look nicer below.
const float SLOPE = (MOTOR_MAX - MOTOR_MIN) /(JOY_MAX - DEADZONE);
const float INTERCEPT = DEADZONE - SLOPE;

int InputScale(int controllerVal)
{
	return (SLOPE * controllerVal + INTERCEPT);
}

//Sets the left motor power to what the Drive task told it to be and manipulates the power acordingly.
void LeftMotorPower(int leftSpeed)
{
	motor[mtrL] = InputScale(leftSpeed) * sgn(leftSpeed);
}

//Sets the right motor power to what the Drive task told it to be and manipulates the power acordingly.
void RightMotorPower(int rightSpeed)
{
	motor[mtrR] = InputScale(rightSpeed) * sgn(rightSpeed);
}
#endif
