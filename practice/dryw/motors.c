#ifndef MOTORS_C
#define MOTORS_C

void LeftMotorPower(int leftSpeed)
{
	motor[mtrL] = (abs(leftSpeed) + 12) * (5.0 / 7) * sgn(leftSpeed); //Sets the left motor power to what the Drive task told it to be
}

void RightMotorPower(int rightSpeed)
{
	motor[mtrR] = (abs(rightSpeed) + 12) * (5.0 / 7) * sgn(rightSpeed); //Sets the right motor power to what the Drive task told it to be
}
#endif
