#ifndef DRIVE_C
#define DRIVE_C

task Drive()
{
	int deadZone = 15;

	while(true)
	{
		if(abs(joystick.joy1_y1) > deadZone)
		{
			LeftMotorPower(joystick.joy1_y1);
			//If the left joystick is out of the deazone, it gives the left motor a power value that corresponds to the joystick value
		}
		else
		{
			LeftMotorPower(0);
			//Otherwise, the left motor power is 0
		}

		if(abs(joystick.joy1_y2) > deadZone)
		{
			RightMotorPower(joystick.joy1_y2);
			//If the right joystick is out of the deazone, it gives the right motor a power value that corresponds to the joystick value
		}
		else
		{
			RightMotorPower(0);
			//Otherwise, the right motor power is 0
		}

	}
}
#endif
