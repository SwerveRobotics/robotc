#ifndef TANK_C
#define TANK_C

task drive()
{
	while(true)
	{
		getJoystickSettings(joystick);

		if(abs(joystick.joy1_y1) > DEAD_ZONE)
		{
			SetSpeed(left, joystick.joy1_y1);
		}
		else
		{
			SetSpeed(left, 0);
		}

		if(abs(joystick.joy1_y2) > DEAD_ZONE)
		{
			SetSpeed(right, joystick.joy1_y2);
		}
		else
		{
			SetSpeed(right, 0);
		}
	}
}

#endif
