#ifndef QUADRANT_C
#define QUADRANT_C

int quad;

int Quadrant()
{
	if(joystick.joy1_x1 > 0 && joystick.joy1_y1 > 0)
	{
		quad = 1;
	}
	if(joystick.joy1_x1 < 0 && joystick.joy1_y1 > 0)
	{
		quad = 2;
	}
	if(joystick.joy1_x1 < 0 && joystick.joy1_y1 < 0)
	{
		quad = 3;
	}
	if(joystick.joy1_x1 > 0 && joystick.joy1_y1 < 0)
	{
		quad = 4;
	}
	return quad;
}
#endif
