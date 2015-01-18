#ifndef MOTORS_C
#define MOTORS_C

tMotor LEFT_FRONT;
tMotor LEFT_REAR;
tMotor RIGHT_FRONT;
tMotor RIGHT_REAR;

void InitMotors(tMotor leftFront, tMotor leftRear, tMotor rightFront, tMotor rightRear)
{
	LEFT_FRONT = leftFront;
	LEFT_REAR = leftRear;
	RIGHT_FRONT = rightFront;
	RIGHT_REAR = rightRear;
}

void ResetMotorEncoders()
{
	nMotorEncoder[LEFT_FRONT] = 0;
	nMotorEncoder[LEFT_REAR] = 0;
	nMotorEncoder[RIGHT_FRONT] = 0;
	nMotorEncoder[RIGHT_REAR] = 0;
}

void DriveLeftMotors(int speed)
{
	motor[LEFT_FRONT] = speed;
	motor[LEFT_REAR] = speed;
}

void DriveRightMotors(int speed)
{
	motor[RIGHT_FRONT] = speed;
	motor[RIGHT_REAR] = speed;
}

void StopMotors()
{
	DriveLeftMotors(0);
	DriveRightMotors(0);
}

void DriveForward(int speed)
{
	DriveLeftMotors(speed);
	DriveRightMotors(speed);
}

void DriveBackwards(int speed)
{
	DriveLeftMotors(-1*speed);
	DriveRightMotors(-1*speed);
}

void DriveDistanceForward(int ticks, int speed)
{
	ResetMotorEncoders();
	int encoderVal = nMotorEncoder[LEFT_FRONT];
	while(abs(encoderVal - nMotorEncoder[LEFT_FRONT]) < abs(ticks))
	{
		DriveForward(speed);
	}
	StopMotors();
}

void DriveDistanceBackwards(int ticks, int speed)
{
	ResetMotorEncoders();
	int encoderVal = nMotorEncoder[LEFT_FRONT];
	while(abs(encoderVal - nMotorEncoder[LEFT_FRONT]) < abs(ticks))
	{
		DriveBackwards(speed);
	}
	StopMotors();
}

void TurnLeft(int ticks, int speed)
{
	ResetMotorEncoders();
	int encoderVal = nMotorEncoder[LEFT_FRONT];
	while(abs(encoderVal - nMotorEncoder[LEFT_FRONT]) < abs(ticks))
	{
		DriveLeftMotors(-1*speed);
		DriveRightMotors(speed);
	}
	StopMotors();
}

void TurnRight(int ticks, int speed)
{
	ResetMotorEncoders();
	int encoderVal = nMotorEncoder[LEFT_FRONT];
	while(abs(encoderVal - nMotorEncoder[LEFT_FRONT]) < abs(ticks))
	{
		DriveLeftMotors(speed);
		DriveRightMotors(-1*speed);
	}
	StopMotors();
}

#endif
