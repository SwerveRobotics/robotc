#ifndef CENTER_GOAL_C
#define CENTER_GOAL_C

int CENTER_STRUCTURE_POSITION = 0;

void DectectGoalIR()
{
	wait1Msec(500);
	if(ReadIRSensor(1) == 3)
	{
		CENTER_STRUCTURE_POSITION = 1;
	}
	else if(ReadIRSensor(1) == 4)
	{
		CENTER_STRUCTURE_POSITION = 2;
	}
	else if(ReadIRSensor(1) == 5)
	{
		CENTER_STRUCTURE_POSITION = 3;
	}
}

void CenterGoalPos1()
{
	TurnRightDegrees(40, 50);
	DriveBackwardDistanceGyro(30, 50);
}

void CenterGoalPos2()
{

}

void CenterGoalPos3()
{

}


#endif
