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
// NOTE: ASSUME_CONTROLLER_INPUT defaults to true
//       If you are calling this function from a non-analog input,
//       make sure to call it as SetMotorPower(myMotor, myPower, false)
void SetMotorPower(tMotor motorName, int power, bool useControllerInput = ASSUME_CONTROLLER_INPUT)
{
	if(useControllerInput==true)
		motor[motorName] = AttenuateControllerOutput(power);
	else
		motor[motorName] = power;
}


#endif
