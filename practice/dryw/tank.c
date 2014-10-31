#ifndef DRIVE_C
#define DRIVE_C

task Drive()
{
	while(true)
	{
		//If the joystick is out of the deazone, it gives the joystick value to the motor function
		//Otherwise, the left motor power is 0
		if(abs(joystick.joy1_y1) > DEADZONE)
		{
			LeftMotorPower(joystick.joy1_y1);
		}
		else
		{
			LeftMotorPower(0);
		}

		if(abs(joystick.joy1_y2) > DEADZONE)
		{
			RightMotorPower(joystick.joy1_y2);
		}
		else
		{
			RightMotorPower(0);
		}
	}
}
#endif
