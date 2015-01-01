#ifndef DRIVE_FUNCTIONS
#define DRIVE_FUNCTOINS

void DriveUntilObjectHit(int power)
{
	StartTask(MonitorSpeed);
	DriveForwardDistanceGyro(500, DEFAULT_POWER);
}

void DrivePerimeterRight()
{
	while(true)
	{
		FollowRightWall(3, 500, DEFAULT_POWER, 2);
		DriveBackwardDistance(5, DEFAULT_POWER);
		TurnLeftDegrees(30, DEFAULT_POWER);
	}
}

#endif
