#ifndef TANK_4M_C
#define TANK_4M_C
//This is a 4 motor tank drive

#include "../motors/motors.c"

tMotor FRONT_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;

bool MOTORS_REVERSED = false; // for use with ReverseDriveMotors()

void RegisterDriveMotors(tMotor frontLeftM, tMotor backLeftM, tMotor frontRightM, tMotor backRightM)
{
	FRONT_LEFT_MOTOR = frontLeftM;
	BACK_LEFT_MOTOR = backLeftM;
	FRONT_RIGHT_MOTOR = frontRightM;
	BACK_RIGHT_MOTOR = backRightM;
}

bool MotorsReversed()
{
	return MOTORS_REVERSED;
}

// Designed for use when having the robot drive backwards as though it were driving forwards
// Care still needs to be taken to negate the power direction inputs
void ReverseDriveMotors(bool setReversed)
{
	// if the request to reverse does not match the current status, then reverse
	if(MotorsReversed() != setReversed)
	{
		tMotor oldFrontLeftMotor = FRONT_LEFT_MOTOR;
		tMotor oldBackLeftMotor = BACK_LEFT_MOTOR;

		FRONT_LEFT_MOTOR = BACK_RIGHT_MOTOR;
		BACK_LEFT_MOTOR = FRONT_RIGHT_MOTOR;

		FRONT_RIGHT_MOTOR = oldBackLeftMotor;
		BACK_RIGHT_MOTOR = oldFrontLeftMotor;

		// Set flag for tracking status
		MOTORS_REVERSED = !MOTORS_REVERSED;
	}
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
