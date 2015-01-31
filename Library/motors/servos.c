#ifndef SERVOS_C
#define SERVOS_C

void SetServoPosition(TServoIndex servoName, int position)
{
	servo[servoName] = position;
}

#endif
