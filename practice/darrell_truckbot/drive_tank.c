#ifndef DRIVE_TANK_C
#define DRIVE_TANK_C

#include "controller_defines.h"
#include "motors.c"

task DriveTank()
{
	while(true)
	{
		getJoystickSettings(joystick);

		// REVERSED CONTROL //
		if(joy1Btn(5) == 1 && joy1Btn(6) == 1)
		{
			// Right Control //
			if(abs(joystick.joy1_y1) > ANALOG_DEAD_ZONE)
			{
				SetRightMotorSpeed(-1*joystick.joy1_y1);
			}
			else
			{
				SetRightMotorSpeed(0);
			}
			// Left Control //
			if(abs(joystick.joy1_y2) > ANALOG_DEAD_ZONE)
			{
				SetLeftMotorSpeed(-1*joystick.joy1_y2);
			}
			else
			{
				SetLeftMotorSpeed(0);
			}

		}
		else // STANDARD CONTROL //
		{
			// Left Motor Control //
			if(abs(joystick.joy1_y1) > ANALOG_DEAD_ZONE)
			{
				SetLeftMotorSpeed(joystick.joy1_y1);
			}
			else
			{
				SetLeftMotorSpeed(0);
			}

			// Right Motor Control //
			if(abs(joystick.joy1_y2) > ANALOG_DEAD_ZONE)
			{
				SetRightMotorSpeed(joystick.joy1_y2);
			}
			else
			{
				SetRightMotorSpeed(0);
			}
		}
		wait1Msec(10);
	}
}
#endif
