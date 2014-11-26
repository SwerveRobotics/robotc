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
void CollectBalls()
{
	motor[collector] = -100;
}
void ReleaseBalls()
{
	motor[collector] = 100;
}
void StopCollector()
{
	motor[collector] = 0;
}
#endif
