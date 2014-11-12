#ifndef TANK_CONTROLLER_C
#define TANK_CONTROLLER_C

// NOTE: This task relies on the user having correctly defined their
// tank drive mode option from those shown in drive_modes.h

#include "JoystickDriver.c"
#include "../drive_modes/drive_modes.h"
#include "../controllers/controller_defines.h"

task DriveTank()
{
	while(true)
	{
		getJoystickSettings(joystick);

		if(abs(joystick.joy1_y1)>ANALOG_DEAD_ZONE)
			DriveLeftMotors(joystick.joy1_y1);
		else
			StopLeftDriveMotors();

		if(abs(joystick.joy1_y2)>ANALOG_DEAD_ZONE)
			DriveRightMotors(joystick.joy1_y2);
		else
			StopRightDriveMotors();
	}
}

#endif
