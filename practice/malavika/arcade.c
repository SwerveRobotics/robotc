#ifndef ARCADE_C
#define ARCADE_C

task drive()
{
	while(true)
	{
		getJoystickSettings(joystick);

		if((abs(joystick.joy1_x1) < deadZone) && (abs(joystick.joy1_y1) < deadZone))
		{
			SetSpeed(left, 0);
			SetSpeed(right, 0);
		}
		else
		{
			SetSpeed(left, joystick.joy1_y1 + joystick.joy1_x1);
			SetSpeed(right, joystick.joy1_y1 - joystick.joy1_x1);
		}
	}
}

#endif
