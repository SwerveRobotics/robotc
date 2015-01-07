#ifndef AUTO_DRIVE_FUNCTIONS_C
#define AUTO_DRIVE_FUNCTIONS_C

#include "../drive_modes/drive_modes.h"

int WHEEL_DIAMETER = 4;
float GEAR_RATIO = 1.0;

const float TICKS_PER_REVOLUTION = 1440.0;

tMotor ENCODER_MOTOR;

void RegisterEncoderMotor(tMotor motorName)
{
	ENCODER_MOTOR = motorName;
}

int ReadEncoderValue()
{
	return nMotorEncoder[ENCODER_MOTOR];
}

void ResetEncoderValue()
{
	nMotorEncoder[ENCODER_MOTOR] = 0;
}

//Takes an input of encoder ticks and converts to inches
float EncoderDistance(float ticks)
{
	float circumference = PI * WHEEL_DIAMETER;
	float revolutions = (ticks / TICKS_PER_REVOLUTION) * GEAR_RATIO;
	return revolutions * circumference;
}

//Drives forward at given power until the distance has been reached
void DriveForwardDistance(int inches, int power)
{
	ResetEncoderValue();
	while(EncoderDistance(abs(ReadEncoderValue())) < abs(inches))
	{
		DriveForward(power);
	}
	StopAllDriveMotors();
}

//Drives backward at given power until the distance has been reached
void DriveBackwardDistance(int inches, int power)
{
	DriveForwardDistance(inches, -1*power);
}

void DriveForwardTime(int time, int power)
{
	DriveForward(power);
	wait1Msec(time);
	StopAllDriveMotors();
}

void DriveBackwardTime(int time, int power)
{
	DriveForwardTime(time, power);
}

//Turns left at a given power until a time limit is reached
void TurnLeftTime(int time, int power)
{
	TurnLeft(power);
	wait1Msec(time);
	StopAllDriveMotors();
}

//Turns right at a given power until a time limit is reached
void TurnRightTime(int time, int power)
{
	TurnLeftTime(time, -power);
}
#endif
