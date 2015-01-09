#ifndef MOTORS_C
#define MOTORS_C

void LeftMotorspeed(int speed)
{
	motor[Left] = speed;
}

void RightMotorSpeed(int speed)
{
	motor[Right] = speed;
}

#endif
