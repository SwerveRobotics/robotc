#ifndef CENTER_OBJECTIVES_C
#define CENTER_OBJECTIVES_C

int CENTER_GOAL_POSITION = 0;

void DectectFloorIR()
{
	wait1Msec(500);
	if(ReadIRSensor(1) == 4)
	{
		CENTER_GOAL_POSITION = 2;
	}
	else if(ReadIRSensor(1) == 3)
	{
		CENTER_GOAL_POSITION = 1;
	}
	else
	{
		CENTER_GOAL_POSITION = 3;
	}
}

void RampKickPos1()
{
	TurnLeftDegrees(50, 50);
	DriveForwardDistanceGyro(60, 50);
}

void RampKickPos2()
{
	DriveForwardDistanceGyro(10, 50);
	TurnLeftDegrees(75, 50);
	DriveForwardDistanceGyro(35, 50);
}

void RampKickPos3()
{

}
#endif
