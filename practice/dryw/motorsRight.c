#ifndef MOTORSRIGHT_C
#define MOTORSRIGHT_C

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
