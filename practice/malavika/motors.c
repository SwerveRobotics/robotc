#ifndef MOTORS_C
#define MOTORS_C

const float deadZone = 15.0;
const float maxJoy = 128.0;
const float minSpeed = 20.0;
const float maxSpeed = 100.0;

const float slope = (maxSpeed - minSpeed)/(maxJoy - deadZone);
const float intercept = minSpeed - slope * deadZone;

void SetSpeed(tMotor mtr, int speed)
{
	motor[mtr] = (slope * abs(speed) + intercept) * sgn(speed);
}

#endif
