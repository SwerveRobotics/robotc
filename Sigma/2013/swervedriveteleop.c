#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     lazySuzan,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servoFL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servoBL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    brush,                tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c";

float slowMult = 1;
int deadZone = 10;


task main()
{
	while (true)
	{
		getJoystickSettings(joystick);

		int pos = atan(joystick.joy1_y2 / joystick.joy1_x2);
		float dist = sqrt(joystick.joy1_y2 ^ 2 + joystick.joy1_x2 ^ 2);

		if (joystick.joy1_Buttons == 6)
		{
			slowMult = 1;
		}
		else
		{
			slowMult = 0.3;
		}

		if ( dist <= deadZone)
		{
			motor[motorFL] = 0;
			motor[motorFR] = 0;
			motor[motorBL] = 0;
			motor[motorBR] = 0;
		}
		else if (dist > deadZone && pos >= 0)
		{
			motor[motorFL] = dist * 0.75;
			motor[motorFR] = dist * 0.75;
			motor[motorBL] = dist * 0.75;
			motor[motorBR] = dist * 0.75;

			float servoPos = pos * 1.416;

			servo[servoFL] = servoPos
			servo[servoFR] = servoPos
			servo[servoBL] = servoPos
			servo[servoBR] = servoPos
		}
		else
		{
			motor[motorFL] = dist * -0.75;
			motor[motorFR] = dist * -0.75;
			motor[motorBL] = dist * -0.75;
			motor[motorBR] = dist * -0.75;

			float servoPos = (pos - 180) * 1.416;

			servo[servoFL] = servoPos
			servo[servoFR] = servoPos
			servo[servoBL] = servoPos
			servo[servoBR] = servoPos
		}


	}

}
