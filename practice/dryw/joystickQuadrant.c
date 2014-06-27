#ifndef QUADRANT_C
#define QUADRANT_C

int Quadrant(int Quad)
{
	if(joystick.joy1_x1 > 0 && joystick.joy1_y1 > 0)
	{
		Quad = 1;
	}
	if(joystick.joy1_x1 < 0 && joystick.joy1_y1 > 0)
	{
		Quad = 2;
	}
	if(joystick.joy1_x1 < 0 && joystick.joy1_y1 < 0)
	{
		Quad = 3;
	}
	if(joystick.joy1_x1 > 0 && joystick.joy1_y1 < 0)
	{
		Quad = 4;
	}
	return Quad;
}
#endif
