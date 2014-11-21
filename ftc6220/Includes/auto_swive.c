#ifndef AUTO_SWIVE_C
#define AUTO_SWIVE_C

const float CENTER_RADIUS = 22.86;//centimeters

const float MOTOR_GEAR_RATIO = 1.0;

const float SERVO_GEAR_RATIO = 1.0;

const float WHEEL_RADIUS = 10.16;//centimeters

#include "../../Library/drive_modes/swerve_4m.c"


int MAX_MOTOR_GEAR_RATIO = 1;   //just added that for testing purposes
int WHEEL_DIAMETER = 1; //ditto
const float WHEEL_CIRCUM = WHEEL_RADIUS * 2.0 *PI;			//calculates wheel circumfrence so that CM can be inputed instead of encoder ticks
const int ENCODER_RESOLUTION = 1024;									//shows number of encoder ticks per rotation. I think this is wrong, and actually should be 1440
const float ENCODER_TO_CM = (ENCODER_RESOLUTION / MAX_MOTOR_GEAR_RATIO) / (WHEEL_DIAMETER * PI);   		//changes encoder ticks to centimeters so centimeters can be inputed instead. not using this yet. I hope to eventually.


// MOVE SWERVE CONSTANTS HERE //

void writeToServos(int value)				//allows all servos to be written to while only typing the value once.
{
	servo[BACK_LEFT_SERVO] = value;
	servo[BACK_RIGHT_SERVO] = value;
	servo[FRONT_LEFT_SERVO] = value;
	servo[FRONT_RIGHT_SERVO] = value;
}

void degreesToMsPulse(int degrees)		//changes degree position of servo to how many MS a pulse needs to be given for
{
	int	MsPulse;
	MsPulse = degrees; //times something to make it work that I haven't figured out yet.
}

void setServos(int direction)			//sets servos to the correct degree setting using the degreesToMsPulse function. I need to add encoders to ensure accuracy.
{
	int MsPulse;
	degreesToMsPulse(direction);		//calculates MS of pulse based on degrees
	writeToServos(1);									//starts pulse
	wait1Msec(MsPulse);							//waits calculated number of MS.
	writeToServos(0);									//ends pulse
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
	nmotorencoder(FRONT_LEFT_MOTOR) = 0; //set motor encoder to zero
	int distanceDriven = 0;								//set distance driven to 0
	setServos(direction);									//turn servos to the correct direction
	while(distanceDriven < distance)			//while distance driven is less than target distance, set motors to the set power and update distance driven
	{
		setMotors(power);
		distanceDriven = ENCODER_TO_CM; // times encoder value
	}
	setMotors(0);													//stop motors
}

#endif
