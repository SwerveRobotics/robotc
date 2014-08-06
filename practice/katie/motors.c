#ifndef MOTORS_C
#define MOTORS_C



void DriveRightMotor(int power)
{
	motor[right] = power;
}


void DriveLeftMotor(int power)
{
	motor[left] = power;
}


#endif
