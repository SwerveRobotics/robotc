#ifndef CENTER_OBJECTIVES_C
#define CENTER_OBJECTIVES_C

void RampKickPos1()
{
	/*Robot drive off ramp
	Turns to face center structure
	Knocks down kickstand*/
	DriveForwardDistance(20, 100);
	TurnLeftDegrees(90, 100);
	DriveForwardDistance(30, 100);
}

void RampKickPos2()
{
	/*Robot drive off ramp
	Turns to face center structure
	Knocks down kickstand*/
	DriveForwardDistance(30, 100);
	TurnLeftDegrees(135, 100);
	DriveForwardDistance(30, 100);
}

void RampKickPos3()
{
	/*Robot drive off ramp
	Turns to face center structure
	Drives toward center structure
	Turns to face kcikstand
	Knocks down kickstand*/
	DriveForwardDistance(20, 100);
	TurnLeftDegrees(90, 100);
	DriveForwardDistance(20, 100);
	TurnRightDegrees(90, 100);
	DriveForwardDistance(10, 100);
}
#endif
