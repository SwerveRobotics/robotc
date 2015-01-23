#ifndef CENTER_OBJECTIVES_C
#define CENTER_OBJECTIVES_C

/* Code Review by Darrell
 - Should set CENTER_GOAL_POSITION via a function instead of directly.
 -
*/

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

/* Code Review by Darrell
 - *Awesomely simple code.*
*/

void KnockKickstandPos1()
{
	TurnLeftDegrees(56, 50);
	DriveForwardDistanceGyro(40, 50);
	DriveBackwardDistanceGyro(50, 60);
}

void KnockKickstandPos2()
{
	DriveForwardDistanceGyro(27, 50);
	TurnLeftDegrees(88, 50);
	DriveForwardDistanceGyro(40, 50);
	//Get out of way of alliance partner
	DriveBackwardDistanceGyro(40, 100);
	TurnRightDegrees(87, 50);
	DriveBackwardDistanceGyro(40, 100);
}

void KnockKickstandPos3()
{
	TurnLeftDegrees(35, 50);
	DriveForwardDistanceGyro(45, 50);
	TurnLeftDegrees(85, 50);
	DriveForwardDistanceGyro(20, 50);
	//Get out of way of alliance partner
	DriveBackwardDistanceGyro(30, 100);
	TurnRightDegrees(130, 50);
	DriveBackwardDistanceGyro(68, 100);
}
#endif
