#ifndef TANK_CONTROLLER_C
#define TANK_CONTROLLER_C

// NOTE: This task relies on the user having correctly defined their
// tank drive mode option from those shown in drive_modes.h

#include "JoystickDriver.c"
#include "../drive_modes/drive_modes.h"
#include "../controllers/controller_defines.h"

int BACKWARD_BUTTON = -1; // Set to non-button so no accidental backwards driving ensues

void RegisterBackwardButton(int button)
{
	BACKWARD_BUTTON = button;
}

task DriveTank()
{
	while(true)
	{
		getJoystickSettings(joystick);

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
