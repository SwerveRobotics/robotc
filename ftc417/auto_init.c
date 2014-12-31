#ifndef AUTO_INIT
#define AUTO_INIT

void AutoInitialize()
{
	ASSUME_CONTROLLER_INPUT = false;
	RegisterDriveMotors(RightMid, RightSides, LeftMid, LeftSides);
	RegisterEncoderMotor(RightMid);
	WHEEL_DIAMETER = 4;
	GEAR_RATIO = 1.5;
	servo[goalGrabber] = 150:
}
