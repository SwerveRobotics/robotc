#ifndef COLORS_C
#define COLORS_C

//These are the colors we will be detecting with the color sensor for the line follower
typedef enum
{
	BLACK_COLOR,
	WHITE_COLOR,
	GREY_COLOR,
	BLUE_COLOR,
	RED_COLOR
}
FloorColorEnum;

//This struct is for the minimum and maximum values of each color to give us a range to detect a color
struct
{
	int min;
	int max;
}
ColorRange;

ColorRange colorArray[5];

//Sets the color minimums and maximums
void InitColorVals()
{
	colorArray[BLACK_COLOR].min = 0;
	colorArray[BLACK_COLOR].max = 22;
	colorArray[WHITE_COLOR].min = 23;
	colorArray[WHITE_COLOR].max = 30;
	colorArray[GREY_COLOR].min = 4;
	colorArray[GREY_COLOR].max = 5;
	colorArray[BLUE_COLOR].min = 6;
	colorArray[BLUE_COLOR].max = 7;
	colorArray[RED_COLOR].min = 8;
	colorArray[RED_COLOR].max = 9;
}

//If the sensor detects a color, it returns true and displays the color
//Otherwise it returns false and displays "Unknown"
bool OnColor(floorColorEnum floorColor, int SensorVal)
{
	if(SensorVal > colorArray[floorColor].min && SensorVal > colorArray[floorColor].max)
	{
		return floorColor;
	}
	else
	{
		return false;
	}
}
#endif
