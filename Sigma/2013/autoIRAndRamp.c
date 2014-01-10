#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     sensorIR,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     motorArm,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motorFlag,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servoBL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servoFL,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servoWrist,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_6,    servoRoller,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c";

float degToServo = (255.0/192.0); // converts degrees into servo values

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
		default:
			break;
	}

	if (abs(wantedPower) == 0)  // Power below threshold, mark as stopped.
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
	waitForStart();
	ClearTimer(T1);
	nMotorEncoder[motorFR] = 0; // zero front right motor encoder
	nMotorEncoder[motorArm] = 0; // zero arm motor

	// set wrist servo to starting position
	servo[servoWrist] = 0;

	// set servos to go sideways
	servo[servoFL] = 0;
	servo[servoFR] = 0;
	servo[servoBL] = 0;
	servo[servoBR] = 0;
	wait1Msec(750);

	while(SensorValue(sensorIR) != 4) // go sideways until IR beacon
	{
		motor[motorFL] = 100;
		motor[motorFR] = StallCode(motorFR, 100);
		motor[motorBL] = 100;
		motor[motorBR] = 100;
	}
	// stop motors
	motor[motorFL] = 0;
	motor[motorFR] = StallCode(motorFR, 0);
	motor[motorBL] = 0;
	motor[motorBR] = 0;

	// place cube with arm
	while(nMotorEncoder[motorArm] < 500){
		motor[motorArm] = StallCode(motorArm, 100);
	}
	nMotorEncoder[motorArm] = 0;
	// maybe do something with wrist servo.
	while(nMotorEncoder[motorArm] > -500){
		motor[motorArm] = StallCode(motorArm, -100);
	}
	motor[motorArm] = StallCode(motorArm, 0);

	while(nMotorEncoder[motorFR] < (1440 * 4)) // go sideways until there's space to move around the ramp
	{
		motor[motorFL] = 100;
		motor[motorFR] = StallCode(motorFR, 100);
		motor[motorBL] = 100;
		motor[motorBR] = 100;
	}
	// stop motors
	motor[motorFL] = 0;
	motor[motorFR] = StallCode(motorFR, 0);
	motor[motorBL] = 0;
	motor[motorBR] = 0;

	// turn servos to default
	servo[servoFL] = 90 * degToServo;
	servo[servoFR] = 90 * degToServo;
	servo[servoBL] = 90 * degToServo;
	servo[servoBR] = 90 * degToServo;
	wait1Msec(200);

	nMotorEncoder[motorFR] = 0; // zero front left motor encoder

	// go forward until there's space to get onto ramp
	while(nMotorEncoder[motorFR] < (1440 * 3.5))
	{
		motor[motorFL] = 100;
		motor[motorFR] = StallCode(motorFR, 100);
		motor[motorBL] = 100;
		motor[motorBR] = 100;
	}
	// stop motors
	motor[motorFL] = 0;
	motor[motorFR] = StallCode(motorFR, 0);
	motor[motorBL] = 0;
	motor[motorBR] = 0;

	// turn servos sideways
	servo[servoFL] = 0;
	servo[servoFR] = StallCode(motorFR, 0);
	servo[servoBL] = 0;
	servo[servoBR] = 0;
	wait1Msec(200);

	// go onto ramp
	while(nMotorEncoder[motorFR] > -1440 * 0.5)
	{
		motor[motorFL] = -100;
		motor[motorFR] = StallCode(motorFR, -100);
		motor[motorBL] = -100;
		motor[motorBR] = -100;
	}
	// stop motors
	motor[motorFL] = 0;
	motor[motorFR] = StallCode(motorFR, 0);
	motor[motorBL] = 0;
	motor[motorBR] = 0;
}
