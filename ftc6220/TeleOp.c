#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorFan1,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorFan2,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     motorSweep,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoFL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    servoFR,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    servoBL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_4,    servoBR,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_5,    servoGrabber,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    servoHopper,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C3_1,    servoSweep,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_2,    servoTube,            tServoStandard)
#pragma config(Servo,  srvo_S2_C3_3,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S2_C3_4,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S2_C3_5,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C3_6,    servo4,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "includes/swive.c"
#include "Includes/manipulators.c"
#include "Includes/writing.c"
task main()
{
	RegisterMotors(
		motorFR,
		motorFL,
		motorBL,
		motorBR,
		motorSweep,
		motorFan1,
		motorFan2
	);

	RegisterServos(
		servoFR,
		servoFL,
		servoBL,
		servoBR,
		servoGrabber,
		servoSweep,
		servoTube
	);
	RunFan(true);
	StartTask(drive);
	StartTask(manipulators);
	while(true)
	{

	}
}
