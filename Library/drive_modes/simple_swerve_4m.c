#ifndef SWERVE_4M_C
#define SWERVE_4M_C

/* code review by Darrell
	driverRelativeMode should have a default initial value
*/

#include "../controllers/controller_defines.h"
#include "../motors/motors.c"
#include "../../ftc6220/includes/read_write.c"

bool driverRelativeMode; //if true, the robot will be relative to the field and driver. if false, it will drive like a car

//swerve module structure for storing all values specific to any given drive assembly
typedef struct
{
	float offsetAngle;        //in radians
	float servoPosition;     	//in degrees (0 - 360)
	float servoSpeed;
	float motorPower;         //in motor power units (0 - 100)
	//PID variables
	float error;
	float errorPrev;
	float errorSum;
	float servoTgt;
	float servoPositionPrev;
	float n;
}
DriveAssemblyState;

DriveAssemblyState Drive[4];

float RTgt;//currently unused, but would be to degree toward which the robot spins

//Attenuate the joystick used for rotation based on the maximum angular speed possible
//and find the "desired" angular velocity.
float JoystickToRotRate(float joystickZ)
{

	float attenuationSlope =  1 / INPUT_RANGE;
	//mapping maximum rotational speed to the allowed joystick input range, aka. finding the slope.

	float attenuationIntercept = -1 * ANALOG_DEAD_ZONE * sgn(joystickZ) * attenuationSlope;
	//finding the range taken up by the dead zone, aka. finding the intercept.

	if (abs(joystickZ) < ANALOG_DEAD_ZONE)
	{
		return 0;
	}
	else
	{
		return attenuationSlope * joystickZ + attenuationIntercept;
	}

}

float JoystickToMagnitude(float joystickXorY) // return a -1 to 1 value for motor power
{
	float attenuationSlope = INPUT_RANGE / MAX_MOTOR_POWER;

	float attenuationIntercept = -1 * sgn(joystickXorY) * attenuationSlope;

	if (abs(joystickXorY) < ANALOG_DEAD_ZONE)
	{
		return 0;
	}
	else
	{
		return (joystickXorY * attenuationSlope) + attenuationIntercept;
	}
}


void SimpleWriteToMotors(float cmps)
{
	Drive[FRONT_LEFT].motorPower = cmps * MOTOR_POWER_PER_CMPS;
	Drive[FRONT_RIGHT].motorPower = cmps * MOTOR_POWER_PER_CMPS;
	Drive[BACK_LEFT].motorPower = cmps * MOTOR_POWER_PER_CMPS;
	Drive[BACK_RIGHT].motorPower = cmps * MOTOR_POWER_PER_CMPS;
}

void SetServosDirection(float angle)
{
	Drive[FRONT_LEFT].servoPosition = angle;
	Drive[FRONT_RIGHT].servoPosition = angle;
	Drive[BACK_LEFT].servoPosition = angle;
	Drive[BACK_RIGHT].servoPosition = angle;
}

void SetServosRotateMode()
{
	Drive[FRONT_LEFT].servoPosition = 45;
	Drive[FRONT_RIGHT].servoPosition = 135;
	Drive[BACK_LEFT].servoPosition = 225;
	Drive[BACK_RIGHT].servoPosition = 315;
}

void RotateBotToDeg(int angle)
{
	SetServosRotateMode();
	RTgt = angle;
	rotateMode = true;
	wait1Msec(400);
	rotateMode = false;
}

#endif
