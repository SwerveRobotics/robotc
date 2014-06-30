#ifndef CONTROLLERS_C
#define CONTROLLERS_C

#include "JoystickDriver.c"
#include "pid_includes.h"
#include "pid_motors.c"



task Controller()
{
	int deadZone = 15;
	
	while(true)
	{
		getJoystickSettings(joystick);

		if(abs(joystick.joy1_y1) > deadZone)
		{
			RequestLeftMotorSpeed(joystick.joy1_y1); // @todo need to convert output to values in (10,100)
		}
		else
		{
			RequestLeftMotorSpeed(0);
		}
		
		if(abs(joystick.joy1_y2) > deadZone)
		{
			RequestRightMotorSpeed(joystick.joy1_y2); // @todo need to convert output to values in (10,100)
		}
		else
		{
			RequestRightMotorSpeed(0);
		}
		
		// @todo add some options for modifying the PID constants while running using available keys //
		// @todo use some buttons increment and some to descrement //
		// @todo we can display their values on the NXT LCD Screen //
	}
}

#endif
