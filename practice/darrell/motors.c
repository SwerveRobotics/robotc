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
	motor[left] = AttenuateControllerOutput(speed);
}

// Assumes speed value is coming from a controller //
void SetRightMotorSpeed(int speed)
{
	motor[right] = AttenuateControllerOutput(speed);
}


#endif
