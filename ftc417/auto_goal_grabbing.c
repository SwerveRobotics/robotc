#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     RightMid,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     RightSides,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     LeftMid,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     LeftSides,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    goalGrabber,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define TANK_4M

/* Code Review by Darrell
 - servo should be using a function.
 - *Good use of library.*
 - *Clean code looks really good.*
*/

#include "auto_init.c"
#include "JoystickDriver.c"
#include "../library/drive_modes/drive_modes.h"


 task main()
{
	AutoInitialize();
	waitForStart();

	DriveBackwardDistance(90, 20);	// what distance is this driving? 90 or 20?
	servo[goalGrabber] = 45;
	TurnRightTime(2000, 30);
	DriveForwardDistance(93, 50);
	TurnRightTime(1000, 30);
	DriveForwardDistance(40, 30);
}
