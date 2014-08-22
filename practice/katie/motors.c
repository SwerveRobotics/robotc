#ifndef MOTORS_C
#define MOTORS_C


const float DEAD_ZONE = 15.0;
const float CONTROLLER_MAX = 128.0;

float m = (20.0-100.0)/(15.0-128.0);
float b = (20.0-m*15.0);
int ScaleInput (int controllerVal)
{
	return (m*controllerVal+b);
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
