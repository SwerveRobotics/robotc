#ifndef INITIALIZATION_C
#define INITIALIZATION_C

#include "manipulators.c"


void InitializeFan()
{
	FAN.running = false;
}

void InitializeGrabber()
{
	GRABBER.grabbed = false;
	ReleaseGoal();
}

void InitializeSweeper()
{
	SWEEPER.running = false;
	SWEEPER.raised = true;
	StopSweeperServos();
}

void InitializeTube()
{
	TUBE.position = 0;
	RetractTube();
}

void InitializeAll()
{
	ASSUME_CONTROLLER_INPUT = false;
	InitializeTube();
	InitializeSweeper();
	InitializeGrabber();
	InitializeFan();
}

#endif
