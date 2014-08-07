#ifndef DRIVE_C
#define DRIVE_C

#include "enums.c"
#include "structs.c"
#include "initialization.c"
#include "colorDetect.c"

task Drive()
{
	StartTask(Initialize);
	while(true)
	{
		if(SensorValue[colorL] > colorArray[BLACK].min && SensorValue[colorL] > colorArray[BLACK].max)
		{
			LeftMotorPower(100);
			RightMotorPower(50);
		}
		// Turns right if black color is detected

		if(SensorValue[colorL] > colorArray[WHITE].min && SensorValue[colorL] > colorArray[WHITE].max)
		{
			LeftMotorPower(50);
			RightMotorPower(100);
		}
		// Turns left if white color is detected

	}
}
#endif
