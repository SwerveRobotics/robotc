#ifndef CONTROLLERS_C
#define CONTROLLERS_C

#include "motors.c"

task MotorController()
{
	int deadZone = 15;
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
