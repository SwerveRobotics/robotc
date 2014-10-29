#ifndef AUTODRIVEFUNCTIONS_C
#define AUTODRIVEFUNCTIONS_C

#include "motors.c"

void DriveStrait(int power)
{
	LeftMotorPower(power);
	RightMotorPower(power);
}

void TurnRight(int rightPower)
{
	RightMotorPower(rightPower);
}

void TurnLeft(int leftPower)
{
	LeftMotorPower(leftPower);
}

#endif
