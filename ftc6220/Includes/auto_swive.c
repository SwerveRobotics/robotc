#ifndef AUTO_SWIVE_C
#define AUTO_SWIVE_C

#include "../Library/drive_modes/swerve_4m.c"

const float WHEEL_CIRCUM = WHEEL_RADIUS * 2.0 *PI;
const int ENCODER_RESOLUTION = 1024;
const float ENCODER_TO_CM = (ENCODER_RESOLUTION / MAX_MOTOR_GEAR_RATIO) / (WHEEL_DIAMETER * PI);

// MOVE SWERVE CONSTANTS HERE //


void SimpleDriveDirection(int direction, int power, int distance)
{
	//set motor encoders to zero
	int distanceDriven = 0;
	SetServos(direction);
	while(distanceDriven < distance)
	{
		SetMotors(power);
		distanceDriven = ENCODER_TO_CM * //encoder value
	}
	SetMotors(0);
}

#endif
