#ifndef INIT_TELEOP
#define INIT_TELEOP

/* Code Review by Darrell
 - Servo should be using a defined value instead of a magic number.
 - file lacks comment explaining what is going on
 - file location should not be in main folder since file does not build
*/


void InitializeTeleOP()
{
	ASSUME_CONTROLLER_INPUT = true;
	RegisterDriveMotors(LeftMid, LeftSides, RightMid, RightSides);
	servo[goalGrabber] = 150;
}
#endif
