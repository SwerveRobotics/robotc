#ifndef COLORS_C
#define COLORS_C

typedef enum
{
	BLACK,
	WHITE,
	GREY,
	BLUE,
	RED
}
floorColorEnum;

struct
{
	int min;
	int max;
}
colorRange;

colorRange colorArray[6];

void InitColorVals()
{
	colorArray[BLACK].min = 0;
	colorArray[BLACK].max = 1;
	colorArray[WHITE].min = 2;
	colorArray[WHITE].max = 3;
	colorArray[GREY].min = 4;
	colorArray[GREY].max = 5;
	colorArray[BLUE].min = 6;
	colorArray[BLUE].max = 7;
	colorArray[RED].min = 8;
	colorArray[RED].max = 9;
}

#include "colorDetect.c"

#endif
