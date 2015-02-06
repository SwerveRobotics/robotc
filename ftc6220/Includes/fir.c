#ifndef FIR_C
#define FIR_C

#include "controller.c"

typedef struct
{
	float input;
	float output;
	float pastValues[20];
	float weight[20];
}FIR_Struct;

FIR_Struct axis[3];

task FIR_Task()
{
	for (int p = 0; p < 3; p++)
	{
		for (int q = 0; q < 20; q++)
		{
			axis[p].pastValues[q] = 0;
			axis[p].weight[q] = (q + 1) / 40;
		}

	}
	while (true)
	{
		axis[JOY_X].pastValues[0] = joystick.joy1_x2;
		axis[JOY_Y].pastValues[0] = joystick.joy1_y2;
		axis[JOY_Z].pastValues[0] = joystick.joy1_x1;

		for (int p = 0; p <3; p++)
		{
			axis[p].output = 0;
			for (int q = 0; q < 19; q ++)
			{
				axis[p].pastValues[q + 1] = axis[p].pastValues[q];
				axis[p].output += (axis[p].pastValues[q] * axis[p].weight[q]);
			}
		}
		//writeDebugStreamLine("%f", axis[JOY_X].output);
	}
	wait10Msec(10);
}

#endif
