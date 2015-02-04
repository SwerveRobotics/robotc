#ifndef AUTO_INIT
#define AUTO_INIT

/* Code Review by Darrell
 - magic numbers need defined with descriptive naming
 - file lacks comment explaining what is going on
 - file location should not be in main folder since file does not build
 - *Good use of library.*
 - servo should be set using a function
 - other file is "init_teleop" and this one is "auto_init". Please use consistent name scheme.
*/

#include "../library/motors/motor_defines.h"
#include "../library/drive/auto_drive.c"

void AutoInitialize()
{
	ASSUME_CONTROLLER_INPUT = false;
	RegisterDriveMotors(RightMid, RightSides, LeftMid, LeftSides);
//	RegisterEncoderMotor(RightMid);
	WHEEL_DIAMETER = 4; // inches
	GEAR_RATIO = 1.5;
	servo[goalGrabber] = 150;
}

#endif
