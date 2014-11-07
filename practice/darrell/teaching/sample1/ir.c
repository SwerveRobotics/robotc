#ifndef IR_C
#define IR_C

#include "motors.c"

void DriveForwardUntilIR(int irval)
{
	while(SensorValue[IRseeker] != 9)
	{
		DriveForward(HALF_IMPULSE);
	}
	StopMotors();
}










#endif
