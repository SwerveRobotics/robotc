#ifndef DRIVE_C
#define DRIVE_C

#include "joystickQuadrant.c"

task Drive()
{
	while(true)
	{
		if(Quadrant(Quad) == 1)
		{
			LeftMotorPower(joystick.joy1_y1);
			RightMotorPower(abs(joystick.joy1_x1 - 100));
		}
		else if(Quadrant(Quad) == 2)
		{
			LeftMotorPower(joystick.joy1_x1 + 100);
			RightMotorPower(joystick.joy1_y1);
		}
		else if(Quadrant(Quad) == 3)
		{
			LeftMotorPower(0 - abs(joystick.joy1_x1 + 100));
			RightMotorPower(joystick.joy1_y1);
		}
		else if(Quadrant(Quad) == 4)
		{
			LeftMotorPower(joystick.joy1_y1);
			RightMotorPower(0 - abs(joystick.joy1_x1 - 100));
		}
	}
}
#endif
