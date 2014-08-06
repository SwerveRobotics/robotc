#ifndef DRIVE_C
#define DRIVE_C

#include "enums.c"
#include "structs.c"

task Drive()
{
	colorArray[UNKNOWN].min = 0;
	colorArray[UNKNOWN].max = 1;
	colorArray[BLACK].min = 2;
	colorArray[BLACK].max = 3;
	colorArray[WHITE].min = 4;
	colorArray[WHITE].max = 5;
	colorArray[GREY].min = 6;
	colorArray[GREY].max = 7;
	colorArray[BLUE].min = 8;
	colorArray[BLUE].max = 9;
	colorArray[RED].min = 10;
	colorArray[RED].max = 11;

	while(true)
	{

	}
}
#endif
