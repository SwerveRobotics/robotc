#ifndef INIT_TELEOP_C
#define INIT_TELEOP_C

void InitializeTeleop()
{
	ASSUME_CONTROLLER_INPUT = true;
	RegisterDriveMotors(mtrFL, mtrBL, mtrFR, mtrBR);
	servo[irRotator] = 128;
	servo[goalGrabber] = 160;
}
#endif
