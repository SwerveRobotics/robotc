#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IRSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Motor,  mtr_S1_C1_1,     mtrFL,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     mtrBL,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     mtrFR,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     mtrBR,         tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    goalGrabber,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    irRotator,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "tankSimple.c"

task main()
{
	ASSUME_CONTROLLER_INPUT = false;
	RegisterDriveMotors(mtrFL, mtrBL, mtrFR, mtrBR);

	StartTask(Drive);
	while(true)
	{
		getJoystickSettings(joystick);

		if(joystick.joy1_Buttons == 1)
		{
			servo[irRotator] = servo[irRotator] + 1;
		}

		if(joystick.joy1_Buttons == 2)
		{
			servo[irRotator] = servo[irRotator] - 1;
		}
	}
}
