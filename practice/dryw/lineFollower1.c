#ifndef LINE_C
#define LINE_C

#include "../../Library/sensors/colors.c"

task Line()
{
	while(true)
	{
		//If the sensor detects a black floor, the robot turns right
		//If the sensor detects a white floor, the robot turns left
		if(OnColor(BLACK, SensorValue[colorL]))
		{
			LeftMotorPower(100);
			RightMotorPower(50);
		}

		if(OnColor(WHITE, SensorValue[colorL]))
		{
			LeftMotorPower(50);
			RightMotorPower(100);
		}
	}
}
#endif
