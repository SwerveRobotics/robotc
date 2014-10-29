#ifndef JOYSTICK_SWIVE_FUNCTIONS.C
#define JOYSTICK_SWIVE_FUNCTIONS.C

#include "joystickdriver.c"

#define TICK_TO_PERCENT_JOY (0.78)

int x = joystick.joy1_x2 * TICK_TO_PERCENT_JOY;
int y = joystick.joy1_y2 * TICK_TO_PERCENT_JOY;

int GetJoystickTranslate()//return the angle of the right stick
{
	int angle = atan2(y,x);
	return angle;
}

int GetJoystickPower()//return the magnitude of the right stick
{
	int dist = sqrt( x^2 + y^2 );
	return dist;
}

int GetJoystickTurn()//return the X value of the left stick, to determine the desired rotation rate
{
	return joystick.joy1_x1 * TICK_TO_PERCENT_JOY;
}

#endif
