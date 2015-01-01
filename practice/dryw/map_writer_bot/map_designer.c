#ifndef MAP_DESIGNER
#define MAP_DESIGNER

void MapRoom()
{
	while(true)
	{
		DriveBackwardDistanceGyro(3, DEFAULT_SPEED);
		TurnLeftDegrees(90, DEFAULT_SPEED);
		DriveUntilObjectHit(DEFAULT_SPEED);
	}
}

#endif
