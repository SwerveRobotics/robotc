#ifndef CENTER_OBJECTIVES_C
#define CENTER_OBJECTIVES_C

void DetectRampIR()
{
	int position1 = 244;
	int position3 = 220;

	//Robot detects position of IR beacon and uses corresponding function accordingly
	servo[irRotator] = position3;
	wait1Msec(500);
	if(ReadIRSensor() == 4)
	{
		CENTER_GOAL_POSITION = 3;
	}

	else
	{
		servo[irRotator] = position1;
		wait1Msec(500);
		if(ReadIRSensor() == 4)
		{
			CENTER_GOAL_POSITION = 3;
		}

		else
		{
			CENTER_GOAL_POSITION = 2;
		}
	}
}

void RampKickPos1()
{
	/*Robot drive off ramp
	Turns to face center structure
	Knocks down kickstand*/
	DriveForwardDistance(60, 20);
	TurnLeftDegrees(120, 50);
	//DriveForwardDistance(40, 20);
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
	wait1Msec(500);
	//DriveForwardDistance(40, 20);
	//TurnLeft(100);
	//wait1Msec(500);
	//DriveForwardDistance(30, 20);
	//TurnRight(100);
	//wait1Msec(500);
	//DriveForwardDistance(10, 20);
}
#endif
