#ifndef MOTORS_C
#define MOTORS_C

void LeftMotorPower(int leftSpeed)
void RightMotorPower(int rightSpeed)
{
	if(abs(leftSpeed) > 15)
	{
		motor[Left] = leftSpeed;
	}
	else
	{
		motor[Left] = 0;
	}

	if(abs(rightSpeed) > 15)
	{
		motor[Right] = rightSpeed;
	}
	else
	{
		motor[Right] = 0;
	}
}
#endif
