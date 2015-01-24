#ifndef PARALLEL_PAIRS_C
#define PARALLEL_PAIRS_C
// This file allows up to four pairs of motors in parallel. Addiontal pairs of motors can be added easily.
// common drive modes which would make good use of this file include:
// - Tank Drive or Arcade Drive with 2 Motors
// - Tank Drive or Arcade Drive with 4 Motors
// - Tank Drive or Arcade Drive with 6 Motors
// - Tank Drive or Arcade Drive with 8 Motors

// Sample of How to Use This File:
/*
task main()
{
	RegisterDriveMotorPair(leftFront, rightFront, PairCount1);
	RegisterDriveMotorPair(leftMid, rightMid, PairCount2);
	RegisterDriveMotorPair(leftRear, rightRear, PairCount3);
}
*/


#include "../motors/motors.c"

typedef enum
{
	PairCount1,	// front
	PairCount2,
	PairCount3,
	PairCount4,  // back
	PairCountEnd  // NEVER ASSIGN THIS - For Iteration only
}PairCountEnum;
const int MOTOR_PAIRS_COUNT = 4;
tMotor LEFT_MOTORS[MOTOR_PAIRS_COUNT];
tMotor RIGHT_MOTORS[MOTOR_PAIRS_COUNT];

void RegisterDriveMotorPair(tMotor leftMotor, tMotor rightMotor, PairCountEnum pair = 0)
{
	LEFT_MOTORS[pair] = leftMotor;
	RIGHT_MOTORS[pair] = rightMotor;
}

void DriveLeftMotors(int power)
{
	for(int i=PairCount1; i<PairCountEnd; i++)
	{
		SetMotorPower(LEFT_MOTORS[i], power);
	}
}

void StopLeftDriveMotors()
{
	DriveLeftMotors(0);
}

void DriveRightMotors(int power)
{
	for(int i=PairCount1; i<PairCountEnd; i++)
	{
		SetMotorPower(RIGHT_MOTORS[i], power);
	}
}

void StopRightDriveMotors()
{
	DriveRightMotors(0);
}

void MoveForward(int power)
{
	DriveLeftMotors(power);
	DriveRightMotors(power);
}

void MoveBackward(int power)
{
	MoveForward(-1 * power);
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
