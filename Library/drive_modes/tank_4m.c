#ifndef TANK_4M_C
#define TANK_4M_C
//This is a 4 motor tank drive

#include "../motors/motors.c"

tMotor FRONT_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;

void RegisterDriveMotors(tMotor frontLeftM, tMotor backLeftM, tMotor frontRightM, tMotor backRightM)
{
	FRONT_LEFT_MOTOR = frontLeftM;
	BACK_LEFT_MOTOR = backLeftM;
	FRONT_RIGHT_MOTOR = frontRightM;
	BACK_RIGHT_MOTOR = backRightM;
}

void DriveLeftMotors(int power)
{
	SetMotorPower(FRONT_LEFT_MOTOR, power);
	SetMotorPower(BACK_LEFT_MOTOR, power);
}

void StopLeftDriveMotors()
{
	DriveLeftMotors(0);
}

void DriveRightMotors(int power)
{
	SetMotorPower(FRONT_RIGHT_MOTOR, power);
	SetMotorPower(BACK_RIGHT_MOTOR, power);
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
	DriveRightMotors(power);
	DriveLeftMotors(-1 * power);
}

void TurnRight(int power)
{
	TurnLeft(-1 * power);
}

#endif
