#ifndef DRIVE_C
#define DRIVE_C

#include "motors.c"

task Drive()
{
	int deadZone = 15;
	while(true)
	{
		getJoystickSettings(joystick);

		// Left Motor Control //
		if(abs(joystick.joy1_y1) > deadZone)
		{
			SetLeftMotorSpeed(joystick.joy1_y1);
		}
		else
		{
			SetLeftMotorSpeed(0);
		}

		// Right Motor Control //
		if(abs(joystick.joy1_y2) > deadZone)
		{
			SetRightMotorSpeed(joystick.joy1_y1);
		}
		else
		{
			SetRightMotorSpeed(0);
		}

	}
}
#endif
