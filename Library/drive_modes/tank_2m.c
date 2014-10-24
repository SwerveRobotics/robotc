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

void DriveLeftMotors(int power)
{
	SetMotorPower(LEFT_MOTOR, power);
}

void StopLeftDriveMotors()
{
	DriveLeftMotors(0);
}

void DriveRightMotors(int power)
{
	SetMotorPower(RIGHT_MOTOR, power);
}

void StopRightDriveMotors()
{
	DriveRightMotors(0);
}

void StopAllDriveMotors()
{
	StopLeftDriveMotors();
	StopRightDriveMotors();
}

void DriveForward(int power)
{
	DriveLeftMotors(power);
	DriveRightMotors(power);
}

void DriveBackward(int power)
{
	DriveForward(-1 * power);
}

void TurnLeft(int power)
{
	DriveLeftMotors(-1 * power);
	DriveRightMotors(power);
}

void TurnRight(int power)
{
	TurnLeft(-1 * power);
}



#endif
