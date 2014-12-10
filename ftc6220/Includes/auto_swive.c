#ifndef AUTO_SWIVE_C
#define AUTO_SWIVE_C

#include "../../Library/drive_modes/simple_swerve_4m.c"
#include "writing.c"

typedef enumWord
{
	FORWARD   = 180,
	FORTH     = 180,
	AGRIEVE   = 180,
	RIGHT     = 270,
	STARBOARD = 270,
	BACKWARD  =   0,
	BACK      =   0,
	ABSCOND   =   0,
	LEFT      =  90,
	PORT      =  90
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
		distanceDriven = ENCODER_TO_CM * avgEncVal;
	}
	SimpleWriteToMotors(0);													//stop motors
}
void RotateTo(int degrees)
{
		SetServosRotateMode();
		SimpleWriteToMotors(60);
		//gyro things
		SimpleWriteToMotors(0);
}
#endif
