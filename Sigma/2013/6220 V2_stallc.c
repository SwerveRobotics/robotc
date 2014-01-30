#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Hubs,  S3, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     sensorIR,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     motorArm,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motorFlag,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C2_1,     motorLifter,   tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servoBL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servoFL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servoSweeper,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_1,    servoWrist,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S3_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S3_C1_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c";

float slowMult = 1; // slow mode multiplier
float slowMultArm = 1; //slow mode multiplier for arm
int deadZone = 15;
float degToServo = (255.0/190.0); // converts degrees into servo values
int pos; // angle in degrees based on right joystick
float dist; // motor power based on right joystick
int servoPos; // servo values based on pos
int servoPosLast;

long wayTooLong = 1000;  // millisecond threshold for absolute stall
long tooLong = 250;  // millisecond threshod for partial stall
long sigMove = 100; // How many encoder ticks is a 'significant' movement

//variables used for stall code need to be initialized
int lastDirection[] = {0, 0, 0}; // Direction of last power -1 (reverse), 0 (stopped) or 1 (forward)
long timeLastSigMove[] = {0, 0, 0}; // Time last significant move occurred
long encLastSigMove[] = {0, 0, 0}; // Encoder reading at last significant move

int StallCode(tMotor motorSentTo, int wantedPower)
{
	int motorIndex;  //index value for the arrays we are storing values in.
	int direction = 0;
	switch(motorSentTo) //which motor power is being sent to
	{
		case motorFR: // This is the name of one of the motors as referenced in the configuraiton.
			motorIndex = 0;
			break;
		case motorArm:
			motorIndex = 1;
			break;
		case motorLifter:
			motorIndex = 2;
			break;
		default:
			break;
	}

	if (abs(wantedPower) < deadZone)  // Power below threshold, mark as stopped.
		direction = 0;
  else
  	direction = (wantedPower < 0) ? -1 : 1;

	if (direction == 0 || lastDirection[motorIndex] != direction)  // Stopped or changed direction.	Allow whatever power desired this time.
		{
    	lastDirection[motorIndex] = direction;
			timeLastSigMove[motorIndex]	 = time1[T1];
			encLastSigMove[motorIndex] = nMotorEncoder[motorSentTo];

			return wantedPower;
		}

 	lastDirection[motorIndex] = direction;

	if ( abs(encLastSigMove[motorIndex] - nMotorEncoder[motorSentTo]) > sigMove)  // Moved far enough to be considered significant, mark
		{
			timeLastSigMove[motorIndex]	= time1[T1];
			encLastSigMove[motorIndex] = nMotorEncoder[motorSentTo];

			return wantedPower;
		}

	if ( (time1[T1] - timeLastSigMove[motorIndex]) > wayTooLong )  // Time since last significant move too long, stalled
		{
			PlayTone(650,4);
			return 0;
		}

	if ( (time1[T1] - timeLastSigMove[motorIndex]) > tooLong )  // Time since last significant move too long, stalled
		{
			PlayTone(365,4);
			return wantedPower / 2;
		}

	return wantedPower;	// Haven�t moved far enough yet to be significant but haven�t timed out yet
}

task main()
{
	// set wrist servo to starting position
	servo[servoWrist] = 255;
	int servoLast = 255; // last servo value before letting go of joystick
	servoPos = 128;
	servoPosLast = servoPos;

	// set servos to default position
	servo[servoFL] = 90 * degToServo;
	servo[servoFR] = 90 * degToServo;
	servo[servoBL] = 90 * degToServo;
	servo[servoBR] = 90 * degToServo;

	ClearTimer(T1);
	nMotorEncoder[motorFR] = 0;
	nMotorEncoder[motorArm] = 0;

	while (true) // infinite loop
	{
		waitForStart();
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
			// set servo positions for rotation
			servo[servoFL] = 45 * degToServo;
			servo[servoFR] = 135 * degToServo;
			servo[servoBL] = 135 * degToServo;
			servo[servoBR] = 45 * degToServo;

			// motor power based on joystick
			motor[motorFL] = joystick.joy1_x1 * slowMult;
			motor[motorFR] = StallCode(motorFR, -1 * joystick.joy1_x1 * slowMult);
			motor[motorBL] = joystick.joy1_x1 * slowMult;
			motor[motorBR] = -1 * joystick.joy1_x1 * slowMult;
		}
		else if (dist < deadZone) // don't move
		{
			motor[motorFL] = 0;
			motor[motorFR] = StallCode(motorFR, 0);
			motor[motorBL] = 0;
			motor[motorBR] = 0;
		}
		else if (joystick.joy1_y2 >= 0 && joystick.joy1_x2 >= 0) // quadrant 1
		{
			servoPos = (int)((pos) * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
			wait1Msec(3*abs(servoPosLast - servoPos));
			servoPosLast = servoPos;

			motorPower = StallCode(motorFR, motorPower);
			motor[motorFL] = motorPower;
			motor[motorFR] = motorPower;
			motor[motorBL] = motorPower;
			motor[motorBR] = motorPower;
		}
		else if (joystick.joy1_y2 >= 0 && joystick.joy1_x2 <= 0) // quadrant 2
		{
			servoPos = (int)((pos) * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
			wait1Msec(3*abs(servoPosLast - servoPos));
			servoPosLast = servoPos;

			motorPower = StallCode(motorFR, motorPower);
			motor[motorFL] = motorPower;
			motor[motorFR] = motorPower;
			motor[motorBL] = motorPower;
			motor[motorBR] = motorPower;
		}
		else if (joystick.joy1_y2 <= 0 && joystick.joy1_x2 <= 0) // quadrant 3
		{
			pos = pos - 180; // change degrees to numbers between 0 and 180 because we're not using CR servos
			servoPos = (int)((pos) * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
			wait1Msec(3*abs(servoPosLast - servoPos));
			servoPosLast = servoPos;

			motorPower = StallCode(motorFR, motorPower);
			motor[motorFL] = motorPower * -1;
			motor[motorFR] = motorPower * -1;
			motor[motorBL] = motorPower * -1;
			motor[motorBR] = motorPower * -1;
		}
		else if (joystick.joy1_y2 <= 0 && joystick.joy1_x2 >= 0) // quadrant 4
		{
			pos = pos - 180; // change degrees to numbers between 0 and 180 because we're not using CR servos
			servoPos = (int)((pos) * degToServo);

			servo[servoFL] = servoPos;
			servo[servoFR] = servoPos;
			servo[servoBL] = servoPos;
			servo[servoBR] = servoPos;
			wait1Msec(3*abs(servoPosLast - servoPos));
			servoPosLast = servoPos;

			motorPower = StallCode(motorFR, motorPower);
			motor[motorFL] = motorPower * -1;
			motor[motorFR] = motorPower * -1;
			motor[motorBL] = motorPower * -1;
			motor[motorBR] = motorPower * -1;
		}

		if(abs(joystick.joy2_y1) > deadZone)
		{
			if (joy2Btn(6)) // right bumper
			{
				slowMultArm = 0.3; // do slow mode
			}
			else
			{
				slowMultArm = 1; // don't do slow mode
			}

			/*if((nMotorEncoder[motorArm] <= 0) && (nMotorEncoder[motorArm] > -3000))
			{
				motor[motorArm]= StallCode(motorArm, -joystick.joy2_y1 * slowMultArm);
			}*/
			/*int armPower = -joystick.joy2_y1 * slowMultArm;

			if((nMotorEncoder[motorArm] <= 0) && (armPower > 0))
			{
				motor[motorArm]= StallCode(motorArm, armPower);
			}
			else if((nMotorEncoder[motorArm] > -3000) && (armPower < 0))
			{
				motor[motorArm]= StallCode(motorArm, armPower);
			}*/

			int armPower = -joystick.joy2_y1 * slowMultArm;

			if(((nMotorEncoder[motorArm] <= 0) && (armPower > 0)) || ((nMotorEncoder[motorArm] > -7000) && (armPower < 0)))
			{
				motor[motorArm]= StallCode(motorArm, armPower);
			}
			/*else
			{
				motor[motorArm]= StallCode(motorArm, 0);
			}*/
		}
		else
		{
			motor[motorArm]= StallCode(motorArm, 0);
		}

		if(joy2Btn(8)) // right trigger
		{
			servo[servoWrist] = 255 - (joystick.joy2_y2 + 128); // wrist servo positions based on right joystick
			servoLast = 255 - (joystick.joy2_y2 + 128);
		}
		else
		{
			servo[servoWrist] = servoLast; // set servo position to last servo position
		}

		if(joy2Btn(5)) // left bumper
		{
			servo[servoSweeper] = 255; // spin roller in
		}
		else if(joy2Btn(7))
		{
			servo[servoSweeper] = 0;
		}
		else
		{
			servo[servoSweeper] = 128; // don't spin roller
		}

		if(joy2Btn(1) || joy1Btn(1))//both joy's
		{
			motor[motorFlag] = -100; // turn flag raiser
		}
		else if(joy2Btn(3) || joy1Btn(3))//both joy's
		{
			motor[motorFlag] = 100; // turn flag raiser
		}
		else
		{
			motor[motorFlag] = 0;
		}

		// use dpad on second controller to control lifter
    if(joy2Btn(4))
    {
      motor[motorLifter] = StallCode(motorLifter, 100);
    }
    else
    {
    	motor[motorLifter] = StallCode(motorLifter, 0);
  	}
	}
}
