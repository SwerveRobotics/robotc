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

tMotor FRONT_LEFT_SERVO_ENC;
tMotor BACK_LEFT_SERVO_ENC;
tMotor FRONT_RIGHT_SERVO_ENC;
tMotor BACK_RIGHT_SERVO_ENC;


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
void RegisterServos(TServoIndex frontLeftS, TServoIndex backLeftS, TServoIndex backRightS, TServoIndex frontRightS)
{
	FRONT_LEFT_SERVO  = frontLeftS;
	BACK_LEFT_SERVO   = backLeftS;
	FRONT_RIGHT_SERVO = frontRightS;
	BACK_RIGHT_SERVO  = backRightS;
}

//register psuedo motors for servo encoders
void RegisterServoEncoders(tMotor flEncoder, tMotor blEncoder, tMotor brEncoder, tMotor frEncoder)
{
	FRONT_LEFT_SERVO_ENC  = flEncoder;
	BACK_LEFT_SERVO_ENC   = flEncoder;
	BACK_RIGHT_SERVO_ENC  = flEncoder;
	FRONT_RIGHT_SERVO_ENC = flEncoder;
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

void DegToCRServo(TServoIndex servoName, tMotor servoEnc, int angle)
{
	while (GetCRServoPosition(servoEnc) >= 360)
	{
		SetCRServoEncoder(servoEnc, GetCRServoPosition(servoEnc) - 360)
	}
	while (GetCRServoPosition(servoEnc) < 0)
	{
		SetCRServoEncoder(servoEnc, GetCRServoPosition(servoEnc) + 360)
	}
	int dAngle = angle - GetCRServoPosition;
	while (abs(dAngle) = 2)
	{
		pulseCRServo(servoEnc, sgn(dAngle) + 1.5);
		dAngle = angle - GetCRServoPosition;
	}
}

int GetCRServoPosition(tMotor servoEnc)
{
	return nMotorEncoder[servoEnc] * ENCODER_TO_DEG;
}

void SetCRServoEncoder(tMotor servoEnc, int deg)
{
	nMotorEncoder[servoEnc] = deg	 * DEG_TO_ENCODER;
}

#endif
