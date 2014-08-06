#ifndef SENSORS_C
#define SENSORS_C

#include "colors.c"

struct
{
	int max;
	int min;
} ColorValueStruct ;

ColorValueStruct ColorValues[5];
void InitColorValues()
{
	ColorValues[BLACK_COLOR_ENUM].min = 5;
	ColorValues[BLACK_COLOR_ENUM].max = 5;
	ColorValues[WHITE_COLOR_ENUM].min = 5;
	ColorValues[WHITE_COLOR_ENUM].max = 5;
	ColorValues[BLUE_COLOR_ENUM].min = 5;
	ColorValues[BLUE_COLOR_ENUM].max = 5;
	ColorValues[GREY_COLOR_ENUM].min = 5;
	ColorValues[GREY_COLOR_ENUM].max = 5;
	ColorValues[RED_COLOR_ENUM].min = 5;
	ColorValues[RED_COLOR_ENUM].max = 5;
}


#endif
