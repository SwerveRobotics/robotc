#ifndef CONTROLLER_C
#define CONTROLLER_C

#include "JoystickDriver.c"

int DEADZONE = 15;

//Gets joystick settings so we can give an input to the robot
task Controller()
{
	while(true)
	{
		getJoystickSettings(joystick);
	}
}

#endif
