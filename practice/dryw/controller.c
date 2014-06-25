#ifndef CONTROLLER_C
#define CONTROLLER_C

#include "JoystickDriver.c"

task controller()
{
	while(true)
	{
		getJoystickSettings(joystick);

 		LeftMotorPower(joystick.joy1_y1);
 		RightMototPower(joystick.joy1_y2);
	}
}

#endif
