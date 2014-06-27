#ifndef MOTORS_C
#define MOTORS_C

void LeftMotorPower(int leftSpeed)
{
	motor[mtrL] = leftSpeed;
}

void RightMotorPower(int rightSpeed)
{
	motor[mtrR] = rightSpeed;
}
#endif
