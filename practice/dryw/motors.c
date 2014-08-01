#ifndef MOTORS_C
#define MOTORS_C

const float joyMin = 50.0;
const float joyMax = 128.0;
const float motorMin = 20.0;
const float motorMax = 100.0;
const float slope = (motorMax - motorMin) /(joyMax - joyMin);
const float intercept = joyMin - slope;

void LeftMotorPower(int leftSpeed)
{
	motor[mtrL] = slope * leftSpeed + intercept * sgn(leftSpeed); //Sets the left motor power to what the Drive task told it to be
}

void RightMotorPower(int rightSpeed)
{
	motor[mtrR] = slope * rightSpeed + intercept * sgn(rightSpeed); //Sets the right motor power to what the Drive task told it to be
}
#endif
