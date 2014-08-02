#ifndef DRIVE_C
#define DRIVE_C

enum {black = 0, white = 1, grey = 2, blue = 3, red = 4, unknown = 5};
int floorColorEnum;

struct colorRange {
	int min;
	int max;
};
struct colorRange colorBlue;
task Drive()
{
	while(true)
	{
		colorBlue.min = 5;
		floorColorEnum = 2;
	}
}
#endif
