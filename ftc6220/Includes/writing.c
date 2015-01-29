#ifndef WRITING_C
#define	WRITING_C // <- Darrell fixed a typo here which was breaking includes of this file

/// - SERVE DRIVE AND CONVERSION PARAMETERS - ///

//float reverseMotorFactor[4] = {1, 1, 1, 1};
//bool rotateMode = false;

const float	MOTOR_GEAR_RATIO      = 1.206;
const float	SERVO_GEAR_RATIO      = 0.5; // maybe raise to -1?

const float MOTOR_POWER_PER_CMPS  = 1.207671; //theoretical motor power nessesary to move at 1 m/s with 4in wheels
const float ENCODER_RESOLUTION = 1440; /* Darrell says: maybe move these to "parameters.h" as well? */

const float ENCODER_TO_DEG = 360 / ENCODER_RESOLUTION;
const float DEG_TO_ENCODER = ENCODER_RESOLUTION / 360;\


/// -           END OF PARAMETERS           - ///

/* code review by Darrell
	- recommend placing tMotor defines in the file you use them in.
	  having them here is really odd since they are not even used.
*/

// these variables will be used to write to the motors and servos
tMotor FRONT_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;
tMotor FAN_MOTOR_1;
tMotor FAN_MOTOR_2;

TServoIndex FRONT_LEFT_SERVO;
TServoIndex BACK_LEFT_SERVO;
TServoIndex FRONT_RIGHT_SERVO;
TServoIndex BACK_RIGHT_SERVO;

//Set Motor Power from a CM/S value
void CMPSToMotor(tMotor motorName, float cmps)
{
	motor[motorName] = 	MOTOR_POWER_PER_CMPS * MOTOR_GEAR_RATIO * cmps;
}

float GetCRServoPosition(tMotor servoEnc)
{
	return (float)nMotorEncoder[servoEnc] * ENCODER_TO_DEG * SERVO_GEAR_RATIO;
}

void SetCRServoEncoder(tMotor servoEnc, int deg)
{
	nMotorEncoder[servoEnc] = deg	 * DEG_TO_ENCODER * SERVO_GEAR_RATIO;
}

#endif
