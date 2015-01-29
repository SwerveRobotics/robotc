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

const float MEDIUM_GOAL_HEIGHT = 182;
const float HIGH_GOAL_HEIGHT = 133;
const float CENTER_GOAL_HEIGHT = 54;
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
	TServoIndex driveServo;
	tSensors zeroTrigger;
	tMotor driveMotor;
	tMotor encoder;
}
DriveAssemblyHardware;

DriveAssemblyHardware Assembly[4];

//structures used to reference servos, sensors, and motors that are accocated with a given manipulator
typedef struct
{
	TServoIndex liftServo;
	TServoIndex winchServo;
	TServoIndex slideServo;
	TServoIndex loaderServo;
	tSensors touchSensor;
}
TubeStruct;

TubeStruct Tube;

typedef struct
{
	tMotor motor1;
	TServoIndex servo1;
	TServoIndex servo2;
	TServoIndex armServo;
}
SweeperStruct;

SweeperStruct Sweeper;

// these variables will be used to write to the motors and servos outside of the drive, tube, or sweeper
tMotor FAN_MOTOR_1;
tMotor FAN_MOTOR_2;
TServoIndex GRABBER_SERVO;
tSensors IR_SENSOR;

//send a servo a value
void SetServo(TServoIndex servoName, int value)
{
	servo[servoName] = value;
}

//send a standard servo to a degree position rather than ticks
void SetStandardServoDegree(TServoIndex servoName, float angle)
{
	SetServo(servoName, angle / 360 * STANDARD_SERVO_TICKS * 2);
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
	Sweeper.motor1    = motorS;
	FAN_MOTOR_1       = motorF1;
	FAN_MOTOR_2       = motorF2;
}

//register the servos clockwise and "zero" the encoders, assuming that the motors are facing forward
void RegisterServos(
TServoIndex frontLeftS,  TServoIndex backLeftS,
TServoIndex backRightS,  TServoIndex frontRightS,//drive servos
TServoIndex grabberS,    TServoIndex sweeperSArm,
TServoIndex sweeperS1,   TServoIndex sweeperS2,
TServoIndex tubeSlift,   TServoIndex tubeSslide,
TServoIndex tubeSwinch,  TServoIndex loaderS//manipulator servos
){
	Assembly[FRONT_LEFT].driveServo  = frontLeftS;
	Assembly[BACK_LEFT].driveServo   = backLeftS;
	Assembly[FRONT_RIGHT].driveServo = frontRightS;
	Assembly[BACK_RIGHT].driveServo  = backRightS;
	GRABBER_SERVO     = grabberS;
	Tube.winchServo   = tubeSwinch;
	Tube.liftServo    = tubeSlift;
	Tube.slideServo   = tubeSslide;
	Tube.loaderServo  = loaderS;
	Sweeper.armServo  = sweeperSArm;
	Sweeper.servo1    = sweeperS1;
	Sweeper.servo2    = sweeperS2;

	SetServo(Assembly[FRONT_LEFT].driveServo, 127);
	SetServo(Assembly[FRONT_RIGHT].driveServo, 127);
	SetServo(Assembly[BACK_LEFT].driveServo, 127);
	SetServo(Assembly[BACK_RIGHT].driveServo, 127);
	servo[GRABBER_SERVO] = 11;
	SetServo(Sweeper.armServo, 0);
	SetServo(servoSweep1, 128);
	SetServo(servoSweep2, 128);
	SetStandardServoDegree(Tube.liftServo, 80);
	SetServo(Tube.slideServo, 127);
	SetCRServoEncoder(FRONT_LEFT,  0);
	SetCRServoEncoder(FRONT_RIGHT, 0);
	SetCRServoEncoder(BACK_RIGHT,  0);
	SetCRServoEncoder(BACK_LEFT,   0);
}

//--------------------------------------//
//   !!! End of required funtions !!!   //
//--------------------------------------//

#endif
