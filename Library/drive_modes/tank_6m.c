#ifndef TANK_6M_C
#define TANK_6M_C
//this is a 6 motor tank drive

#include "../motors/motors.c"

tMotor FRONT_LEFT_MOTOR;
tMotor MID_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor MID_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;

void RegisterDriveMotors(tMotor frontLeftM, tMotor midLeftM, tMotor backLeftM, tMotor frontRightM, tMotor midRightM, tMotor backRightM)
{
	FRONT_LEFT_MOTOR = frontLeftM;
	MID_LEFT_MOTOR = midLeftM;
	BACK_LEFT_MOTOR = backLeftM;
	FRONT_RIGHT_MOTOR = frontRightM;
	MID_RIGHT_MOTOR = midRightM;
	BACK_RIGHT_MOTOR = backRightM;

}

void MoveForward(int power)
{
	SetMotorPower(FRONT_LEFT_MOTOR, power);
	SetMotorPower(MID_LEFT_MOTOR, power);
	SetMotorPower(BACK_LEFT_MOTOR, power);
	SetMotorPower(FRONT_RIGHT_MOTOR, power);
	SetMotorPower(MID_RIGHT_MOTOR, power);
	SetMotorPower(BACK_RIGHT_MOTOR, power);
}

void MoveBackward(int power)
{
	MoveForward(-1 * power);
}

void DriveLeftMotors(int power)
{
	SetMotorPower(FRONT_LEFT_MOTOR, power);
	SetMotorPower(MID_LEFT_MOTOR, power);
	SetMotorPower(BACK_LEFT_MOTOR, power);
}

void StopLeftDriveMotors()
{
	DriveLeftMotors(0);
}

void DriveRightMotors(int power)
{
	SetMotorPower(FRONT_RIGHT_MOTOR, power);
	SetMotorPower(MID_RIGHT_MOTOR, power);
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
