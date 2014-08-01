#ifndef MOTORS_C
#define MOTORS_C

void SetLeftMotorSpeed(int speed)
{
	motor[left] = speed;
}
void SetRightMotorSpeed(int speed)
{
	motor[right] = speed;
}
#endif
