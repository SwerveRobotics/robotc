#ifndef CENTER_OBJECTIVES_C
#define CENTER_OBJECTIVES_C

int CENTER_GOAL_POSITION = 0;

void DectectFloorIR()
{
	wait1Msec(500);
	if(ReadIRSensor(1) == 3)
	{
		CENTER_GOAL_POSITION = 1;
	}
	else if(ReadIRSensor(1) == 4)
	{
		CENTER_GOAL_POSITION = 2;
	}
	else if(ReadIRSensor(1) == 5)
	{
		CENTER_GOAL_POSITION = 3;
	}
}

void KnockKickstandPos1()
{
	TurnLeftDegrees(42, 50);
	DriveForwardDistanceGyro(48, 50);
	//Get out of way of alliance partner and block opponent
	TurnRightDegrees(32, 50);
	DriveBackwardDistanceGyro(55, 60);
}

void KnockKickstandPos2()
{
	DriveForwardDistanceGyro(27, 50);
	TurnLeftDegrees(88, 50);
	DriveForwardDistanceGyro(40, 50);
	//Get out of way of alliance partner and block opponent
	DriveBackwardDistanceGyro(40, 100);
	TurnRightDegrees(107, 50);
	DriveBackwardDistanceGyro(55, 100);
}

void KnockKickstandPos3()
{
	TurnLeftDegrees(35, 50);
	DriveForwardDistanceGyro(45, 50);
	TurnLeftDegrees(82, 50);
	DriveForwardDistanceGyro(25, 50);
	//Get out of way of alliance partner and block opponent
	DriveBackwardDistanceGyro(35, 100);
	TurnRightDegrees(125, 50);
	DriveBackwardDistanceGyro(68, 100);
}

void CenterGoalScorePos1()
{

}

void CenterGoalScorePos2()
{

}

void CenterGoalScorePos3()
{
	DriveForwardDistanceGyro(32, 30);
	TurnRightDegrees(64, 50);
	DriveBackwardDistanceGyro(24, 30);
}

#endif
