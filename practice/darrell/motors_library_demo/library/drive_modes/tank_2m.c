#ifndef TANK_2M_C
#define TANK_2M_C
// Drive Mode: Tank
// Number of Motors: 2

#include "../motors/motors.c"

tMotor LEFT_MOTOR;
tMotor RIGHT_MOTOR;

void RegisterDriveMotors(tMotor leftM, tMotor rightM)
{
	LEFT_MOTOR = leftM;
	RIGHT_MOTOR = rightM;
}

void DriveLeftMotors(int speed)
{
	SetMotorSpeed(LEFT_MOTOR, speed);
}

void DriveRightMotors(int speed)
{
	SetMotorSpeed(RIGHT_MOTOR, speed);
}

void DriveForward(int speed)
{
	DriveLeftMotors(speed);
	DriveRightMotors(speed);
}

void DriveBackward(int speed)
{
	DriveForward(-1*speed);
}

void TurnLeft(int speed)
{
	DriveLeftMotors(speed);
	DriveRightMotors(-1*speed);
}

void TurnRight(int speed)
{
	TurnLeft(-1*speed);
}

#endif
