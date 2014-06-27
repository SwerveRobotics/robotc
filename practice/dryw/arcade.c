#ifndef DRIVE_C
#define DRIVE_C

#include "joystickQuadrant.c"

task Drive()
{
	while(true)
	{
		int deadZone = 15;

		quad = Quadrant();

		if(joystick.joy1_y1 < deadZone && joystick.joy1_x1 < deadZone)
		{
			LeftMotorPower(0);
			RightMotorPower(0);
		}

		else if(quad == 1)
		{
			LeftMotorPower(joystick.joy1_y1);
			RightMotorPower(abs(joystick.joy1_x1 - 100));
		}
		else if(quad == 2)
		{
			LeftMotorPower(joystick.joy1_x1 + 100);
			RightMotorPower(joystick.joy1_y1);
		}
		else if(quad == 3)
		{
			LeftMotorPower(0 - abs(joystick.joy1_x1 + 100));
			RightMotorPower(joystick.joy1_y1);
		}
		else if(quad == 4)
		{
			LeftMotorPower(joystick.joy1_y1);
			RightMotorPower(0 - abs(joystick.joy1_x1 - 100));
		}
	}
}
#endif
