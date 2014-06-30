// Note only one MOTORS_C file can be included.
// If you are including this file, then any other MOTORS_C file should not be included
// This file is designed to work with PID
#ifndef MOTORS_C
#define MOTORS_C

void RequestLeftMotorSpeed(int speed = 0)
{
	leftMotorRequestedSpeed = speed;
}

void RequestRightMotorSpeed(int speed = 0)
{
	rightMotorRequestedSpeed = speed;
}

void SetLeftMotorSpeed(int speed = 0)
{
	motor[left] = speed;
}

void SetRightMotorSpeed(int speed = 0)
{
	motor[right] = speed;
}

int GetLeftMotorSpeed()
{
	return motor[left];
}

int GetRightMotorSpeed()
{
	return motor[right];
}

#endif
