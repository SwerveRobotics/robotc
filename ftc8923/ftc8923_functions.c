#ifndef FTC8923_FUNCTIONS
#define FTC8923_FUNCTIONS

void GrabGoal()
{
	servo[goalGrabber] = 170;
}

void ReleaseGoal()
{
	servo[goalGrabber] = 100;
}
#endif
