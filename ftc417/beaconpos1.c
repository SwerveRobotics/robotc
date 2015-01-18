#ifndef BEACONPOS1_C
#define BEACONPOS1_C

/* Code Review by Darrell
 - User of magic numbers needs fixed.
 - Direct assignment of speeds should be replaced by function calls
 - File should be using our library code
 - File name does not meet minimal style requirements
 - Encoder should be using our library code
*/

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
