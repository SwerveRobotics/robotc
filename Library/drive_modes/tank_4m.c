#ifndef TANK_4M_C
#define TANK_4M_C
//This is a 4 motor tank drive

#include "../motors/motors.c"

tMotor FRONT_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;

void RegisterDriveMotors(tMotor FleftMotor, tMotor BleftMotor, tMotor FrightMotor, tMotor BrightMotor)
{
	FRONT_LEFT_MOTOR = FleftMotor;
	BACK_LEFT_MOTOR = BleftMotor;
	FRONT_RIGHT_MOTOR = FrightMotor;
	BACK_RIGHT_MOTOR = BrightMotor;
}

void DriveLeftMotors(int speed)
{
	SetMotorSpeed (FRONT_LEFT_MOTOR, speed);
	SetMotorSpeed (BACK_LEFT_MOTOR, speed);
}

void DriveRightMotors(int speed)
{
	SetMotorSpeed (FRONT_RIGHT_MOTOR, speed);
	SetMotorSpeed (BACK_RIGHT_MOTOR, speed);
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
	DriveRightMotors(speed);
	DriveLeftMotors(-1*speed);
}

void TurnRight(int speed)
{
	TurnLeft(-1*speed);
}

#endif
