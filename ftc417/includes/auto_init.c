#ifndef AUTO_INIT
#define AUTO_INIT

#include "../library/motors/motor_defines.h"
#include "../library/drive/auto_drive.c"
#include "includes/servo_417.c"
#include "../../Library/drive/gyro_drive.c"

void AutoInitialize()
{
	ASSUME_CONTROLLER_INPUT = false;
	RegisterDriveMotors(RightMid, RightSides, LeftMid, LeftSides);
//	RegisterEncoderMotor(RightMid);

//	RegisterGyroSensor(gyroSensor); // @todo uncomment and put gyro sensor name for gyro code use
	LEFT_TURN_GYRO_OVERRUN = 15;
	RIGHT_TURN_GYRO_OVERRUN = 20;

	WHEEL_DIAMETER = 4; // inches
	GEAR_RATIO = 1.5;
	ReleaseGoal();
}

#endif
