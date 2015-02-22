#ifndef DRIVE_ARCADE_C
#define DRIVE_ARCADE_C

// NOTE: This task relies on the user having correctly defined their
// tank drive mode option from those shown in drive_modes.h

// ARCADE controller can work with any of the left-right drive modes

#include "JoystickDriver.c"
#include "../drive_modes/drive_modes.h"
#include "../controllers/controller_defines.h"

task DriveArcade()
{
	while(true)
	{
		getJoystickSettings(joystick);

		// Left Analog Stick //
		float x1 = joystick.joy1_x1;
		float y1 = joystick.joy1_y1;

		// Arcade Drive Uses Only Left Analog Stick //
		if(abs(x1) > ANALOG_DEAD_ZONE || abs(y1) > ANALOG_DEAD_ZONE)
		{
			//Makes driving strait easier
			x1 = x1*0.5;

			DriveLeftMotors(x1+y1);
			DriveRightMotors(-x1+y1);
		}
		else
		{
			StopAllDriveMotors();
		}
	}
}
#endif
