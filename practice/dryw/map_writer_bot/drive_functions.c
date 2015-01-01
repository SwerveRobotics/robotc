#ifndef DRIVE_FUNCTIONS
#define DRIVE_FUNCTOINS

void DriveUntilObjectHit(int power)
{
	StartTask(MonitorSpeed);
	DriveForward(power);
	while(CurrentSpeed() != 0)
	{

	}
	StopAllDriveMotors();
}

#endif
