#ifndef COLORDETECT_C
#define COLORDETECT_C

//If the sensor detects a color, it returns true
//Otherwise it returns false
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

}
#endif
