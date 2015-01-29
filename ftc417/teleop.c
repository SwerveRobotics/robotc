#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     LeftMid,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     LeftSides,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     RightMid,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     RightSides,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     Arm,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    goalGrabber,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* Code Review by Darrell
 - Servo needs functions written
 - replace magic numbers with const ints defined with descriptive names per our style guide
 - *Good use of library files.*
*/


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
  RegisterDriveMotors(LeftMid, LeftSides, RightMid, RightSides);
	InitializeTeleOP();

	waitForStart();

	StartTask(DriveTank);
	while(true)
	{
		if (joy2Btn(3) == 1)
		{
			servo[goalGrabber] = 150;
		}
		else if (joy2Btn(2) == 1)
		{
			servo[goalGrabber] = 45;
		}

		/*while (joy2Btn(7) == 1 && nMotorEncoder[Arm] <= 1110)
		{
			motor[Arm] = 50;
		}
		nMotorEncoder[Arm] = 0;

		while(joy2Btn(6) == 1 && nMotorEncoder[Arm] >= -1110)
		{
			motor[Arm] = -50;
		}
		nMotorEncoder[Arm] = 0;*/


	}
}
