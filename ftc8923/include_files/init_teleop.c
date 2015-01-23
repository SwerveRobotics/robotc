#ifndef INIT_TELEOP_C
#define INIT_TELEOP_C


void InitializeTeleop()
{
	ASSUME_CONTROLLER_INPUT = true;
	RegisterDriveMotors(mtrFL, mtrBL, mtrFR, mtrBR);
	RegisterBackwardButton(7);
	SetGoalGrabberPos(GRAB_GOAL_SERVO_POS);
}
#endif
