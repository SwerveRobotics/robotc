#ifndef BEACON_C
#define BEACON_C
//note add #define TANK_4M to any file that uses this//
#include "../../../library/drive_modes/drive_modes.h"


const int MOTOR_POWER = 60;
const int motorPower = MOTOR_POWER;

//this is for the first position of the center goal
void BeaconPos1()
{
	//move the robot forward 3-4 rotations
		while(nMotorEncoder[Left] <= 4320)
		{
			motor[Right] = motorPower;
			motor[Right2] = motorPower;
			motor[Left] = motorPower;
			motor[Left2] = motorPower;
		}
		motor[Right] = 0;
		motor[Right2] = 0;
		motor[Left] = 0;
		motor[Left2] = 0;
		nMotorEncoder[Left] = 0;

	//turn the robot by half a rotation
		while(nMotorEncoder[Left] >= -720)
		{
			motor[Right] = motorPower;
			motor[Right2] = motorPower;
			motor[Left] = -motorPower;
			motor[Left2] = -motorPower;
		}
		motor[Right] = 0;
		motor[Right2] = 0;
		motor[Left] = 0;
		motor[Left2] = 0;
		nMotorEncoder[Left] = 0;

	//move the robot forward by 2 rotations
		while(nMotorEncoder[Left] <= 2160)
		{
			motor[Right] = motorPower;
			motor[Right2] = motorPower;
			motor[Left] = motorPower;
			motor[Left2] = motorPower;
		}
		motor[Right] = 0;
		motor[Right2] = 0;
		motor[Left] = 0;
		motor[Left2] = 0;
		nMotorEncoder[Left] = 0;
}

//function for the 2nd position of the center goal
void BeaconPos2()
{
	//move the robot forward by 3.5-4.5 rotations
	while(nMotorEncoder[Left] <= 4420)
	{
		motor[Left] = motorPower;
		motor[Left2] = motorPower;
		motor[Right] = motorPower;
		motor[Right2] = motorPower;
	}
	motor[Left] = 0;
	motor[Left2] = 0;
	motor[Right] = 0;
	motor[Right2] = 0;
	nMotorEncoder[Left] = 0;

	//turn the robot by about half a rotation
	while(nMotorEncoder[Left] >= -720)
	{
		motor[Left] = -motorPower;
		motor[Left2] = -motorPower;
		motor[Right] = motorPower;
		motor[Right2] = motorPower;
	}
	motor[Left] = 0;
	motor[Left2] = 0;
	motor[Right] = 0;
	motor[Right2] = 0;
	nMotorEncoder[Left] = 0;

	//move forward by two rotations
	while(nMotorEncoder[Left] <= 2160)
	{
		motor[Left] = motorPower;
		motor[Left2] = motorPower;
		motor[Right] = motorPower;
		motor[Right2] = motorPower;
	}
	motor[Left] = 0;
	motor[Left2] = 0;
	motor[Right] = 0;
	motor[Right2] = 0;
	nMotorEncoder[Left] = 0;
}

//function for the 3rd position of the center goal
void BeaconPos3()
{
	while(nMotorEncoder[Left] <= 4520)
	{
		motor[Left] = motorPower;
		motor[Left2] = motorPower;
		motor[Right] = motorPower;
		motor[Right2] = motorPower;
	}
	motor[Left] = 0;
	motor[Left2] = 0;
	motor[Right] = 0;
	motor[Right2] = 0;
	nMotorEncoder[Left] = 0;

	while(nMotorEncoder[Left] >= -720)
	{
		motor[Left] = motorPower;
		motor[Left2] = motorPower;
		motor[Right] = motorPower;
		motor[Right2] = motorPower;
	}
	motor[Left] = 0;
	motor[Left2] = 0;
	motor[Right] = 0;
	motor[Right2] = 0;
	nMotorEncoder[Left] = 0;

	while(nMotorEncoder[Left] <= 2160)
	{
		motor[Left] = motorPower;
		motor[Left2] = motorPower;
		motor[Right] = motorPower;
		motor[Right2] = motorPower;
	}
	motor[Left] = 0;
	motor[Left2] = 0;
	motor[Right] = 0;
	motor[Right2] = 0;
	nMotorEncoder[Left] = 0;
}


#endif
