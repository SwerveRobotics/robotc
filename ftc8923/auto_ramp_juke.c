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
//Place robot facing backwards on top of
//ramp. Make the outside edge of the back
//right wheel 3 inches away from the edge
//of the ramp. Ensure the robot is lined
//up so the center of the robot will hit
//the center of the goal.
////////////////////////////////////////

#define TANK_4M

#include "include_files/includes.h"

task main()
{
	InitializeAuto();
	waitForStart();

	DriveBackwardDistanceGyro(50, 20);
	TurnRightDegrees(90, 50);
	DriveForwardDistanceGyro(20, 20);
	TurnLeftDegrees(90, 50);
	wait1Msec(8000);
	DriveBackwardDistanceGyro(57, 20);
	SetGoalGrabberPos(GRAB_GOAL_SERVO_POS);
	DriveForwardDistanceGyro(70,20);
	TurnRightDegrees(45,20);
	DriveForwardDistanceGyro(10,20);
	TurnLeftDegrees(90,20);
	TurnLeftDegrees(90,20);
	DriveBackwardDistanceGyro(20,20);
}
