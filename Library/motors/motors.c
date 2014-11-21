#ifndef MOTORS_C
#define MOTORS_C

#include "motor_defines.h"
#include "../controllers/controller_defines.h"


// Assuming a linear relationship between these values, we can solve for the slope //
const float LINEAR_MOTOR_CONTROL_SLOPE = (MAX_MOTOR_POWER-MIN_MOTOR_POWER)/(MAX_ANALOG-ANALOG_DEAD_ZONE);
// Solve for the Y-intercept (equation was sovled for with a simple system of two equations assuming a linear relationship)
const float LINEAR_MOTOR_CONTROL_INTERCEPT = (MIN_MOTOR_POWER-(LINEAR_MOTOR_CONTROL_SLOPE*ANALOG_DEAD_ZONE));

// Calculates Output from Input based on a Linear Relationship
int AttenuateControllerOutput(int output)
{
	// using linear equation in slope-intercept form of y = mx + b
  return (LINEAR_MOTOR_CONTROL_SLOPE*output + sgn(output)*LINEAR_MOTOR_CONTROL_INTERCEPT);
}

// Set Motor Power
void SetMotorPower(tMotor motorName, int power)
{
	if(ASSUME_CONTROLLER_INPUT==true)
		motor[motorName] = AttenuateControllerOutput(power);
	else
		motor[motorName] = power;
}

#endif



/////////////////////////////////////////////////////////////////
//AUTO SWIVE STARTS HERE
#ifndef AUTO_SWIVE_C
#define AUTO_SWIVE_C

#include "../../Library/drive_modes/swerve_4m.c"


int MAX_MOTOR_GEAR_RATIO = 1;   //just added that for testing purposes
int WHEEL_DIAMETER = 1; //ditto
const float WHEEL_CIRCUM = WHEEL_RADIUS * 2.0 *PI;			//calculates wheel circumfrence so that CM can be inputed instead of encoder ticks
const int ENCODER_RESOLUTION = 1044;									//shows number of encoder ticks per rotation.
const float ENCODER_TO_CM = (ENCODER_RESOLUTION / MAX_MOTOR_GEAR_RATIO) / (WHEEL_DIAMETER * PI);   		//changes encoder ticks to centimeters so centimeters can be inputed instead. not using this yet. I hope to eventually.

//"motors" are not actually motors. Encoders can only be definded if a motor is added for them.
tMotor frontLeftServoEncoder;
tMotor backLeftServoEncoder;
tMotor backRightServoEncoder ;
tMotor frontRightServoEncoder;

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
void registerServoEncoders(tMotor flServoEncoder, tMotor blServoEncoder, tMotor brServoEncoder, tMotor frServoEncoder)		//have to register encoders as motor encoders instead of servos.
{
frontLeftServoEncoder	= flServoEncoder;
backLeftServoEncoder = blServoEncoder;
backRightServoEncoder	= brServoEncoder;
frontRightServoEncoder = frServoEncoder;
}
//This function registers servo encoders as motors because RobotC is stupid and won't let encoders be defined without a motor
//////////////////////////////////////


void writeToServos(int servoPower)				//allows all servos to be written to while only typing the value once.
{
	servo[BACK_LEFT_SERVO] = servoPower;
	servo[BACK_RIGHT_SERVO] = servoPower;
	servo[FRONT_LEFT_SERVO] = servoPower;
	servo[FRONT_RIGHT_SERVO] = servoPower;
}


void setServos(int degrees)			//sets servos to the correct degree setting using the degreesToMsPulse function. I need to add encoders to ensure accuracy.
{
		registerServoEncoders(frontLeftServoEncoder, backLeftServoEncoder, backRightServoEncoder, frontRightServoEncoder);		//has to register servos b/c I don't want to have to call this is my other program


		int Ticks = degreesToTicks(degrees);
		writeToServos(1);									//starts pulse
		wait1Msec(1);											//waits one MS to use max power. see "http://www.robotc.net/wiki/Tutorials/Arduino_Projects/Mobile_Robotics/BoeBot/Continuous_Rotation_Servo_Intro"
	  writeToServos(0);									//ends pulse
	  	while (abs(nMotorEncoder(frontLeftServoEncoder) - Ticks) < 5)
		{
		}
		writeToServos(1);
		wait1Msec(1.5);
		writeToServos(0);
}




void setMotors(int power)						//allows all motors to have the same value written to them while only typing the value once
{
	motor[BACK_LEFT_MOTOR] = power;
	motor[BACK_RIGHT_MOTOR] = power;
	motor[FRONT_LEFT_MOTOR] = power;
	motor[FRONT_RIGHT_MOTOR] = power;
}

void SimpleDriveDirection(int direction, int power, int distance)
{
	nMotorEncoder(FRONT_LEFT_MOTOR) = 0;  //set motor encoder to zero
	int distanceDriven = 0;								//set distance driven to 0
	setServos(direction);									//turn servos to the correct direction
	while(distanceDriven < distance)			//while distance driven is less than target distance, set motors to the set power and update distance driven
	{
		setMotors(power);
		distanceDriven = ENCODER_TO_CM; // times encoder value
	}
	setMotors(0);													//stop motors
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////End Section//////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
