#include "joystickdriver.c"

#ifndef JOYSTICK_FUNCTIONS.C
#define JOYSTICK_FUNCTIONS.C

#define TICK_TO_PERCENT_JOY (0.78)

int x = joystick.joy1_x2 * TICK_TO_PERCENT_JOY;
int y = joystick.joy1_y2 * TICK_TO_PERCENT_JOY;

int GetJoystickTranslate()
{
	int angle = atan2(y,x);
	return angle;
}

int GetJoystickPower()
{
	return sqrt( x^2 + y^2 );
}

int GetJoystickTurn()
{
	return joystick.joy1_x1 * TICK_TO_PERCENT_JOY;
}

#endif
