

typedef struct
{
	int min;
	int max;
}ColorRange;
ColorRange BLACK_COLOR;

void InitializeColor(ColorRange range, int min, int max)
{
	range.min = min;
	range.max = max;
}

task main()
{
	InitializeColor(BLACK_COLOR, 300, 350);



}
