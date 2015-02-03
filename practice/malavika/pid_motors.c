#ifndef PID_MOTORS_C
#define PID_MOTORS_C

const float deadZone = 15;
int requestedSpeed = 0;

void RequestMotorSpeed(int speed)
{
	requestedSpeed = speed;
}

void SetMotorSpeed(tMotor mtr, int speed)
{
	motor[mtr] = speed;
}

int GetMotorSpeed(tMotor mtr,)
{
	return motor[mtr];
}

#endif
