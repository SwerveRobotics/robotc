#ifndef CONTROLLER_C
#define CONTROLLER_C

#include "JoystickDriver.c"
#include "motors.c"

task controller()
{
	while(true)
	{
		getJoystickSettings(joystick);
	}
}

#endif
