#ifndef COLORDETECT_C
#define COLORDETECT_C

//If the sensor detects a color, it returns true and displays the color
//Otherwise it returns false and displays "Unknown"
bool OnColor(floorColorEnum floorColor, int SensorVal)
{
	if(SensorVal > colorArray[floorColor].min && SensorVal > colorArray[floorColor].max)
	{
		nxtDisplayTextLine(0, "%d", floorColor);
		return true;
	}

	else
	{
		nxtDisplayTextLine(0, "Unknown");
		return false;
	}

}
#endif
