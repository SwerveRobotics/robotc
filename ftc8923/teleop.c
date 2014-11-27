#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Hubs,  S4, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IRSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     mtrFL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mtrBL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     collector,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     mtrBR,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_2,     mtrFR,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    goalGrabber,          tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    irRotator,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define TANK_4M

#include "../Library/controllers/tank_controller.c"
#include "include_files/init_teleop.c"
#include "include_files/functions.c"

task main()
{
	InitializeTeleop();

	waitForStart();

	StartTask(DriveTank);
	while(true)
	{
		getJoystickSettings(joystick);

		if(joy1Btn(8) == 1)
		{
			GrabGoal();
		}

		if(joy1Btn(7) == 1)
		{
			ReleaseGoal();
		}
		if(joy2Btn(8) == 1)
		{
			CollectBalls();
		}
		else if(joy2Btn(7) == 1)
		{
			ReleaseBalls();
		}
		else
		{
			StopCollector();
		}
	}
}
