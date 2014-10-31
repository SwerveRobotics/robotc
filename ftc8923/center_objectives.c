#ifndef CENTER_OBJECTIVES_C
#define CENTER_OBJECTIVES_C

void RampKickPos1()
{
	/*Robot drive off ramp
	Turns to face center structure
	Knocks down kickstand*/
	DriveForwardDistance(40, 20);
	TurnLeft(100);
	wait1Msec(500);
	DriveForwardDistance(40, 20);
}

void RampKickPos2()
{
	/*Robot drive off ramp
	Turns to face center structure
	Knocks down kickstand*/
	DriveForwardDistance(50, 20);
	TurnLeft(100);
	wait1Msec(500);
	DriveForwardDistance(30, 20);
}

void RampKickPos3()
{
	/*Robot drive off ramp
	Turns to face center structure
	Drives toward center structure
	Turns to face kcikstand
	Knocks down kickstand*/
	DriveForwardDistance(40, 20);
	TurnLeft(100);
	wait1Msec(500);
	DriveForwardDistance(30, 20);
	TurnRight(100);
	wait1Msec(500);
	DriveForwardDistance(10, 20);
}
#endif
