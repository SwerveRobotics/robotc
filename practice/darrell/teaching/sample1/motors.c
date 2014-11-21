#ifndef MOTORS_C
#define MOTORS_C

const int FULL_IMPULSE = 100;
const int THREE_QUARTER_IMPULSE = 75;
const int HALF_IMPULSE = 50;

void ResetMotorEncoders()
{
	nMotorEncoder[LeftMotor] = 0;
	nMotorEncoder[RightMotor] = 0;
}

void DriveLeftMotor(int speed)
{
	motor[LeftMotor] = speed;
}

void DriveRightMotor(int speed)
{
	motor[RightMotor] = speed;
}

void StopMotors()
{
	DriveLeftMotor(0);
	DriveRightMotor(0);
}

void DriveForward(int speed)
{
	DriveLeftMotor(speed);
	DriveRightMotor(speed);
}

void DriveBackwards(int speed)
{
	DriveLeftMotor(-1*speed);
	DriveRightMotor(-1*speed);
}

void DriveDistanceForward(int ticks, int speed)
{
	ResetMotorEncoders();
	int encoderVal = nMotorEncoder[LeftMotor];
	while(abs(encoderVal - nMotorEncoder[LeftMotor]) < abs(ticks))
	{
		DriveForward(speed);
	}
	StopMotors();
}

void DriveDistanceBackwards(int ticks, int speed)
{
	ResetMotorEncoders();
	int encoderVal = nMotorEncoder[LeftMotor];
	while(abs(encoderVal - nMotorEncoder[LeftMotor]) < abs(ticks))
	{
		DriveBackwards(speed);
	}
	StopMotors();
}

void TurnLeft(int ticks, int speed)
{
	ResetMotorEncoders();
	int encoderVal = nMotorEncoder[LeftMotor];
	while(abs(encoderVal - nMotorEncoder[LeftMotor]) < abs(ticks))
	{
		DriveLeftMotor(-1*speed);
		DriveRightMotor(speed);
	}
	StopMotors();
}

void TurnRight(int ticks, int speed)
{
	ResetMotorEncoders();
	int encoderVal = nMotorEncoder[LeftMotor];
	while(abs(encoderVal - nMotorEncoder[LeftMotor]) < abs(ticks))
	{
		DriveLeftMotor(speed);
		DriveRightMotor(-1*speed);
	}
	StopMotors();
}

#endif
