#ifndef GYRO_DRIVE_C
#define GYRO_DRIVE_C
// Gyro Based Drive Functions

// NOTE: This file relies on the user having correctly defined their
// tank drive mode option from those shown in drive_modes.h

#include "../autonomous/auto_drive.c"
#include "../drive_modes/drive_modes.h"
#include "../sensors/gyro.c"

// May need to calibrate to specific robots
int MOTOR_POWER_SHAVE = 1;

typedef enum
{
	DriveActionForward,
	DriveActionBackward,
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
	startGyro();
	wait1Msec(200);
	// @todo use gyroValid() functionality somehow
	resetGyro();
	ClearTimer(T4);
	bool failed = false;

	bool stopAction = false;
	bool wasTurningRight = false;
	bool wasTurningLeft = false;
	int shavedPower = drivePower;
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
				drivePower = drivePower*-1; // @todo test this
			case DriveActionForward:
				if(EncoderDistance(abs(ReadEncoderValue())) > abs(driveArg)) // hopefully you have configured your encoder!
				{
					break;
				}
				if(readGyro() > 0) // turning right
				{
					// Reset shavedPower if we just switched turn directions //
					wasTurningLeft = true;
					if(wasTurningRight == true)
					{
						wasTurningRight = false;
						shavedPower = drivePower;
					}
					shavedPower = shavedPower - MOTOR_POWER_SHAVE;
					DriveLeftMotors(shavedPower);
					DriveRightMotors(drivePower);
				}
				else if(readGyro() < 0) // turning left
				{
					// Reset shavedPower if we just switched turn directions //
					wasTurningRight = true;
					if(wasTurningLeft == true)
					{
						wasTurningLeft = false;
						shavedPower = drivePower;
					}
					shavedPower = shavedPower - MOTOR_POWER_SHAVE;
					DriveRightMotors(shavedPower);
					DriveLeftMotors(drivePower);
				}
				else
				{
					DriveForward(drivePower);
				}
				wait1Msec(200); // so we don't attempt to adjust power 60 times a second thus reducing one motor power to zero
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
#endif
