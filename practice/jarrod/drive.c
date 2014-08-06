#ifndef DRIVE_C
#define DRIVE_C

#include "controller.c"
#include "motors_defined.c"

task Drive()
{
	int deadZone = 15;
	while(true)
	{
		getJoystickSettings(joystick);
	}


}
