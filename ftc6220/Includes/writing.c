#ifndef WRITING_C
#define	WRITNG_C

/// - SERVE DRIVE AND CONVERSION PARAMETERS - ///

const float	MOTOR_GEAR_RATIO      = 1.206;
const float	SERVO_GEAR_RATIO      = 1.0;

const float CENTER_RADIUS         = 22.86; //centimeters
const float WHEEL_RADIUS          = 11.16; //centimeters

const float MOTOR_POWER_PER_CMPS  = 1.207671; //theoretical motor power nessesary to move at 1 m/s with 4in wheels
const float MAX_MOTOR_SPEED_CMPS  = 81.93;//theoretical max based on 154rpm motor and 4in diameter wheel

const float SERVO_TICK_PER_DEGREE = 1.4118;//number of servo ticks nessesary to rotate 1 degree (standard servo)

const int ENCODER_RESOLUTION = 1440;

const float ENCODER_TO_CM = (ENCODER_RESOLUTION / MAX_MOTOR_SPEED_CMPS) / (WHEEL_RADIUS * 2 * PI);

const float ENCODER_TO_DEG = 360 / ENCODER_RESOLUTION;
const float DEG_TO_ENCODER = ENCODER_RESOLUTION / 360;
const float DEG_TO_WINCH_TICK = 1.0;

int currentWinchAngle[4] = { 180 , 180 , 180 , 180 };

/// -           END OF PARAMETERS           - ///

// these variables will be used to write to the motors and servos
tMotor FRONT_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;

TServoIndex FRONT_LEFT_SERVO;
TServoIndex BACK_LEFT_SERVO;
TServoIndex FRONT_RIGHT_SERVO;
TServoIndex BACK_RIGHT_SERVO;
TServoIndex GRABBER_SERVO;

//-------------------------------------------------------------------------------------------------//
// !!! IMPORTANT - The following three functions MUST be called, else the drive will not work. !!! //
//-------------------------------------------------------------------------------------------------//

//register the motors clockwise
void RegisterMotors(tMotor frontLeftM, tMotor backLeftM, tMotor backRightM, tMotor frontRightM)
{
	FRONT_LEFT_MOTOR  = frontLeftM;
	BACK_LEFT_MOTOR   = backLeftM;
	FRONT_RIGHT_MOTOR = frontRightM;
	BACK_RIGHT_MOTOR  = backRightM;
}

//register the servos clockwise
void RegisterServos(TServoIndex frontLeftS, TServoIndex backLeftS, TServoIndex backRightS, TServoIndex frontRightS, TServoIndex grabberS)
{
	FRONT_LEFT_SERVO  = frontLeftS;
	BACK_LEFT_SERVO   = backLeftS;
	FRONT_RIGHT_SERVO = frontRightS;
	BACK_RIGHT_SERVO  = backRightS;
	GRABBER_SERVO = grabberS;

}


//--------------------------------------//
//   !!! End of required funtions !!!   //
//--------------------------------------//

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

int GetCRServoPosition(tMotor servoEnc)
{
	return nMotorEncoder[servoEnc] * ENCODER_TO_DEG;
}

void SetCRServoEncoder(tMotor servoEnc, int deg)
{
	nMotorEncoder[servoEnc] = deg	 * DEG_TO_ENCODER;
}

//flawed
void DegToCRServo(TServoIndex servoName, tMotor servoEnc, int angle)
{
	while (GetCRServoPosition(servoEnc) > 359)
	{
		SetCRServoEncoder(servoEnc, GetCRServoPosition(servoEnc) - 360);
	}
	while (GetCRServoPosition(servoEnc) < 0)
	{
		SetCRServoEncoder(servoEnc, GetCRServoPosition(servoEnc) + 360);
	}
	int dAngle = angle - GetCRServoPosition(servoEnc);
	while (abs(dAngle) <= 2)
	{
		PulseCRServo(servoName, sgn(dAngle) + 1.5);
		dAngle = angle - GetCRServoPosition(servoEnc);
	}
}

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
	else if (dAngle < -360)
	{
		angle = angle - 360;
	}
	else if (dAngle > 360)
	{
		angle = angle + 360;
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

void EnableGoalGrabber(bool state)
{
	if (state == true)
	{
		servo[GRABBER_SERVO] = 90;
	}
	else
	{
		servo[GRABBER_SERVO] = 0;
	}
}



#endif
