#ifndef DRIVE_C
#define DRIVE_C

#include "../Library/drive_modes/tank_4m.c"
#include "JoystickDriver.c"

task Drive()
{
	while(true)
	{
		getJoystickSettings(joystick);

		//If the left joystick is out out of the deadzone, the left motors are powered
		if(joystick.joy1_y1 > ANALOG_DEAD_ZONE)
		{
			DriveLeftMotors(joystick.joy1_y1);
		}
		else
		{
			DriveLeftMotors(0);
		}

		//If the right joystick is out out of the deadzone, the right motors are powered
		if(joystick.joy1_y2 > ANALOG_DEAD_ZONE)
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
