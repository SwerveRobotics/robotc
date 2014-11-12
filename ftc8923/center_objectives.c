#ifndef CENTER_OBJECTIVES_C
#define CENTER_OBJECTIVES_C

void RampKickPos1()
{
	/*Robot drive off ramp
	Turns to face center structure
	Knocks down kickstand*/
	DriveForwardDistance(60, 20);
	TurnRightTime(500, 50);
	DriveBackwardDistance(40, 20);
	TurnRightTime(250, 50);
	DriveBackwardDistance(40, 100);
}

void RampKickPos2()
{
	/*Robot drive off ramp
	Turns to face center structure
	Knocks down kickstand*/
	servo[irRotator] = 64;
	wait1Msec(500);
	//DriveForwardDistance(50, 20);
	//TurnLeft(100);
	//wait1Msec(500);
	//DriveForwardDistance(30, 20);
}

void RampKickPos3()
{
	/*Robot drive off ramp
	Turns to face center structure
	Drives toward center structure
	Turns to face kcikstand
	Knocks down kickstand*/
	servo[irRotator] = 0;
	DriveForwardDistance(60, 20);
	TurnLeftTime(500, 50);
	DriveForwardDistance(40, 20);
	TurnRightTime(600, 50);
	DriveBackwardDistance(30, 100);
}
#endif
