#ifndef MOTORS_C
#define MOTORS_C

int RunMotorForOneSecond(int speed)
{
	motor[single] = speed;
	wait1Msec(1000);
	motor[single] = 0;
	return motor[single];
}

#endif
