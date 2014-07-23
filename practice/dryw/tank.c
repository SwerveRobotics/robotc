#ifndef DRIVE_C
#define DRIVE_C

task Drive()
{
	while(true)
	{
		LeftMotorPower(joystick.joy1_y1);
		RightMotorPower(joystick.joy1_y2);
	}
}
#endif
