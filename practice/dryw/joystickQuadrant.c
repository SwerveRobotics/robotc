#ifndef QUADRANT_C
#define QUADRANT_C

int quad;

int Quadrant()
{
	if(joystick.joy1_x1 > 0 && joystick.joy1_y1 > 0)
	{
		quad = 1;
	}
	//If the joystcik is in quadrant 1, it sets quad to 1

	if(joystick.joy1_x1 < 0 && joystick.joy1_y1 > 0)
	{
		quad = 2;
	}
	//If the joystcik is in quadrant 2, it sets quad to 2

	if(joystick.joy1_x1 < 0 && joystick.joy1_y1 < 0)
	{
		quad = 3;
	}
	//If the joystcik is in quadrant 3, it sets quad to 3

	if(joystick.joy1_x1 > 0 && joystick.joy1_y1 < 0)
	{
		quad = 4;
	}
	//If the joystcik is in quadrant 4, it sets quad to 4

	return quad;
}
#endif
