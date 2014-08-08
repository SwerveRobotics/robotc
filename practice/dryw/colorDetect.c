#ifndef COLORDETECT_C
#define COLORDETECT_C

bool OnColor(floorColorEnum floorColor, int SensorVal)
{
	if(SensorVal > colorArray[floorColor].min && SensorVal > colorArray[floorColor].max)
	{
		return true;
	}

	else
	{
		return false;
	}
	//If the sensor detects a color, it returns true
}
#endif
