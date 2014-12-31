#ifndef AUTO_INIT
#define AUTO_INIT

#include "../library/motors/motor_defines.h"
#include "../library/drive/auto_drive.c"

void AutoInitialize()
{
	ASSUME_CONTROLLER_INPUT = false;
	RegisterDriveMotors(RightMid, RightSides, LeftMid, LeftSides);
//	RegisterEncoderMotor(RightMid);
	WHEEL_DIAMETER = 4;
	GEAR_RATIO = 1.5;
	servo[goalGrabber] = 150;
}

#endif
