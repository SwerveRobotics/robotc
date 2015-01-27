#ifndef TANK_CONTROLLER_C
#define TANK_CONTROLLER_C

// NOTE: This task relies on the user having correctly defined their
// tank drive mode option from those shown in drive_modes.h

#include "JoystickDriver.c"
#include "../drive_modes/drive_modes.h"
#include "../controllers/controller_defines.h"

int BACKWARD_BUTTON = -1; // Set to non-button so no accidental backwards driving ensues
int SLOW_MODE_BUTTON = -1;
int SLOW_MODE_DIVISOR = 1;

void RegisterBackwardButton(int button)
{
	BACKWARD_BUTTON = button;
}

/* Reverse Drive Recommendation by Darrell
bool ReverseDrive()
{
	// note that short-circuit may cause second term to not get evaluated
	// if backward button is not set
	return (BACKWARD_BUTTON >= 0 && joy1Btn(BACKWARD_BUTTON) == 1);
}

int ReverseDriveMultiplier()
{
	return (ReverseDrive() ? -1 : 1);
}
*/

void RegisterSlowModeButton(int button)
{
	SLOW_MODE_BUTTON = button;
}

void SlowModeDivisor(int divisor)
{
	SLOW_MODE_DIVISOR = divisor;
}

task DriveTank()
{
	while(true)
	{
		getJoystickSettings(joystick);

/* Reverse Drive Recommendation by Darrell
 * Follow this pattern to implement slow drive by looking at the functions I have written.
 * @todo to use these, the functions implemented in tank_4m.c must be also set in tank_2m.c, tank_6m.c, and parallel_pairs.c

		ReverseDriveMotors(ReverseDrive()); // sets motors to correct setting
		if(abs(joystick.joy1_y1)>ANALOG_DEAD_ZONE)
			DriveLeftMotors(ReverseDriveMultiplier()*joystick.joy1_y1);
		else
			StopLeftDriveMotors();

		if(abs(joystick.joy1_y2)>ANALOG_DEAD_ZONE)
			DriveRightMotors(ReverseDriveMultiplier()*joystick.joy1_y2);
		else
			StopRightDriveMotors();
*/


		//Drive forward
		if(BACKWARD_BUTTON < 0 || joy1Btn(BACKWARD_BUTTON) == 0)
		{
			if(abs(joystick.joy1_y1)>ANALOG_DEAD_ZONE)
				DriveLeftMotors(joystick.joy1_y1);
			else
				StopLeftDriveMotors();

			if(abs(joystick.joy1_y2)>ANALOG_DEAD_ZONE)
				DriveRightMotors(joystick.joy1_y2);
			else
				StopRightDriveMotors();
		}

		//slow mode
		if(SLOW_MODE_BUTTON < 0 || joy1Btn(SLOW_MODE_BUTTON) == 0)
		{
			if(abs(joystick.joy1_y1) > ANALOG_DEAD_ZONE)
				DriveLeftMotors(joystick.joy1_y1 / SLOW_MODE_DIVISOR);
			else
				StopLeftDriveMotors();

			if(abs(joystick.joy1_y2) > ANALOG_DEAD_ZONE)
				DriveRightMotors(joystick.joy1_y2 / SLOW_MODE_DIVISOR);
			else
				StopRightDriveMotors();
		}

		//Drive Backward
		else
		{
			if(abs(joystick.joy1_y1)>ANALOG_DEAD_ZONE)
				DriveRightMotors(-1*joystick.joy1_y1);
			else
				StopLeftDriveMotors();

			if(abs(joystick.joy1_y2)>ANALOG_DEAD_ZONE)
				DriveLeftMotors(-1*joystick.joy1_y2);
			else
				StopRightDriveMotors();
		}
	}
}

#endif
