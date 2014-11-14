#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IRSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Motor,  mtr_S1_C1_1,     mtrFR,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     mtrBR,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     mtrFL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mtrBL,         tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    goalGrabber,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    irRotator,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    container,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define TANK_4M

#include "../Library/controllers/tank_controller.c"
#include "init_teleop.c"

task main()
{
	InitializeTeleop();

	waitForStart();

	StartTask(DriveTank);
	while(true)
	{
		getJoystickSettings(joystick);

		if(joy2Btn(1) == 1)
		{
			servo[goalGrabber] = 100;
		}

		if(joy2Btn(3) == 1)
		{
			servo[goalGrabber] = 160;
		}
		/*if(joy1Btn(2) == 1)
		{
			servo[container] = ;
		}*/
	}
}
