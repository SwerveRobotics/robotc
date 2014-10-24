#ifndef DRIVE_5953_C
#define DRIVE_5953_C

#include "controller_defines.h"
#include "motors.c"

task Drive5953()
{
	int Y_DEADZONE = 100;
	while(true)
	{
		getJoystickSettings(joystick);

		// FORWARD AND REVERSE //
		if(abs(joystick.joy1_y1) > Y_DEADZONE)
		{
			SetLeftMotorSpeed(joystick.joy1_y1);
			SetRightMotorSpeed(joystick.joy1_y1);
		}
		else if((joystick.joy1_x1) > ANALOG_DEAD_ZONE) // STRAFE RIGHT //
		{
			Strafe(joystick.joy1_x1);
		}
		else if((joystick.joy1_x1) < -1.0*ANALOG_DEAD_ZONE) // STRAFE LEFT //
		{
			Strafe(joystick.joy1_x1);
		}
		else if(abs(joystick.joy1_x2) > ANALOG_DEAD_ZONE) // TURN //
		{
			Turn(joystick.joy1_x2);
		}
		else
		{
			Turn(0);
		}
		// ARM //
		if(joy1Btn(5) == 1) // UP //
		{
			MoveArm(ARM_SPEED);
		}
		else if(joy1Btn(7) == 1) // DOWN //
		{
			MoveArm(-1*ARM_SPEED);
		}
		else
		{
			MoveArm(0);
		}
		// BUCKET //
		if(joy1Btn(6) == 1) // UP //
		{
			MoveBucket(BUCKET_SPEED);
		}
		else if(joy1Btn(8) == 1) // DOWN //
		{
			MoveBucket(-1*BUCKET_SPEED);
		}
		else
		{
			MoveBucket(0);
		}

		// JAMMER //
		if(joy1Btn(4) == 1)
		{
			while(joy1Btn(4) == 1) {}
			servo[servo2] = 34;
		}
		else if(joy1Btn(2) == 1)
		{
			while(joy1Btn(2) == 1) {}
			servo[servo2] = 180;
		}
	}
}
#endif
