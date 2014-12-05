#ifndef DRIVE_C
#define DRIVE_C

#include "../Library/drive_modes/tank_4m.c"
#include "JoystickDriver.c"

task Drive()
{
	while(true)
	{
		getJoystickSettings(joystick);

		//If the left joystick is out out of the deadzone, the left motors are powered
		if(abs(joystick.joy1_y1) > ANALOG_DEAD_ZONE)
		{
			motor[mtrFL] = joystick.joy1_y1;
			motor[mtrBL] = joystick.joy1_y1;
		}
		else
		{
			motor[mtrFL] = 0;
			motor[mtrBL] = 0;
		}

		//If the right joystick is out out of the deadzone, the right motors are powered
		if(abs(joystick.joy1_y2) > ANALOG_DEAD_ZONE)
		{
			motor[mtrFR] = joystick.joy1_y2;
			motor[mtrBR] = joystick.joy1_y2;
		}
		else
		{
			motor[mtrFR] = 0;
			motor[mtrBR] = 0;
		}
	}
}
#endif
