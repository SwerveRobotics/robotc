#ifndef WRITING_C
#define	WRITNG_C

/* Code Review by Darrell
 - *Great use of consts and great adherance to style guide for naming them!*
 - *Good use of comments to explain constants.*
 - Motors and Servos should really be in an array of structs indexed by an enum. Each
   struct should have one tMotor and one TServoIndex in it.
 - CMPSToMotor: This should be two functions: CMPSToMotorPower() and SetMotorPower()
 - DegToServo: This should be two functions: SetServoDegree() and DegreesToTicks()
 - Your use of functions to perform two tasks forces you to re-perform those tasks in each function.
 - Complexity of this file could be reduced greatly if you do the two things I recommend:
   1. Stop doing two functions in single functions.
   2. Create an array of structs indexed by enums. This will reduce some of your functiosn from 20 lines to 3.
 - Curly brace placement is inconsistent.
 - Naming of this file is odd. Why is it called "writing"?
*/

/// - SERVE DRIVE AND CONVERSION PARAMETERS - ///

int reverseMotorFactor = 1;

const float	MOTOR_GEAR_RATIO      = 1.206;
const float	SERVO_GEAR_RATIO      = 0.5; // maybe raise to -1?

const float CENTER_RADIUS         = 22.86; //centimeters
const float WHEEL_RADIUS          = 11.16; //centimeters

const float MOTOR_POWER_PER_CMPS  = 1.207671; //theoretical motor power nessesary to move at 1 m/s with 4in wheels
const float MAX_MOTOR_SPEED_CMPS  = 81.93;//theoretical max based on 154rpm motor and 4in diameter wheel

const float SERVO_TICK_PER_DEGREE = 1.4118;//number of servo ticks nessesary to rotate 1 degree (standard servo)

const float ENCODER_RESOLUTION = 1440;

const float ENCODER_TO_DEG = 360 / ENCODER_RESOLUTION;
const float DEG_TO_ENCODER = ENCODER_RESOLUTION / 360;
const float DEG_TO_WINCH_TICK = 4.235;

int currentWinchAngle[4] = { 180 , 180 , 180 , 180 };

/// -           END OF PARAMETERS           - ///

// these variables will be used to write to the motors and servos
tMotor FRONT_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;
tMotor SWEEPER_MOTOR;
tMotor FAN_MOTOR_1;
tMotor FAN_MOTOR_2;

TServoIndex FRONT_LEFT_SERVO;
TServoIndex BACK_LEFT_SERVO;
TServoIndex FRONT_RIGHT_SERVO;
TServoIndex BACK_RIGHT_SERVO;
TServoIndex GRABBER_SERVO;
TServoIndex SWEEPER_SERVO;
TServoIndex TUBE_SERVO;

//Set Motor Power from a CM/S value
void CMPSToMotor(tMotor motorName, float cmps)
{
	motor[motorName] = 	MOTOR_POWER_PER_CMPS * MOTOR_GEAR_RATIO * cmps;
}

void DegToServo(TServoIndex servoName, int angle)
{
	servo[servoName] = SERVO_GEAR_RATIO * SERVO_TICK_PER_DEGREE * angle;
}

void PulseCRServo(TServoIndex servoName, float length)
{
	servo[servoName] = 1;
	wait1Msec(length);
	servo[servoName] = 0;
	wait1Msec(1);
}

float GetCRServoPosition(tMotor servoEnc)
{
	return (float)nMotorEncoder[servoEnc] * ENCODER_TO_DEG * SERVO_GEAR_RATIO;
}

void SetCRServoEncoder(tMotor servoEnc, int deg)
{
	nMotorEncoder[servoEnc] = deg	 * DEG_TO_ENCODER * SERVO_GEAR_RATIO;
}

void DegToCRServo(TServoIndex servoName, tMotor servoEnc, float angle)
{

	while (GetCRServoPosition(servoEnc) > 359)
	{
		SetCRServoEncoder(servoEnc, GetCRServoPosition(servoEnc) - 360);
	}
	while (GetCRServoPosition(servoEnc) < 0)
	{
		SetCRServoEncoder(servoEnc, GetCRServoPosition(servoEnc) + 360);
	}
	float dAngle = angle - GetCRServoPosition(servoEnc);
	/*if (abs(dAngle) > 180)
	{
		angle = angle + (180 * sgn(dAngle));
		if (reverseMotorFactor == 1)
		{
			reverseMotorFactor = -1;
		}
		else
		{
			reverseMotorFactor = 1;
		}
	}
	while (abs(dAngle) >= 2)
	{
		servo[servoName] = 127 - (sgn(dAngle)) * 127 + dAngle / 10;
		dAngle = angle - GetCRServoPosition(servoEnc);
	}*/

	while( abs(dAngle) > 5)
	{
		if (abs(dAngle) <= 5)
		{
			break;
		}
		if (dAngle > 0)
		{
			servo[servoName] = 100;
		}
		else
		{
			servo[servoName] = 154;
		}
		dAngle = angle - GetCRServoPosition(servoEnc);
	}
	servo[servoName] = 127;
}

/* Review by Darrell - If you used an array indexed by an enum, then you wouldn't need the large if-statement. */
void DegToWinchServo(TServoIndex servoName, int angle)//set a winch servo to a position between -360 and 720
{
	servo[servoName] = (angle + 360) * DEG_TO_WINCH_TICK;

	if (servoName == FRONT_LEFT_SERVO)
	{
		currentWinchAngle[0] = angle;
	}
	else if (servoName == BACK_LEFT_SERVO)
	{
		currentWinchAngle[1] = angle;
	}
	else if (servoName == BACK_RIGHT_SERVO)
	{
		currentWinchAngle[2] = angle;
	}
	else if (servoName == FRONT_RIGHT_SERVO)
	{
		currentWinchAngle[3] = angle;
	}
}

/* Review by Darrell - If you used an array indexed by an enum, then you wouldn't need the large if-statement. */
void ClosestDegToWinchServo(TServoIndex servoName, int angle)//set a winch servo to a position between -360 and 720, but perfers the closest value
{
	int w;
	if (servoName == FRONT_LEFT_SERVO)
	{
		w = 0;
	}
	else if (servoName == BACK_LEFT_SERVO)
	{
		w = 1;
	}
	else if (servoName == BACK_RIGHT_SERVO)
	{
		w = 2;
	}
	else if (servoName == FRONT_RIGHT_SERVO)
	{
		w = 3;
	}
	int dAngle = currentWinchAngle[w] - angle;
	if (abs(dAngle) > 180)
	{
		angle = angle + (180 * sgn(dAngle));
		if (reverseMotorFactor == 1)
		{
			reverseMotorFactor = -1;
		}
		else
		{
			reverseMotorFactor = 1;
		}
	}
	if (abs(dAngle) > 360)
	{
		angle = angle + (360 * sgn(dAngle));
	}
	if (angle > 720)
	{
		angle = angle - 360;
	}
	else if (angle < -360)
	{
		angle = angle + 360;
	}
	servo[servoName] = (angle + 360) * DEG_TO_WINCH_TICK;
}

//-------------------------------------------------------------------------------------------------//
// !!! IMPORTANT - The following three functions MUST be called, else the drive will not work. !!! //
//-------------------------------------------------------------------------------------------------//

//register the motors clockwise
void RegisterMotors(
tMotor frontLeftM,    tMotor backLeftM,
tMotor backRightM,    tMotor frontRightM,//drive motors
tMotor motorS,        tMotor motorF1,
tMotor motorF2                                 //manipulator motors
)
{
	FRONT_LEFT_MOTOR  = frontLeftM;
	BACK_LEFT_MOTOR   = backLeftM;
	FRONT_RIGHT_MOTOR = frontRightM;
	BACK_RIGHT_MOTOR  = backRightM;
	SWEEPER_MOTOR     = motorS;
	FAN_MOTOR_1       = motorF1;
	FAN_MOTOR_2       = motorF2;
}

//register the servos clockwise and "zero" the encoders, assuming that the motors are facing forward
void RegisterServos(
TServoIndex frontLeftS,  TServoIndex backLeftS,
TServoIndex backRightS,  TServoIndex frontRightS,//drive servos
TServoIndex grabberS,    TServoIndex sweeperS,
TServoIndex tubeS                                //manipulator servos
){
	FRONT_LEFT_SERVO  = frontLeftS;
	BACK_LEFT_SERVO   = backLeftS;
	FRONT_RIGHT_SERVO = frontRightS;
	BACK_RIGHT_SERVO  = backRightS;
	GRABBER_SERVO     = grabberS;
	SWEEPER_SERVO     = sweeperS;
	TUBE_SERVO        = tubeS;

	SetCRServoEncoder(FRONT_LEFT_MOTOR,  90);
	SetCRServoEncoder(FRONT_RIGHT_MOTOR, 90);
	SetCRServoEncoder(BACK_RIGHT_MOTOR,  90);
	SetCRServoEncoder(BACK_LEFT_MOTOR,   90);
}


//--------------------------------------//
//   !!! End of required funtions !!!   //
//--------------------------------------//



#endif
