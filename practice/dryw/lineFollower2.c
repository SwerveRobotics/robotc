#ifndef LINE_C
#define LINE_C

#include "colors.c"

task Line()
{
	while(true)
	{
		//If the left sensor detects a black floor, the robot turns left
		//If the right sensor detects a black floor, the robot turns right
		if(OnColor(BLACK, SensorValue[colorL]))
		{
			LeftMotorPower(50);
			RightMotorPower(100);
		}

		if(OnColor(BLACK, SensorValue[colorR]))
		{
			LeftMotorPower(100);
			RightMotorPower(50);
		}
	}
}
#endif
