#ifndef SENSORS_C
#define SENSORS_C

#include "colors.c"

bool LightSensorOnColor(ColorsEnum color, int sensorVal)
{
	if(sensorVal > ColorValues[color].min && sensorVal < ColorValues[color].max)
	{
		return true;
	}
	return false;
}


#endif
