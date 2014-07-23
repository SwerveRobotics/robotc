#ifndef CONTROLLER_C
#define CONTROLLER_C

#include "JoystickDriver.c"

task Controller()
{
	while(true)
	{
		getJoystickSettings(joystick); //Gets joystick settings so we can give an input to the robot
	}
}

#endif
