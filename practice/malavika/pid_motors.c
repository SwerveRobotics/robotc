#ifndef MOTORS_C
#define MOTORS_C

int requestedSpeed = 0;

void RequestMotorSpeed(int speed)
{
	requestedSpeed = speed;
}

void SetMotorSpeed(int speed)
{
	motor[single] = speed;
}

int GetMotorSpeed()
{
	return motor[single];
}

#endif
