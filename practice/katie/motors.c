#ifndef MOTORS_C
#define MOTORS_C

#include "controllers.c"

const float MOTOR_MIN_POWER = 20.0;
const float MOTOR_MAX_POWER = 100.0;

const float CONTROLLER_SLOPE = (MOTOR_MIN_POWER-MOTOR_MAX_POWER)/(CONTROLLER_MIN-CONTROLLER_MAX);
const float CONTROLLER_INT = (MOTOR_MIN_POWER-CONTROLLER_SLOPE*CONTROLLER_MIN);
int ScaleInput (int controllerVal)
{
	return (CONTROLLER_SLOPE*controllerVal+CONTROLLER_INT);
}

void DriveRightMotor(int power)
{
	motor[right] = ScaleInput(power);
}


void DriveLeftMotor(int power)
{
	motor[left] = ScaleInput(power);
}


#endif
