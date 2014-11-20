#ifndef MOTORS_C
#define MOTORS_C

void RunMotorForOneSecond(int speed)
{
	motor[single] = speed;
	wait1Msec(1000);
	motor[single] = 0;
}






#endif
