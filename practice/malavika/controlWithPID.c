#ifndef CONTROL_WITH_PID_C
#define CONTROL_WITH_PID_C

#include "JoystickDriver.c"
#include "motorsPID.c"

int deadZone = 15;

task controller()
{
	while(true)
	{
		getJoystickSettings(joystick);

		SetSpeedIfAboveDeadZone(joystick.joy1_y1, deadZone);
	}
}

#endif
