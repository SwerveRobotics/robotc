#ifndef MOTORS_C
#define MOTORS_C

void SetSpeedIfAboveDeadZone(int speed, int deadZone)
{
	if(abs(speed) > deadZone)
	{
		motor[single] = speed;
	}
	else
	{
		motor[single] = 0;
	}
}

#endif
