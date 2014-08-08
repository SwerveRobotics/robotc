#ifndef MOTORS_C
#define MOTORS_C

//Sets the minimums and maximums of motor powers and joystick values.
const float joyMax = 128.0;
const float motorMin = 20.0;
const float motorMax = 100.0;

//Sets the slope and y-intercept of the function to look nicer below.
const float slope = (motorMax - motorMin) /(joyMax - deadZone);
const float intercept = deadZone - slope;

//Sets the left motor power to what the Drive task told it to be and manipulates the power acordingly.
void LeftMotorPower(int leftSpeed)
{
	motor[mtrL] = slope * leftSpeed + intercept * sgn(leftSpeed);
}

//Sets the right motor power to what the Drive task told it to be and manipulates the power acordingly.
void RightMotorPower(int rightSpeed)
{
	motor[mtrR] = slope * rightSpeed + intercept * sgn(rightSpeed);
}
#endif
