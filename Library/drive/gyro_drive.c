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
	bool failed = false;

	bool stopAction = false;
	bool wasTurningRight = false;
	bool wasTurningLeft = false;
	int shavedPower = drivePower;
	if(driveAction == DriveActionBackward)
	{
		drivePower *= -1; // @todo test this
		shavedPower *= -1;
		MOTOR_POWER_SHAVE *= -1;
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
			// Drive Forward and Drive Backward with the gyro shaves power off of one motor
			// when the Gyro detects any turn degrees.
			case DriveActionBackward:
			case DriveActionForward:
				if(EncoderDistance(abs(ReadEncoderValue())) > abs(driveArg)) // hopefully you have configured your encoder!
				{
					stopAction = true;
					break;
				}

				//readGyro() may need to be divided by some number to not make too big of a change
				DriveRightMotors(drivePower-readGyro());
				DriveLeftMotors(drivePower+readGyro());

				/*
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

				wait1Msec(25); // so we don't attempt to adjust power 60 times a second thus reducing one motor power to zero
				*/
				break;
			case DriveActionTurnLeft:
				TurnLeft(drivePower);
				// Turn until we exceed the requested (absolute) angle
				int angleLeft = abs(readGyro());
				if (angleLeft > driveArg)
					stopAction = true;
				break;
			case DriveActionTurnRight:
				TurnRight(drivePower);
				// Turn until we exceed the requested (absolute) angle
				int angleRight = abs(readGyro());
				if (angleRight > driveArg)
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
