#ifndef CONTROLLER_C
#define CONTROLLER_C

#include "JoystickDriver.c"

task controller()
{
	while(true)
	{
		getJoystickSettings(joystick);

 		MotorPower(joystick.joy1_y1);
	}
}

#endif
