#ifndef BEACONPOS1_C
#define BEACONPOS1_C

task BeaconPos1()
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
