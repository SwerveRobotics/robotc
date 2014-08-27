#ifndef DRIVE_C
#define DRIVE_C

task Drive()
{
	while(true)
	{
		//If the joystick is out of the deazone, some math is done, then that value is given to the motor function
		//Otherwise it's 0
		if(abs(joystick.joy1_y1) > DEADZONE || abs(joystick.joy1_x1) > DEADZONE)
		{
			LeftMotorPower(joystick.joy1_y1 + joystick.joy1_x1);
			RightMotorPower(joystick.joy1_y1 - joystick.joy1_x1);
		}

		else
		{
			LeftMotorPower(0);
			RightMotorPower(0);
		}
	}
}
#endif
