#ifndef DRIVE_C
#define DRIVE_C

#include "JoystickDriver.c"
#include "../library/controllers/controller_defines.h"
#include "../library/drive_modes/tank_2m.c"

task Drive()
{
	while(true)
	{
		getJoystickSettings(joystick);

		// Left Motor Control //
		if(abs(joystick.joy1_y1) > CONTROLLER_DEAD_ZONE)
		{
			DriveLeftMotors(joystick.joy1_y1);
		}
		else
		{
			DriveLeftMotors(0);
		}

		// Right Motor Control //
		if(abs(joystick.joy1_y2) > CONTROLLER_DEAD_ZONE)
		{
			DriveRightMotors(joystick.joy1_y2);
		}
		else
		{
			DriveRightMotors(0);
		}

	}
}
#endif
