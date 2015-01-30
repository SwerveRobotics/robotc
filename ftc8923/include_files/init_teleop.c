#ifndef INIT_TELEOP_C
#define INIT_TELEOP_C


void InitializeTeleop()
{
	ASSUME_CONTROLLER_INPUT = true;
	RegisterDriveMotorPair(mtrFL, mtrFR, 0);
	RegisterDriveMotorPair(mtrBL, mtrBR, 1);
	RegisterSlowModeButton(2);
	SetSlowModeDivisor(3);
	RegisterBackwardButton(1);
	GrabGoal();
}
#endif
