// Note only one MOTORS_C file can be included.
// If you are including this file, then any other MOTORS_C file should not be included
// This file is designed to work with PID
#ifndef MOTORS_C
#define MOTORS_C

void RequestLeftMotorSpeed(int speed)
{
	leftMotorRequestedSpeed = speed;
}

void RequestRightMotorSpeed(int speed)
{
	rightMotorRequestedSpeed = speed;
}

void SetLeftMotorSpeed(int speed)
{
	motor[left] = speed;
}

void SetRightMotorSpeed(int speed)
{
	motor[right] = speed;
}

int oldEncoderVal = nMotorEncoder[left];
int CalculateLeftMotorSpeed()
{
	int currentEncoderVal = nMotorEncoder[left];
	int encoderDelta = abs(currentEncoderVal - oldEncoderVal);
	oldEncoderVal = currentEncoderVal;
	return 0; // work in progress

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
