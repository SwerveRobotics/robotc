#ifndef DRIVE_C
#define DRIVE_C

#include "controller_defines.h"
#include "motors.c"
int motorLeft = 0;
int motorRight = 0;

task Drive()
{
	int deadZone = 15;
	while(true)
	{
		getJoystickSettings(joystick);
		motorLeft = AttenuateControllerOutput(joystick.joy1_y1);
		motorRight = AttenuateControllerOutput(joystick.joy1_y2);
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
			SetRightMotorSpeed(joystick.joy1_y2);
		}
		else
		{
			SetRightMotorSpeed(0);
		}

	}
}
#endif
