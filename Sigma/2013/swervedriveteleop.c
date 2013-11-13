#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorBR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorBL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorFL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servoFL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servoBL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c";

float slowMult = 1; // slow mode multiplier
int deadZone = 10;
float degToServo = (255.0/192.0); // converts degrees into servo values
int pos; // angle in degrees based on right joystick
float dist; // motor power based on right joystick
int servoPos; // servo values based on pos

task main()
{
	// set servos to default position
	servo[servoFL] = 90 * degToServo;
	servo[servoFR] = 90 * degToServo;
	servo[servoBL] = 90 * degToServo;
	servo[servoBR] = 90 * degToServo;

	while (true) // infinite loop
	{
		getJoystickSettings(joystick); // find joystick values

		pos = (int)radiansToDegrees(atan2(joystick.joy1_y2, joystick.joy1_x2)); // get servo degrees based on right joystick x and y values
		/*if(joystick.joy1_x2 == 0)
		{
			pos = 0;
		}*/
		dist = sqrt(joystick.joy1_y2 * joystick.joy1_y2 + joystick.joy1_x2 * joystick.joy1_x2); // use distance formula to get motor powers based on right joystick x and y values

		// slow mode
		if (joy1Btn(6)) // right bumper
		{
			slowMult = 0.3; // do slow mode
		}
		else
		{
			slowMult = 1; // don't do slow mode
		}

		int motorPower = (int)(dist * slowMult); // motor power values with slow mode multiplier

		if (abs(joystick.joy1_x1) > deadZone) // turning based on left joystick
		{
			// motor power based on joystick
			motor[motorFL] = joystick.joy1_x1 * slowMult;
			motor[motorFR] = -1 * joystick.joy1_x1 * slowMult;
			motor[motorBL] = joystick.joy1_x1 * slowMult;
			motor[motorBR] = -1 * joystick.joy1_x1 * slowMult;

			// set servo positions for rotation
			servo[servoFL] = 45 * degToServo;
			servo[servoFR] = 135 * degToServo;
			servo[servoBL] = 135 * degToServo;
			servo[servoBR] = 45 * degToServo;
		}
		else if (dist < deadZone) // don't move
		{
			motor[motorFL] = 0;
			motor[motorFR] = 0;
			motor[motorBL] = 0;
			motor[motorBR] = 0;
		}
		else if (joystick.joy1_y2 > 0 && joystick.joy1_x2 > 0) // quadrant 1
		{
			motor[motorFL] = motorPower;
			motor[motorFR] = motorPower;
			motor[motorBL] = motorPower;
			motor[motorBR] = motorPower;

			servoPos = (int)((pos) * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
		}
		else if (joystick.joy1_y2 > 0 && joystick.joy1_x2 < 0) // quadrant 2
		{
			motor[motorFL] = motorPower;
			motor[motorFR] = motorPower;
			motor[motorBL] = motorPower;
			motor[motorBR] = motorPower;

			servoPos = (int)((pos) * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
		}
		else if (joystick.joy1_y2 < 0 && joystick.joy1_x2 < 0) // quadrant 3
		{
			motor[motorFL] = motorPower * -1;
			motor[motorFR] = motorPower * -1;
			motor[motorBL] = motorPower * -1;
			motor[motorBR] = motorPower * -1;

			pos = pos - 180; // change degrees to numbers between 0 and 180 because we're not using CR servos
			servoPos = (int)((pos) * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
		}
		else if (joystick.joy1_y2 < 0 && joystick.joy1_x2 > 0) // quadrant 4
		{
			motor[motorFL] = motorPower * -1;
			motor[motorFR] = motorPower * -1;
			motor[motorBL] = motorPower * -1;
			motor[motorBR] = motorPower * -1;

			pos = pos - 180; // change degrees to numbers between 0 and 180 because we're not using CR servos
			servoPos = (int)((pos) * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
		}
	}

}
