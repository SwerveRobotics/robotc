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
const int MOTOR_PAIRS_COUNT = (int)PairCountEnd;
tMotor LEFT_MOTORS[MOTOR_PAIRS_COUNT];
tMotor RIGHT_MOTORS[MOTOR_PAIRS_COUNT];

//@todo write a function to store the nubmer of pairs a user has
// then modify the for-loops to not iterate beyond the set pair count
// -> you coul deven set the pair count based on the RegisterDriveMotorPair() function

bool MOTORS_REVERSED = false; // for use with ReverseDriveMotors()

void RegisterDriveMotorPair(tMotor leftMotor, tMotor rightMotor, PairCountEnum pair = 0)
{
	LEFT_MOTORS[pair] = leftMotor;
	RIGHT_MOTORS[pair] = rightMotor;
}

bool MotorsReversed()
{
	return MOTORS_REVERSED;
}

//   ^^
// FL  FR
// FL2 FR2
// FL3 FR3
// FL4 FR4
//   vv

// Designed for use when having the robot drive backwards as though it were driving forwards
// Care still needs to be taken to negate the power direction inputs
void ReverseDriveMotors(bool setReversed)
{
	tMotor oldLeftMotors[MOTOR_PAIRS_COUNT];
	// if the request to reverse does not match the current status, then reverse
	if(MotorsReversed() != setReversed)
	{
		for(unsigned int i=(unsigned int)PairCount1; i<(unsigned int)PairCountEnd; i++)
		{
			oldLeftMotors[i] = LEFT_MOTORS[i];
		}

		for(unsigned int i=(unsigned int)PairCount1; i<(unsigned int)PairCountEnd; i++)
		{
			unsigned int reverseIndex = (unsigned int)PairCountEnd-i-1;
			LEFT_MOTORS[i] = RIGHT_MOTORS[i];
		}

		for(unsigned int i=(unsigned int)PairCount1; i>(unsigned int)PairCountEnd; i++)
		{
			unsigned int reverseIndex = (unsigned int)PairCountEnd-i-1;
			RIGHT_MOTORS[i] = oldLeftMotors[i];
		}

		// Set flag for tracking status
		MOTORS_REVERSED = !MOTORS_REVERSED;
	}
}

void ToggleReverseDriveMotors()
{
	ReverseDriveMotors(MotorsReversed() ? false: true);
}

void DriveLeftMotors(int power)
{
	power *= (MotorsReversed() ? -1: 1);
	for(int i=(int)PairCount1; i<(int)PairCountEnd; i++)
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
	power *= (MotorsReversed() ? -1: 1);
	for(int i=(int)PairCount1; i<(int)PairCountEnd; i++)
	{
		SetMotorPower(RIGHT_MOTORS[i], power);
	}
}

void StopRightDriveMotors()
{
	DriveRightMotors(0);
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
