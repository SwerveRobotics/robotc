#ifndef INIT_TELEOP_C
#define INIT_TELEOP_C

/* Code Review by Darrell
 - could use const defines for servo positions with descriptive names
 - *Nice idea mapping a backward button - maybe we can discuss mapping entire controllers?*
*/

void InitializeTeleop()
{
	ASSUME_CONTROLLER_INPUT = true;
	RegisterDriveMotors(mtrFL, mtrBL, mtrFR, mtrBR);
	RegisterBackwardButton(7);
	nMotorEncoder[mtrLifterL] = 0;
	servo[irRotator] = 256;
	servo[goalGrabber] = 160;
}
#endif
