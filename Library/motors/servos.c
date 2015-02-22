#ifndef SERVOS_C
#define SERVOS_C

///////////// CODE REVIEW BY DRYW ///////////////////
// This file should probably go into a servos folder

#include "servo_defines.h"

void SetServoPosition(TServoIndex servoName, int position)
{
	servo[servoName] = position;
}

void SetServoSpeed(TServoIndex servoName, float speed)
{
	servo[servoName] = CR_SERVO_ZERO + (speed * (SERVO_RANGE / 2));
}

void SetServoSpeed(TServoIndex servoName, float speed, int direction)
{
	servo[servoName] = CR_SERVO_ZERO + (abs(speed) * direction * (SERVO_RANGE / 2));
}

#endif
