#ifndef AUTO_SWIVE_C
#define AUTO_SWIVE_C

#include "../../Library/drive_modes/simple_swerve_4m.c"
#include "writing.c"

typedef enumWord
{
	FORWARD   =  90,
	FORTH     =  90,
	AGRIEVE   =  90,
	RIGHT     =   0,
	STARBOARD =   0,
	BACKWARD  = 270,
	BACK      = 270,
	ABSCOND   = 270,
	LEFT      = 180,
	PORT      = 180
}
DirectionEnum;


const float INCH_TO_CM = 2.54;

// zero encoders by type
void ZeroMotorEncoders()
{
	nMotorEncoder(FRONT_LEFT_MOTOR) = 0;
	nMotorEncoder(BACK_LEFT_MOTOR) = 0;
	nMotorEncoder(BACK_RIGHT_MOTOR) = 0;
	nMotorEncoder(FRONT_RIGHT_MOTOR) = 0;
}

//makes it easy to drive straight in one direction
void SimpleDriveDirection(int direction, int power, int distance)
{
	ZeroMotorEncoders();  								//set servo encoders to zero
	int distanceDriven = 0;								//set distance driven to 0
	SimpleWriteToServos(direction);
	SimpleWriteToMotors(power);
	while(distanceDriven < distance)			//while distance driven is less than target distance, set motors to the set power and update distance driven
	{
		int avgEncVal =
		(
		nMotorEncoder(FRONT_LEFT_MOTOR) +
		nMotorEncoder(FRONT_LEFT_MOTOR) +
		nMotorEncoder(FRONT_LEFT_MOTOR) +
		nMotorEncoder(FRONT_LEFT_MOTOR)
		) / 4;
		distanceDriven = 1 * avgEncVal;
	}
	SimpleWriteToMotors(0);													//stop motors
}
void TimedDriveDirection(int direction, int power, float time)
{
	SimpleWriteToServos(direction);
	SimpleWriteToMotors(power);
	wait1Msec(time * 1000);
	SimpleWriteToMotors(0);
}

void RotateTo(int degrees)
{
		SetServosRotateMode();
		SimpleWriteToMotors(60);
		//gyro things
		SimpleWriteToMotors(0);
}
#endif
