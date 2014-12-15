#ifndef GYRO_DRIVE_C
#define GYRO_DRIVE_C
// Gyro Based Drive Functions

// NOTE: This file relies on the user having correctly defined their
// tank drive mode option from those shown in drive_modes.h

#include "../autonomous/auto_drive.c"
#include "../drive_modes/drive_modes.h"
#include "../sensors/gyro.c"

// May need to calibrate to specific robots
int MOTOR_POWER_SHAVE = 3;

typedef enum
{
	DriveActionForward,
	DriveActionBackward,
	DriveActionForwardForever,
	DriveActionBackwardForever,
	DriveActionTurnLeft,
	DriveActionTurnRight
} DriveActionEnum;

///@todo: write a time protection so that we don't turn longer than some given time
// Depending on driveAction, this will turn driveArg degrees or drive forward or backward driveArg inches at
// a power of drivePower
void GyroDrive(DriveActionEnum driveAction, int driveArg, int drivePower)
{
	StopAllDriveMotors();
	wait1Msec(250); //The wait is here to ensure the robot comes to a stop before calibrating the gyro
	ResetEncoderValue();
	startGyro();
	while(!gyroValid()) {} // @todo should have a timeout here
	resetGyro();
	ClearTimer(T4);
	time1[T3] = 0;
	bool failed = false;
	bool stopAction = false;

	if(driveAction == DriveActionBackward || driveAction == DriveActionTurnLeft)
	{
		drivePower *= -1;
	}
	// Action loop
	while(true)
	{
		if(stopAction == true)
			break;
		// Stop if the gyro reading is invalid
		if (!gyroValid())
		{
			failed = true;
			break;
		}
		switch(driveAction)
		{
			//Driving strait code
			case DriveActionBackward:
			case DriveActionForward:
				//If the distance has been reached, it stops running
				if(EncoderDistance(abs(ReadEncoderValue())) > abs(driveArg)) // hopefully you have configured your encoder!
				{
					stopAction = true;
					break;
				}
				//If the robot hasn't stopped after 10 seconds, it breaks
				if(time1[T3] == 10000)
				{
					stopAction = true;
					break;
				}
				//Adjusts power according to gyro reading
				DriveRightMotors(drivePower+readGyro()*5);
				DriveLeftMotors(drivePower-readGyro()*5);
				break;
			//Turning code
			case DriveActionTurnLeft:
			case DriveActionTurnRight:
				//If the robot hasn't stopped after 5 seconds, it breaks
				if(time1[T3] == 5000)
				{
					stopAction = true;
					break;
				}
				//Turns until requested angle is reached
				TurnRight(drivePower);
				int angle = abs(readGyro());
				if (angle > driveArg)
					stopAction = true;
				break;
		}
	}
	StopAllDriveMotors();
	stopGyro();
}

void TurnLeftDegrees(int degrees, int power)
{
	GyroDrive(DriveActionTurnLeft, degrees-LEFT_TURN_GYRO_OVERRUN, power);
}

void TurnRightDegrees(int degrees, int power)
{
	GyroDrive(DriveActionTurnRight, degrees-RIGHT_TURN_GYRO_OVERRUN, power);
}

void DriveForwardDistanceGyro(int distance, int power)
{
	GyroDrive(DriveActionForward, distance, power);
}

void DriveBackwardDistanceGyro(int distance, int power)
{
	GyroDrive(DriveActionBackward, distance, power);
}












bool wasTurningRight = false;
bool wasTurningLeft = false;
int shavedPower = 0;

void InitSpecialGyroDrive(DriveActionEnum driveAction, int drivePower)
{
	wasTurningRight = false;
	wasTurningLeft = false;
	shavedPower = drivePower;
	if(driveAction == DriveActionBackward)
	{
		drivePower *= -1;
		shavedPower *= -1;
		MOTOR_POWER_SHAVE *= -1;
	}
}

bool SpecialGyroDrive(DriveActionEnum driveAction, int drivePower)
{
	// Stop if the gyro reading is invalid
	if (!gyroValid() || shavedPower == 0)
	{
		return false;
	}
	if(readGyro() > 1) // turning right
	{
		// Reset shavedPower if we just switched turn directions //
		wasTurningLeft = true;
		if(wasTurningRight == true)
		{
			wasTurningRight = false;
			shavedPower = drivePower;
		}
		shavedPower = shavedPower - (MOTOR_POWER_SHAVE);
		DriveLeftMotors(shavedPower);
		DriveRightMotors(drivePower);
	}
	else if(readGyro() < -1) // turning left
	{
		// Reset shavedPower if we just switched turn directions //
		wasTurningRight = true;
		if(wasTurningLeft == true)
		{
			wasTurningLeft = false;
			shavedPower = drivePower;
		}
		shavedPower = shavedPower - (MOTOR_POWER_SHAVE);
		DriveRightMotors(shavedPower);
		DriveLeftMotors(drivePower);
	}
	else
	{
		DriveForward(drivePower);
	}
	return true;
}












#endif
