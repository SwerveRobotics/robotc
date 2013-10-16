#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorFR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorBR,       tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servoFL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servoBL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c";

float slowMult = 1;
int deadZone = 10;

float dist = sqrt(joystick.joy1_y2 ^ 2 + joystick.joy1_x2 ^ 2);//distance from center of joy1


void setMotorsServos()//self explainitory
{


	if ((joystick.joy1_y2 > 0) || (joystick.joy1_y2 == 0 && joystick.joy1_x2 > 0))//if motor need not be reversed
	{
		motor[motorFL] = dist * 0.75;//sets motor Front Right to distance (see above)
		motor[motorFR] = dist * 0.75;
		motor[motorBL] = dist * 0.75;
		motor[motorBR] = dist * 0.75;
	}
	else//else
	{
		motor[motorFL] = dist * -0.75;
		motor[motorFR] = dist * -0.75;
		motor[motorBL] = dist * -0.75;
		motor[motorBR] = dist * -0.75;
	}

	if ((joystick.joy1_y2 / joystick.joy1_x2) >= 0)//if slope >= 0
	{
		int pos = atan(joystick.joy1_y2 / joystick.joy1_x2);
		float servoPos = pos * 1.416;

		servo[servoFL] = servoPos;
		servo[servoFR] = servoPos;
		servo[servoBL] = servoPos;
		servo[servoBR] = servoPos;

	}
	else
	{
		int pos = atan(joystick.joy1_y2 / joystick.joy1_x2);//angle
		float servoPos = (180 + pos) * 1.416;

		servo[servoFL] = servoPos;
		servo[servoFR] = servoPos;
		servo[servoBL] = servoPos;
		servo[servoBR] = servoPos;

	}


}


task main()
{
	while (true)
	{
		getJoystickSettings(joystick);



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
			motor[motorFR] = 0;
			motor[motorFL] = 0;
			motor[motorBR] = 0;
			motor[motorBR] = 0;
		}
		else
		{

			setMotorsServos();


		}


	}
}
