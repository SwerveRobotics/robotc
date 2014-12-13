#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     LeftMid,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     LeftSides,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     RightMid,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     RightSides,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define TANK_4M
#include "../library/drive_modes/drive_modes.h"
#include "../library/controllers/tank_controller.c"
#include "init_teleop.c"

#pragma debuggerWindows("nxtLCDScreen");
//#pragma debuggerWindows("Servos");
#pragma debuggerWindows("joystickSimple");

#include "JoystickDriver.c"

task main()
{
	//RegisterDriveMotors(LeftMid, LeftSides, RightMid, RightSides);
	InitializeTeleOP();

	waitForStart();

	StartTask(DriveTank);
	while(true)
	{
	}
}
