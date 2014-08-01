#ifndef CONTROLLER_C
#define CONTROLLER_C

#include "motors_defined.c"

task MotorController()
{
	int deadzone = 15
	while(true)
	{
		getJoystickSettings(joystick);
		if(abs(joystick.joy1_y1) > deadZone)
		{
			SetMotorSpeed(joystick.joy1_y1);
		}
		else
		{
			SetMotorSpeed(0);
		}
	}
}
#endif
