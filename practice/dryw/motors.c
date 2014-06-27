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

void RightMotorPower(int rightSpeed)
{
	if(abs(rightSpeed) > 15)
	{
		motor[mtrR] = rightSpeed;
	}
	else
	{
		motor[mtrR] = 0;
	}
}
#endif
