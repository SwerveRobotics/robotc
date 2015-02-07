#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  HTServo,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorFan1,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorFan2,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorSweeper,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorEnc,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servoFL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_2,    servoFR,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_3,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    servoBL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C2_2,    servoBR,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C2_3,    servoLoader,          tServoStandard)
#pragma config(Servo,  srvo_S2_C2_4,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo7,               tServoNone)
#pragma config(Servo,  srvo_S2_C3_1,    servoSweeperArm,      tServoStandard)
#pragma config(Servo,  srvo_S2_C3_2,    servoSweeper1,        tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C3_3,    servoSweeper2,        tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C3_4,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S2_C3_5,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C3_6,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C4_1,    servoTubeWinch,       tServoStandard)
#pragma config(Servo,  srvo_S2_C4_2,    servoTubeSlide,       tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C4_3,    servoGrabber,              tServoNone)
#pragma config(Servo,  srvo_S2_C4_4,    servo14,              tServoNone)
#pragma config(Servo,  srvo_S2_C4_5,    servo15,              tServoNone)
#pragma config(Servo,  srvo_S2_C4_6,    servo16,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true)
	{
		servo[servoGrabber] = 0;
	}
}
