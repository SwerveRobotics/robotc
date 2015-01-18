#ifndef AUTO_SWIVE_C
#define AUTO_SWIVE_C

#include "../../Library/drive_modes/simple_swerve_4m.c"
#include "writing.c"

const float INCH_TO_CM = 2.54;

//makes it easy to drive straight in one direction
void SimpleDriveDirection(int direction, int power, int distance)
{
	ZeroMotorEncoders();  								//set servo encoders to zero
	int distanceDriven = 0;								//set distance driven to 0
	SimpleWriteToMotors(power);
	while(distanceDriven < distance)			//while distance driven is less than target distance, set motors to the set power and update distance driven
	{
		int avgEncVal =
		(
		nMotorEncoder(FRONT_LEFT_MOTOR) +
		nMotorEncoder(FRONT_RIGHT_MOTOR) +
		nMotorEncoder(BACK_LEFT_MOTOR) +
		nMotorEncoder(BACK_RIGHT_MOTOR)
		) / 4;
		distanceDriven = 1 * avgEncVal;
	}
	SimpleWriteToMotors(0);													//stop motors
}
void TimedDriveDirection(int power, float time)
{
	CMPSToMotor(FRONT_LEFT_MOTOR,  power);
	CMPSToMotor(BACK_LEFT_MOTOR,   power);
	CMPSToMotor(BACK_RIGHT_MOTOR,  -1 * power);
	CMPSToMotor(FRONT_RIGHT_MOTOR, -1 * power);
	wait1Msec(time * 1000);
	SimpleWriteToMotors(0);
}

void RotateTo(int degrees)
{
		SetServosRotateMode();

		//gyro things
		SimpleWriteToMotors(0);
}
#endif
