#ifndef COLORDETECT_C
#define COLORDETECT_C

void ColorDetect()
{
	if(SensorValue[colorL] > colorArray[BLACK].min && SensorValue[colorL] > colorArray[BLACK].max)
	{
		nxtDisplayTextLine(0, "Black");
	}

	else if(SensorValue[colorL] > colorArray[WHITE].min && SensorValue[colorL] > colorArray[WHITE].max)
	{
		nxtDisplayTextLine(0, "White");
	}

	else if(SensorValue[colorL] > colorArray[GREY].min && SensorValue[colorL] > colorArray[GREY].max)
	{
		nxtDisplayTextLine(0, "Grey");
	}

	else if(SensorValue[colorL] > colorArray[BLUE].min && SensorValue[colorL] > colorArray[BLUE].max)
	{
		nxtDisplayTextLine(0, "Blue");
	}

	else if(SensorValue[colorL] > colorArray[RED].min && SensorValue[colorL] > colorArray[RED].max)
	{
		nxtDisplayTextLine(0, "Red");
	}
	//If the sensor detects a color, it says which one
}

#endif
