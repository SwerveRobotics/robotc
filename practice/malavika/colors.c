#ifndef COLORS_C
#define COLORS_C

typedef enum
{
	BLACK,
	WHITE,
	GREY,
	BLUE,
	RED,
	UNKNOWN
} FloorColorEnum;

typedef struct
{
	int min;
	int max;
}ColorRange;

ColorRange colorsArray[6];

void IntializeColors()
{
	colorsArray[BLACK].min = 0;
	colorsArray[BLACK].max = 1;
	colorsArray[WHITE].min = 2;
	colorsArray[WHITE].max = 3;
	colorsArray[GREY].min = 4;
	colorsArray[GREY].max = 5;
	colorsArray[BLUE].min = 6;
	colorsArray[BLUE].max = 7;
	colorsArray[RED].min = 8;
	colorsArray[RED].max = 9;
	colorsArray[UNKNOWN].min = 10;
	colorsArray[UNKNOWN].max = 11;
}

bool OnColor(FloorColorEnum floorColor, int sensorVal)
{
	if(sensorVal > colorsArray[floorColor].min && sensorVal < colorsArray[floorColor].max)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif
