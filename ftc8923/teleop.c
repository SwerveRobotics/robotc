#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     mtrFL,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     mtrBL,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     mtrFR,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     mtrBR,         tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "tank.c"

task main()
{
	StartTask(Drive);
	while(true)
	{
		//Main loop
	}
}
