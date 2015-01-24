#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IRSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     mtrFL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mtrBL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     collector,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     mtrBR,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_2,     mtrFR,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     mtrLifterL,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_2,     mtrLifterR,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    goalGrabber,          tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    container,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

////////// SETUP INSTRUCTIONS //////////
//Place robot facing backwards on left
//side of parking zone. Ensure the outside
//of the right omni-wheel and the center
//of the back right wheel are aligned with
//the inside edge of the tile seam.
////////////////////////////////////////

#define TANK_4M

#include "include_files/includes.h"

task main()
{
	InitializeAuto();
	waitForStart();

	//Get positioned to detect beacon
	DriveBackwardDistanceGyro(10, 50);
	TurnLeftDegrees(70, 30);
	DriveBackwardDistanceGyro(21, 20);

	DectectFloorIR();

	if(CENTER_GOAL_POSITION == 1)
	{
		KnockKickstandPos1();
	}
	else if(CENTER_GOAL_POSITION == 2)
	{
		KnockKickstandPos2();
	}
	else if(CENTER_GOAL_POSITION == 3)
	{
		KnockKickstandPos3();
	}
}
