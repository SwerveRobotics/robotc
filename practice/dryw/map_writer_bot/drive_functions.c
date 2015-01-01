#ifndef DRIVE_FUNCTIONS
#define DRIVE_FUNCTOINS

void FollowRightWall(int distanceFromWall, int power, int sonarNum)
{
	StartTask(MonitorSpeed);
	while(CURRENT_SPEED != 0)
	{
	 	DriveRightMotors(power + (ReadSonar(sonarNum) - distanceFromWall));
	 	DriveLeftMotors(power - (ReadSonar(sonarNum) - distanceFromWall));
	}
}

void DriveUntilObjectHit(int power)
{
	StartTask(MonitorSpeed);
	DriveForwardDistanceGyro(500, DEFAULT_POWER);
}

void DrivePerimeterRight()
{
	while(true)
	{
		FollowRightWall(3, DEFAULT_POWER, 2);
		DriveBackwardDistance(5, DEFAULT_POWER);
		TurnLeftDegrees(30, DEFAULT_POWER);
	}
}

#endif
