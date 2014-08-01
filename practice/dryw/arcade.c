#ifndef DRIVE_C
#define DRIVE_C

task Drive()
{
	int deadZone = 15;

	while(true)
	{
		if(abs(joystick.joy1_y1) < deadZone && abs(joystick.joy1_x1) < deadZone)
		{
			LeftMotorPower(0);
			RightMotorPower(0);
		}

		else
		{
		LeftMotorPower(joystick.joy1_y1 + joystick.joy1_x1);
		RightMotorPower(joystick.joy1_y1 - joystick.joy1_x1)
		}
	}
}
#endif
