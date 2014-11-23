#ifndef AUTO_SWIVE_C
#define AUTO_SWIVE_C

#include "../../Library/drive_modes/simple_swerve_4m.c"
#include "writing.c"

const int ENCODER_RESOLUTION = 1440;
//changes encoder ticks to centimeters so centimeters can be inputed instead
const float ENCODER_TO_CM = (ENCODER_RESOLUTION / MAX_MOTOR_SPEED_CMPS) / (WHEEL_RADIUS * 2 * PI);

const float ENCODER_TO_DEG = 360 / ENCODER_RESOLUTION;

// zero encoders by type
void ZeroMotorEncoders()
{
	nMotorEncoder(FRONT_LEFT_MOTOR) = 0;
	nMotorEncoder(BACK_LEFT_MOTOR) = 0;
	nMotorEncoder(BACK_RIGHT_MOTOR) = 0;
	nMotorEncoder(FRONT_RIGHT_MOTOR) = 0;
}

void ZeroServoEncoders()
{
	nMotorEncoder(FRONT_LEFT_SERVO_ENC) = 0;
	nMotorEncoder(BACK_LEFT_SERVO_ENC) = 0;
	nMotorEncoder(BACK_RIGHT_SERVO_ENC) = 0;
	nMotorEncoder(FRONT_RIGHT_SERVO_ENC) = 0;
}

//makes it easy to drive straight in one direction
void SimpleDriveDirection(int direction, int power, int distance)
{
	ZeroMotorEncoders();  								//set servo encoders to zero
	int distanceDriven = 0;								//set distance driven to 0
	DegToCRServo(FRONT_LEFT_SERVO, FRONT_LEFT_SERVO_ENC, direction);
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
//makes it easy to drive in a direction
//////////////////////////////////////

#endif
