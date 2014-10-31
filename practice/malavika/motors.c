#ifndef MOTORS_C
#define MOTORS_C

const float DEAD_ZONE = 15.0;
const float MAX_JOY = 128.0;
const float MIN_SPEED = 20.0;
const float MAX_SPEED = 100.0;

const float SLOPE = (MAX_SPEED - MIN_SPEED)/(MAX_JOY - DEAD_ZONE);
const float INTERCEPT = MIN_SPEED - SLOPE * DEAD_ZONE;

void SetSpeed(tMotor mtr, int speed)
{
	motor[mtr] = (SLOPE * abs(speed) + INTERCEPT) * sgn(speed);
}

#endif
