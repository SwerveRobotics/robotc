#ifndef READ_WRITE_C
#define	READ_WRITE_C

/// - SERVE DRIVE AND CONVERSION PARAMETERS - ///

int reverseMotorFactor[4] = {1, 1, 1, 1};
bool rotateMode = false;

const float	MOTOR_GEAR_RATIO      = 1.206;
const float	SERVO_GEAR_RATIO      = 0.5; // maybe raise to -1?

const float CENTER_RADIUS         = 22.86; //centimeters
const float WHEEL_RADIUS          = 11.16; //centimeters

const float MOTOR_POWER_PER_CMPS  = 1.207671; //theoretical motor power nessesary to move at 1 m/s with 4in wheels
const float MAX_MOTOR_SPEED_CMPS  = 81.93;//theoretical max based on 154rpm motor and 4in diameter wheel

const float SERVO_TICK_PER_DEGREE = 1.4118;//number of servo ticks nessesary to rotate 1 degree (standard servo)

const float ENCODER_RESOLUTION = 1440;
const int STANDARD_SERVO_TICKS = 255;

const float RADIAN_TO_DEGREE = 57.5;

const float ENCODER_TO_DEG = 360 / ENCODER_RESOLUTION;
const float DEG_TO_ENCODER = ENCODER_RESOLUTION / 360;
const float DEG_TO_WINCH_TICK = 4.235;


/// -           END OF PARAMETERS           - ///


//CornerEnum datatype used to refer to each of the four drive modules
typedef enumWord
{
	FRONT_LEFT,
	FRONT_RIGHT,
	BACK_LEFT,
	BACK_RIGHT,
}
CornerEnum;

//structure used to reference servos, sensors, and motors that are accocated with a given drive assembly
typedef struct
{
	TServoIndex servo;
	tSensors zeroTrigger;
	tMotor driveMotor;
	tMotor encoder;
}
DriveAssemblyHardware;

DriveAssemblyHardware Assembly[4];

//structure used to reference servos, sensors, and motors that are accocated with a given manipulator//unused as of yet
typedef struct
{
	TServoIndex servo;
	tSensors sensor;
	tMotor motor;
}
ManipulatorStruct;

ManipulatorStruct Manipulator[4];

// these variables will be used to write to the motors and servos
tMotor SWEEPER_MOTOR;
tMotor FAN_MOTOR_1;
tMotor FAN_MOTOR_2;

TServoIndex GRABBER_SERVO;
TServoIndex SWEEPER_SERVO_ARM;
TServoIndex TUBE_SERVO_SLIDE;
TServoIndex TUBE_SERVO_LIFT;
TServoIndex TUBE_SERVO_WINCH;
TServoIndex SWEEPER_SERVO_1;
TServoIndex SWEEPER_SERVO_2;
TServoIndex LOADER_SERVO;

//send a servo a value
void SetServo(TServoIndex servoName, int value)
{
	servo[servoName] = value;
}

//send a standard servo to a degree position rather than ticks
void SetStandardServoDegree(TServoIndex servoName, float angle)
{
	SetServo(servoName, angle / 360 * STANDARD_SERVO_TICKS);
}

//Set motor power
void SetMotorPower(tMotor motorName, float power)
{
	motor[motorName] = floor(power);
}

//Set Motor Power from a CM/S value
void CMPSToMotor(tMotor motorName, float cmps)
{
	SetMotorPower(Assembly[motorName].driveMotor, MOTOR_POWER_PER_CMPS * MOTOR_GEAR_RATIO * cmps);
}

//return the position of a drive assembly CR servo in degrees
float GetCRServoPosition(CornerEnum servoEnc)
{
	return (float)nMotorEncoder[Assembly[servoEnc].encoder] * ENCODER_TO_DEG * SERVO_GEAR_RATIO;
}

//set the position of a drive assembly CR servo in degrees
void SetCRServoEncoder(CornerEnum servoEnc, int deg)
{
	nMotorEncoder[Assembly[servoEnc].encoder] = deg	 * DEG_TO_ENCODER * SERVO_GEAR_RATIO;
}



//-------------------------------------------------------------------------------------------------//
// !!! IMPORTANT - The following two functions MUST be called, else nothing will not work.     !!! //
//-------------------------------------------------------------------------------------------------//

//register the motors clockwise
void RegisterMotors(
tMotor frontLeftM,    tMotor frontRightM,
tMotor backLeftM,     tMotor backRightM,//drive motors
tMotor motorS,        tMotor motorF1,
tMotor motorF2                                 //manipulator motors
)
{
	Assembly[FRONT_LEFT].driveMotor  = frontLeftM;
	Assembly[BACK_LEFT].driveMotor   = backLeftM;
	Assembly[FRONT_RIGHT].driveMotor = frontRightM;
	Assembly[BACK_RIGHT].driveMotor  = backRightM;
	Assembly[FRONT_LEFT].encoder   = frontLeftM;
	Assembly[BACK_LEFT].encoder    = backLeftM;
	Assembly[FRONT_RIGHT].encoder  = frontRightM;
	Assembly[BACK_RIGHT].encoder   = backRightM;
	SWEEPER_MOTOR     = motorS;
	FAN_MOTOR_1       = motorF1;
	FAN_MOTOR_2       = motorF2;
}

//register the servos clockwise and "zero" the encoders, assuming that the motors are facing forward
void RegisterServos(
TServoIndex frontLeftS,  TServoIndex backLeftS,
TServoIndex backRightS,  TServoIndex frontRightS,//drive servos
TServoIndex grabberS,    TServoIndex sweeperSarm,
TServoIndex sweeperS1,   TServoIndex sweeperS2,
TServoIndex tubeSlift,   TServoIndex tubeSslide,
TServoIndex tubeSwinch,  TServoIndex loaderS//manipulator servos
){
	Assembly[FRONT_LEFT].servo  = frontLeftS;
	Assembly[BACK_LEFT].servo   = backLeftS;
	Assembly[FRONT_RIGHT].servo = frontRightS;
	Assembly[BACK_RIGHT].servo  = backRightS;
	GRABBER_SERVO     = grabberS;
	SWEEPER_SERVO_ARM     = sweeperSarm;
	TUBE_SERVO_WINCH  = tubeSwinch;
	TUBE_SERVO_LIFT   = tubeSlift;
	TUBE_SERVO_SLIDE  = tubeSslide;
	LOADER_SERVO      = loaderS;
	SWEEPER_SERVO_1   = sweeperS1;
	SWEEPER_SERVO_2   = sweeperS2;

	SetServo(Assembly[FRONT_LEFT].servo, 127);
	SetServo(Assembly[FRONT_RIGHT].servo, 127);
	SetServo(Assembly[BACK_LEFT].servo, 127);
	SetServo(Assembly[BACK_RIGHT].servo, 127);
	servo[GRABBER_SERVO] = 11;
	SetCRServoEncoder(FRONT_LEFT,  0);
	SetCRServoEncoder(FRONT_RIGHT, 0);
	SetCRServoEncoder(BACK_RIGHT,  0);
	SetCRServoEncoder(BACK_LEFT,   0);
}

//--------------------------------------//
//   !!! End of required funtions !!!   //
//--------------------------------------//

#endif
