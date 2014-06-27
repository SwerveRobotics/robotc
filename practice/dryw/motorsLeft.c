#ifndef MOTORS_C
#define MOTORS_C

void LeftMotorPower(int leftSpeed)
{
	if(abs(leftSpeed) > 15)
	{
		motor[mtrL] = leftSpeed;
	}
	else
	{
		motor[mtrL] = 0;
	}
}
#endif
