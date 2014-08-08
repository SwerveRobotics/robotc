#ifndef DRIVE_C
#define DRIVE_C

#include "colors.c"

task Drive()
{
	while(true)
	{
		if(OnColor(BLACK, SensorValue[colorL]))
		{
			LeftMotorPower(100);
			RightMotorPower(50);
		}
		// Turns right if black color is detected

		if(OnColor(WHITE, SensorValue[colorL]))
		{
			LeftMotorPower(50);
			RightMotorPower(100);
		}
		// Turns left if white color is detected

	}
}
#endif
