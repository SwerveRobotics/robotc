#ifndef COLORS_C
#define COLORS_C

typedef enum
{
	BLACK_COLOR_ENUM,
	WHITE_COLOR_ENUM,
	BLUE_COLOR_ENUM,
	GREY_COLOR_ENUM,
	RED_COLOR_ENUM
} ColorsEnum;

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
