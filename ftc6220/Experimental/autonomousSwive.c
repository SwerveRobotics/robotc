#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeftM,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backLeftM,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     backRightM,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     frontRightM,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     frontLeftServoEncoder, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     backLeftServoEncoder, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     backRightServoEncoder, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     frontRightServoEncoder, tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    frontLeftS,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_2,    backLeftS,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_3,    backRightS,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_4,    frontRightS,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "../Includes/auto_swive.c"
#include "../Includes/swive.c"
#include "../Includes/manipulators.c"
#include "../../Library/drive_modes/swerve_4m.c"

task main()
{
	setServoEncoders(0);
	SimpleDriveDirection(0, 75, 25);			//direction in degrees, motor power, centimeters

}
