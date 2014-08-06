#ifndef MOTORS_C
#define MOTORS_C

#include "motor_defines.h"
#include "controller_defines.h"

// Desired Controller Input and Motor Ouput is assumed to be as follows:
// INPUT             OUTPUT
// -MAX_ANALOG       -MAX_MOTOR_SPEED
// -ANALOG_DEAD_ZONE -MIN_MOTOR_SPEED
// +ANALOG_DEAD_ZONE +MIN_MOTOR_SPEED
// +MAX_ANALOG       +MAX_MOTOR_SPEED

// Assuming a linear relationship between these values, we can solve for the slope //
const float LINEAR_MOTOR_CONTROL_SLOPE = (MAX_MOTOR_SPEED-MIN_MOTOR_SPEED)/(MAX_ANALOG-ANALOG_DEAD_ZONE);
// Solve for the Y-intercept (equation was sovled for with a simple system of two equations assuming a linear relationship)
const float LINEAR_MOTOR_CONTROL_INTERCEPT = (MIN_MOTOR_SPEED-(LINEAR_MOTOR_CONTROL_SLOPE*ANALOG_DEAD_ZONE));

// Calculates Output from Input based on a Linear Relationship
int AttenuateControllerOutput(int output)
{
	// using linear equation in slope-intercept form of y = mx + b
  return (LINEAR_MOTOR_CONTROL_SLOPE*output + sgn(output)*LINEAR_MOTOR_CONTROL_INTERCEPT);
}

// Assumes speed value is coming from a controller //
void SetLeftMotorSpeed(int speed)
{
	motor[leftFront] = AttenuateControllerOutput(speed);
	motor[leftRear] = AttenuateControllerOutput(speed);
}

// Assumes speed value is coming from a controller //
void SetRightMotorSpeed(int speed)
{
	motor[rightFront] = AttenuateControllerOutput(speed);
	motor[rightRear] = AttenuateControllerOutput(speed);
}

void Strafe(int speed)
{
	motor[rightFront] = -1.0*AttenuateControllerOutput(speed);
	motor[leftRear] = -1.0*AttenuateControllerOutput(speed);

	motor[rightRear] = AttenuateControllerOutput(speed);
	motor[leftFront] = AttenuateControllerOutput(speed);
}


void Turn(int speed)
{
	motor[rightFront] = -1.0*AttenuateControllerOutput(speed);
	motor[rightRear] = -1.0*AttenuateControllerOutput(speed);
	motor[leftFront] = AttenuateControllerOutput(speed);
	motor[leftRear] = AttenuateControllerOutput(speed);
}

void MoveArm(int speed)
{
	motor[arm1] = speed;
	motor[arm2] = speed;
}

void MoveBucket(int speed)
{
	motor[bucket] = speed;
}

#endif
