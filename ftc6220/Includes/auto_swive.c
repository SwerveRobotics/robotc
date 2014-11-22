#ifndef AUTO_SWIVE_C
#define AUTO_SWIVE_C

#include "../../Library/drive_modes/swerve_4m.c"


int MAX_MOTOR_GEAR_RATIO = 1;   //just added that for testing purposes
int WHEEL_DIAMETER = 1; //ditto
int WHEEL_RADIUS = 1; //ditto
const float WHEEL_CIRCUM = WHEEL_RADIUS * 2.0 *PI;			//calculates wheel circumfrence so that CM can be inputed instead of encoder ticks
const int ENCODER_RESOLUTION = 1440;									//shows number of encoder ticks per rotation.
const float ENCODER_TO_CM = (ENCODER_RESOLUTION / MAX_MOTOR_GEAR_RATIO) / (WHEEL_DIAMETER * PI);   		//changes encoder ticks to centimeters so centimeters can be inputed instead. not using this yet. I hope to eventually.

//"motors" are not actually motors. Encoders can only be definded if a motor is added for them.
tMotor FRONT_LEFT_SERVO_ENCODER;
tMotor BACK_LEFT_SERVO_ENCODER;
tMotor BACK_RIGHT_SERVO_ENCODER ;
tMotor FRONT_RIGHT_SERVO_ENCODER;

// MOVE SWERVE CONSTANTS HERE //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////Defining Functions Section//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////
//Changes Degrees to Ticks
int degreesToTicks(int degrees)
{
	int Ticks = degrees * 4;
	return(Ticks);
}
//Changes Degrees to Ticks
//////////////////////////////////////

//////////////////////////////////////
//This function registers servo encoders as motors because RobotC is stupid and won't let encoders be defined without a motor
//void registerServoEncoders(tMotor flServoEncoder, tMotor blServoEncoder, tMotor brServoEncoder, tMotor frServoEncoder)		//have to register encoders as motor encoders instead of servos.
//{
//	= flServoEncoder;
// = blServoEncoder;
//	= brServoEncoder;
// = frServoEncoder;
//}
//This function registers servo encoders as motors because RobotC is stupid and won't let encoders be defined without a motor
//////////////////////////////////////


void registerServoEncoders(tMotor flServoEncoder, tMotor blServoEncoder, tMotor brServoEncoder, tMotor frServoEncoder)
{
FRONT_LEFT_SERVO_ENCODER = flServoEncoder;
BACK_LEFT_SERVO_ENCODER = blServoEncoder;
BACK_RIGHT_SERVO_ENCODER = brServoEncoder;
FRONT_RIGHT_SERVO_ENCODER = frServoEncoder;
}

//////////////////////////////////////
//allows all servos to be written to while only typing the value once.
void writeToServos(int servoPower)
{
	servo[BACK_LEFT_SERVO] = servoPower;
	servo[BACK_RIGHT_SERVO] = servoPower;
	servo[FRONT_LEFT_SERVO] = servoPower;
	servo[FRONT_RIGHT_SERVO] = servoPower;
}
//allows all servos to be written to while only typing the value once.
//////////////////////////////////////

//////////////////////////////////////
//sets servos to the correct degree setting using the degreesToMsPulse function. I need to add encoders to ensure accuracy.
void setServos(int degrees)
{
		registerServoEncoders(FRONT_LEFT_SERVO_ENCODER, BACK_LEFT_SERVO_ENCODER, BACK_RIGHT_SERVO_ENCODER, FRONT_RIGHT_SERVO_ENCODER);		//has to register servos b/c I don't want to have to call this is my other program

		int Ticks = degreesToTicks(degrees); //uses function to change degrees to ticks
		writeToServos(1);									//starts pulse
		wait1Msec(1);											//waits one MS to use max power. see "http://www.robotc.net/wiki/Tutorials/Arduino_Projects/Mobile_Robotics/BoeBot/Continuous_Rotation_Servo_Intro"
	  writeToServos(0);									//ends pulse
	  	while (abs(nMotorEncoder(FRONT_LEFT_SERVO_ENCODER) - Ticks) < 5)		//waits for servo to get close enough
		{
		}
		writeToServos(1);																									//starts pulse
		wait1Msec(1.5);																										//makes the pulse long enough to stop the servo
		writeToServos(0);																									//stops pulse
}
//sets servos to the correct degree setting using the degreesToMsPulse function. I need to add encoders to ensure accuracy.
//////////////////////////////////////

//////////////////////////////////////
//sets all motor encoders to the same value in one go
void setMotorEncoders(int motorEncoderValue)
{
	nMotorEncoder(FRONT_LEFT_MOTOR) = 0;
	nMotorEncoder(BACK_LEFT_MOTOR) = 0;
	nMotorEncoder(BACK_RIGHT_MOTOR) = 0;
	nMotorEncoder(FRONT_RIGHT_MOTOR) = 0;
}
//sets all motor encoders to the same value in one go
//////////////////////////////////////

//////////////////////////////////////
//sets all servo encoders to the same value in one go
void setServoEncoders(int servoEncoderValue)
{
	registerServoEncoders(FRONT_LEFT_SERVO_ENCODER, BACK_LEFT_SERVO_ENCODER, BACK_RIGHT_SERVO_ENCODER, FRONT_RIGHT_SERVO_ENCODER);
	nMotorEncoder(FRONT_LEFT_SERVO_ENCODER) = 0;
	nMotorEncoder(BACK_LEFT_SERVO_ENCODER) = 0;
	nMotorEncoder(BACK_RIGHT_SERVO_ENCODER) = 0;
	nMotorEncoder(FRONT_RIGHT_SERVO_ENCODER) = 0;
}
//sets all servo encoders to the same value in one go
//////////////////////////////////////

//////////////////////////////////////
//allows all motors to have the same value written to them while only typing the value once
void setMotors(int power)
{
	motor[BACK_LEFT_MOTOR] = power;
	motor[BACK_RIGHT_MOTOR] = power;
	motor[FRONT_LEFT_MOTOR] = power;
	motor[FRONT_RIGHT_MOTOR] = power;
}
//allows all motors to have the same value written to them while only typing the value once
//////////////////////////////////////

//////////////////////////////////////
//makes it easy to drive straight in one direction
void SimpleDriveDirection(int direction, int power, int distance)
{
	setMotorEncoders(0);  								//set servo encoders to zero
	int distanceDriven = 0;								//set distance driven to 0
	setServos(direction);									//turn servos to the correct direction
	while(distanceDriven < distance)			//while distance driven is less than target distance, set motors to the set power and update distance driven
	{
		setMotors(power);
		distanceDriven = ENCODER_TO_CM * nMotorEncoder(FRONT_LEFT_MOTOR);
	}
	setMotors(0);													//stop motors
}
//makes it easy to drive in a direction
//////////////////////////////////////

#endif
