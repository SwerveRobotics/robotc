#ifndef SWERVE_4M_C
#define SWERVE_4M_C

#include "../controllers/controller_defines.h"
#include "../motors/motors.c"
#include "../../ftc6220/includes/writing.c"
//Attenuate the joystick used for rotation based on the maximum angular speed possible
//and find the "desired" angular velocity.
float JoystickToRotRate(float joystickZ)
{

	float attenuationSlope =  1 / joystickRange;
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
	float attenuationSlope = joystickRange / MAX_MOTOR_POWER;

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

float CalculateDriveAngle(float valueX, float valueY)
{
	int tangent = 57.3 * atan2(valueX, valueY); //drive angle
	if (tangent < 0)
	{
		return tangent + 360;
	}
	else
	{
		return tangent;
	}
}

void SimpleWriteToMotors(float cmps)
{
	CMPSToMotor(FRONT_LEFT_MOTOR,  cmps);
	CMPSToMotor(BACK_LEFT_MOTOR,   cmps);
	CMPSToMotor(BACK_RIGHT_MOTOR,  cmps);
	CMPSToMotor(FRONT_RIGHT_MOTOR, cmps);
}

void SimpleWriteToServos(int angle)
{
	DegToCRServo(FRONT_LEFT_SERVO,  FRONT_LEFT_SERVO_ENC,  angle);
	DegToCRServo(BACK_LEFT_SERVO,   BACK_LEFT_SERVO_ENC,   angle);
	DegToCRServo(BACK_RIGHT_SERVO,  BACK_RIGHT_SERVO_ENC,  angle);
	DegToCRServo(FRONT_RIGHT_SERVO, FRONT_RIGHT_SERVO_ENC, angle);
}

void SetServosRotateMode()
{
	DegToCRServo(FRONT_LEFT_SERVO,  FRONT_LEFT_SERVO_ENC,  0  );
	DegToCRServo(BACK_LEFT_SERVO,   BACK_LEFT_SERVO_ENC,   90 );
	DegToCRServo(BACK_RIGHT_SERVO,  BACK_RIGHT_SERVO_ENC,  180);
	DegToCRServo(FRONT_RIGHT_SERVO, FRONT_RIGHT_SERVO_ENC, 270);
}

#endif
