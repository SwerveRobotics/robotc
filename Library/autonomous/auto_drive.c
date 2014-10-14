#ifndef AUTO_DRIVE_FUNCTIONS_C
#define AUTO_DRIVE_FUNCTIONS_C

//Takes an input of inches and converts to encoder ticks, assuming 4 inch wheels
float EncoderDistance(int inches)
{
	float circumference = PI * 4;
	float revolutions = inches / circumference;
	return revolutions * 1440;
}

//Drives forward at given power until the distance has been reached
void DriveDistance(int distance, int power)
{
	nMotorEncoder[FRONT_LEFT_MOTOR] = 0;
	while(nMotorEncoder[FRONT_LEFT_MOTOR] < EncoderDistance(distance))
	{
		DriveForward(power);
	}
	DriveForward(0);
}

void TurnRightDegrees(int degrees, int power)
{
	SensorValue[gyro] = 0;
	while(SensorValue[gyro] < -1 * degrees)
	{
		TurnRight(power);
	}
	DriveForward(0);
}

void TurnLeftDegrees(int degrees, int power)
{
	TurnRightDegrees(-1 * degrees, -1 * power);
}
#endif
