#ifndef COLORDETECT_C
#define COLORDETECT_C

bool OnColor(floorColorEnum floorColor, int SensorVal)
{
	if(SensorValue[colorL] > colorArray[BLACK].min && SensorValue[colorL] > colorArray[BLACK].max)
	{
		nxtDisplayTextLine(0, "Black");
		return true;
	}

	else if(SensorValue[colorL] > colorArray[WHITE].min && SensorValue[colorL] > colorArray[WHITE].max)
	{
		nxtDisplayTextLine(0, "White");
		return true;
	}

	else if(SensorValue[colorL] > colorArray[GREY].min && SensorValue[colorL] > colorArray[GREY].max)
	{
		nxtDisplayTextLine(0, "Grey");
		return true;
	}

	else if(SensorValue[colorL] > colorArray[BLUE].min && SensorValue[colorL] > colorArray[BLUE].max)
	{
		nxtDisplayTextLine(0, "Blue");
		return true;
	}

	else if(SensorValue[colorL] > colorArray[RED].min && SensorValue[colorL] > colorArray[RED].max)
	{
		nxtDisplayTextLine(0, "Red");
		return true;
	}

	else
	{
		return false;
	}
	//If the sensor detects a color, it says which one
}

#endif
