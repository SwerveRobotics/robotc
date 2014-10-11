#ifndef AUTO_DRIVE_FUNCTIONS_C
#define AUTO_DRIVE_FUNCTIONS_C

#include "../drive_modes/tank_4m.c"

//Takes an input of inches and converts to encoder ticks, assuming 4 inch wheels
float EncoderDistance(int inches)
{
	float circumference = PI * 4;
	float revolutions= inches / circumference;
	return revolutions * 1440;
}

//Drives forward at given speed until the distance has been reached
void DriveDistance(int distance, int speed)
{
	nMotorEncoder[FRONT_LEFT_MOTOR] = 0;
	while(nMotorEncoder[FRONT_LEFT_MOTOR] < EncoderDistance(distance))
	{
		DriveForward(speed);
	}
	DriveForward(0);
}

#endif
