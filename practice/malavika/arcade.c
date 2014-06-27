#ifndef ARCADE_C
#define ARCADE_C

task drive()
{
	int deadZone = 15;

	while(true)
	{
		getJoystickSettings(joystick);

		if(joystick.joy1_y2 > 0)
		{
			//positive signs, motors go forward
			if(joystick.joy1_x2 < 0)
			{
				//more right, less left
			}
			else if(joystick.joy1_x2 > 0)
			{
				//more left, less right
			}
		}
		else if(joystick.joy1_y2 < 0)
		{
			//negative signs, motors go backwards
			if(joystick.joy1_x2 < 0)
			{
				//more right, less left
			}
			else if(joystick.joy1_x2 > 0)
			{
				//more left, less right
			}
		}
	}
}

#endif
