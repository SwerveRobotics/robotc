#ifndef CONTROL_WITH_PID_C
#define CONTROL_WITH_PID_C

#include "JoystickDriver.c"
#include "pid_motors.c"

int deadZone = 15;

task controller()
{
	while(true)
	{
		getJoystickSettings(joystick);

		if(abs(joystick.joy1_y1) > deadZone)
		{
			RequestMotorSpeed(joystick.joy1_y1);
		}
		else
		{
			RequestMotorSpeed(0);
		}
	}
}

#endif
