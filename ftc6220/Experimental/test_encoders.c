#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Hubs,  S3, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorFan1,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorFan2,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     motorSweep,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoFL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    servoBL,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    servoTubeSlide,       tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_4,    servo1_3_4,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_5,    servo1_3_5,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    servo1_3_6,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_1,    servoFR,              tServoStandard)
#pragma config(Servo,  srvo_S2_C3_2,    servoBR,              tServoStandard)
#pragma config(Servo,  srvo_S2_C3_3,    servoTubeLift,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_4,    servo2_3_4,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_5,    servo2_3_5,           tServoStandard)
#pragma config(Servo,  srvo_S2_C3_6,    servo2_3_6,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_1,    servoSweepArm,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_2,    servoTubeWinch,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_3,    servoLoader,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_4,    servo3_1_4,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_5,    servo3_1_5,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_6,    servo3_1_6,           tServoStandard)
#pragma config(Servo,  srvo_S3_C2_1,    servoSweep1,        tServoStandard)
#pragma config(Servo,  srvo_S3_C2_2,    servoSweep2,       tServoStandard)
#pragma config(Servo,  srvo_S3_C2_3,    servoGrabber,         tServoStandard)
#pragma config(Servo,  srvo_S3_C2_4,    servo3_2_4,           tServoStandard)
#pragma config(Servo,  srvo_S3_C2_5,    servo3_2_5,           tServoStandard)
#pragma config(Servo,  srvo_S3_C2_6,    servo3_2_6,           tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "../includes/read_write.c"
#include "../JoystickDriver.c"
#include "../../library/drive_modes/simple_swerve_4m.c"
#include "../includes/manipulators.c"

task main()
{
	RegisterMotors(
	motorFL,
	motorFR,
	motorBL,
	motorBR,
	motorSweep,
	motorFan1,
	motorFan2
	);
	RegisterServos(
	servoFL,
	servoFR,
	servoBL,
	servoBR,
	servoGrabber,
	servoSweepArm,
	servoTubeWinch,
	servoTubeLift,
	servoTubeSlide,
	servoLoader,
	servoSweep1,
	servoSweep2,
	);

	float Kp = 0.009;
	float Ki = 0.008;
	float Kd = 0.005;
	float errorPrevSum = 0;
	float errorPrev = 0;
	float error;
	float ang = 0.0;
	float newAng = 0.0;
	float n = 0.0;
	float angPrev = 0.0;
	float newAngPrev = 0.0;
	float servoSpeed = 0.0;

	waitForStart();
	StartTask(manipulators);
	float joyDistance;
	float joyAngle;
	int joyX;
	int joyY;
	int joyZ;

	while(true)
	{
		joyX = joystick.joy1_x2;
		joyY = joystick.joy1_y2;
		joyZ = joystick.joy1_x1;
		joyDistance = sqrt( pow(joyX, 2) + pow( joyY, 2) );
		joyAngle = -57.3 * atan2(joyY, joyX);

		angPrev = ang;
		newAngPrev = newAng;
		if (JoystickToRotRate(joyZ) > 0)
		{
			newAng = -45.0 + n;
		}
		else if (JoystickToMagnitude(joyDistance) > 0)
		{
			ang = joyAngle;

			/*if (abs(ang) > 90)
			{
			if (sgn(ang * angPrev) == -1)
			{
			n = n + -1 * sgn(ang);
			}
			}
			if (n > 3)
			{
			n = 4.0;
			}
			else if (n < -3)
			{
			n = -3.0;
			}*/
			if (abs(ang - angPrev) > 180)
			{
				n = n + -360 * sgn(ang-angPrev);
			}

			else if (abs(ang - angPrev) > 90)
			{
				n = n + -180 * sgn(ang-angPrev);
			}
			newAng = ang + n - 90;
			/*if (abs(newAng - angPrev) > 90)
			{
				n = n + -180 * sgn(ang-angPrev);
			}
			newAng = ang + n - 90;*/
		}
		error = newAng + GetCRServoPosition(FRONT_LEFT);
		servoSpeed = ( Kp * error ) + ( Ki * errorPrevSum ) + ( Kd * (error - errorPrev) );
		servo[Assembly[FRONT_LEFT].driveServo] = 127 * ( -1 * servoSpeed + 1);

		errorPrev = error;
		errorPrevSum = errorPrevSum + errorPrev * 0.005;
		wait1Msec(100);

	}
}
