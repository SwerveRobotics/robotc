#ifndef DRIVE_ARCADE_C
#define DRIVE_ARCADE_C

#include "motors.c"

task DriveArcade()
{
	int deadZone = 15;
	while(true)
	{
		getJoystickSettings(joystick);

		// Left Analog Stick //
		float x1 = joystick.joy1_x1;
		float y1 = joystick.joy1_y1;

		// Arcade Drive Uses Only Left Analog Stick //
		if(abs(x1) > deadZone || abs(y1) > deadZone)
		{
			x1 = x1*0.5;
			SetLeftMotorSpeed(x1+y1);
			SetRightMotorSpeed(-x1+y1);
		}
		else
		{
			SetLeftMotorSpeed(0);
			SetRightMotorSpeed(0);
		}
	}
}
#endif
