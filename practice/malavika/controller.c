#ifndef CONTROLLER_C
#define CONTROLLER_C

#include "JoystickDriver.c"
#include "motors.c"

int deadZone = 15;

task controller()
{
	while(true)
	{
		getJoystickSettings(joystick);

		SetSpeed(joystick.joy1_y1, deadZone);
	}
}

#endif
