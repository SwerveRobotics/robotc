#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IRSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Motor,  mtr_S1_C1_1,     mtrFR,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     mtrBR,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     mtrFL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mtrBL,         tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    goalGrabber,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    irRotator,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "../Library/drive_modes/tank_4m.c"
#include "../Library/autonomous/auto_drive.c"
#include "center_objectives.c"
#include "JoystickDriver.c"

task main()
{
	ASSUME_CONTROLLER_INPUT = false;
	#include "initialize_robot.h"

	waitForStart();

	//Robot drives backward until it reaches the rolling goal
	//Goal grabbers extend
	//Robot drives back towards ramp
	//Robot turns right to go to parking zone
	//Robot drives strait toward parking zone
	//Robot turns while in parking zone
	//Robot ensures goal is in parking zone

	DriveBackwardDistance(80, 20);
	servo[goalGrabber] = 0;
	wait1Msec(500);

	//This doesn't use TurnRightDegrees, as we don't have a gyro
	TurnRight(50);
	wait1Msec(300);

	DriveForwardDistance(94, 20);

	//Not using the funtion for the same reason above
	TurnRight(50);
	wait1Msec(500);

	DriveForwardDistance(10,20);
}
