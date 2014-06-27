#ifndef CONTROLLER_C
#define CONTROLLER_C

#include "JoystickDriver.c"

task Controller()
{
	while(true)
	{
		getJoystickSettings(joystick);
	}
}

#endif
