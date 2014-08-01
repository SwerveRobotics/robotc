#ifndef PID_CONTROL_C
#define PID_CONTROL_C

#include "JoystickDriver.c"
#include "pid_motors.c"

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
