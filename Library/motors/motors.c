#ifndef MOTORS_C
#define MOTORS_C

#include "motor_defines.h"
#include "../controllers/controller_defines.h"

float MOTOR_GEAR_RATIO;
float SERVO_GEAR_RATIO;

const float MOTOR_POWER_PER_CMPS = 1.207671; //theoretical motor power nessesary to move at 1 m/s with 4in wheels
const float MAX_MOTOR_SPEED_CMPS = 81.93;//theoretical max based on 154rpm motor and 4in diameter wheel // gear ratio?

const float SERVO_TICK_PER_DEGREE = 1.4118;//number of servo ticks nessesary to rotate 1 degree

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

//Set Motor Power from a CM/S value
void mpsToMotor(tMotor motorName, float cmps)
{
	motor[motorName] = 	MOTOR_POWER_PER_CMPS * MOTOR_GEAR_RATIO * cmps;
}

void degToCRServo(TServoIndex servoName, int angle)
{
	//sig code here
}

void degToServo(TServoIndex servoName, int angle)
{
	servo[servoName] = SERVO_GEAR_RATIO * SERVO_TICK_PER_DEGREE * angle;
}

#endif
