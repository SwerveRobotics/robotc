#ifndef DRIVE_C
#define DRIVE_C

task Drive()
{
	while(true)
	{
		int deadZone = 15;

		if(joystick.joy1_y1 > deadZone)
		{
			LeftMotorPower(joystick.joy1_y1);
		}
		else
		{
			LeftMotorPower(0);
		}
		if(joystick.joy1_y2 > deadZone)
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
