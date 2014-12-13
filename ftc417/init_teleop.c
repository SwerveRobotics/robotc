#ifndef INIT_TELEOP
#define INIT_TELEOP

void InitializeTeleOP()
{
	ASSUME_CONTROLLER_INPUT = true;
	RegisterDriveMotors(LeftMid, LeftSides, RightMid, RightSides);
}
#endif
