#ifndef INIT_TELEOP_C
#define INIT_TELEOP_C


void InitializeTeleop()
{
	ASSUME_CONTROLLER_INPUT = true;
	nMotorEncoder[mtrFR] = 0;
	nMotorEncoder[mtrLifterL] = 0;
	nMotorEncoder[mtrLifterR] = 0;
	RegisterDriveMotorPair(mtrFL, mtrFR, 0);
	RegisterDriveMotorPair(mtrBL, mtrBR, 1);
	RegisterSlowModeButton(2);
	SetSlowModeDivisor(3);
	RegisterBackwardButton(1);
	GrabGoal();
	HoldBalls();
}
#endif
