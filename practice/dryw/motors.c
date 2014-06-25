#ifndef MOTORS_C
#define MOTORS_C

void MotorPower(int speed)
{
	if(abs(speed) > 10)
		{
		 	motor[single] = speed;
		}
		else
		{
			motor[single] = 0;
		}
}

#endif
