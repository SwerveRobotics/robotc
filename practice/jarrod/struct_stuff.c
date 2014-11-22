#ifndef STRUCT_STUFF
#define STRUCT_STUFF

#include "enum_stuff.c"

typedef struct
{
	int min;
	int max;
}ColorRange;

ColorRange color[3];

void colorStructInit()
{
	color[BLACK_COLOR].max = 4;
	color[BLACK_COLOR].min = 5;
	color[WHITE_COLOR].max = 6;
	color[WHITE_COLOR].min = 7;
	color[BLUE_COLOR].max = 3;
	color[BLUE_COLOR].min = 9;
}

#endif
