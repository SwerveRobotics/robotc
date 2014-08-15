#ifndef STRUCT_C
#define STRUCT_C

#include "enum.c"

struct
{
	int max;
	int min;
} colorstruct;


colorstruct colors[3];

void InitColorsStruct()
{
	colors[BLACK].min = 4;
	colors[BLACK].max = 5;
	colors[WHITE].min = 6;
	colors[WHITE].max = 7;
	colors[BLUE].min = 3;
	colors[BLUE].max = 9;
}

#endif
