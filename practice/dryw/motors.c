#ifndef MOTORS_C
#define MOTORS_C

void LeftMotorPower(int leftSpeed)
{
	motor[mtrL] = leftSpeed; //Sets the left motor power to what the Drive task told it to be
}

void RightMotorPower(int rightSpeed)
{
	motor[mtrR] = rightSpeed; //Sets the right motor power to what the Drive task told it to be
}
#endif
