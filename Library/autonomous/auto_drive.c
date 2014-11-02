#ifndef AUTO_DRIVE_FUNCTIONS_C
#define AUTO_DRIVE_FUNCTIONS_C

int WHEEL_DIAMETER = 4;
float GEAR_RATIO = 1.0;

tMotor ENCODER_MOTOR;

void RegisterEncoderMotor(tMotor motorName)
{
	ENCODER_MOTOR = motorName;
}

//Takes an input of encoder ticks and converts to inches
float EncoderDistance(float ticks)
{
	float circumference = PI * WHEEL_DIAMETER;
	float revolutions = (ticks / 1440.0) * GEAR_RATIO;
	return revolutions * circumference;
}

//Drives forward at given power until the distance has been reached
void DriveForwardDistance(int inches, int power)
{
	nMotorEncoder[ENCODER_MOTOR] = 0;
	while(EncoderDistance(nMotorEncoder[ENCODER_MOTOR]) < inches)
	{
		DriveForward(power);
	}
	DriveForward(0);
}

void DriveBackwardDistance(int inches, int power)
{
	nMotorEncoder[ENCODER_MOTOR] = 0;
	while(EncoderDistance(nMotorEncoder[ENCODER_MOTOR]) > -inches)
	{
		DriveBackward(power);
	}
	DriveBackward(0);
}

//Turns left until the gyro reads a vaule equal to or greater than the degrees
void TurnLeftDegrees(int degrees, int power)
{
	SensorValue[gyro] = 0;
	while(abs(SensorValue[gyro]) < degrees)
	{
		TurnRight(power);
	}
	DriveForward(0);
}

void TurnLeftTime(int time, int power)
{
	TurnLeft(power);
	wait1Msec(time);
}

//Turns right until the gyro reads a vaule equal to or greater than the degrees
void TurnRightDegrees(int degrees, int power)
{
	TurnLeftDegrees(degrees, -1 * power);
}

void TurnRightTime(int time, int power)
{
	TurnRight(power);
	wait1Msec(time);
}
#endif
