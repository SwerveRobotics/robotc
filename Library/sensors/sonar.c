#ifndef SONAR_C
#define SONAR_C

//Ratio between centimeters and inches
int centimetersToInches = 2.54;

//Displays on the NXT screen how far away the sensor is from an object in inches
void Sonar()
{
	nxtDisplayTextLine(0, "Distance(Inches): %d", SensorValue[sonar] / centimetersToInches);
}


void GoToObject(int move = 0)
{
	//The distance we want the robot to be away from an object
	int targetDistance = 30;

	//The margin of error for the target distance
	int accuracyMargin = 3;

	//If the function has been told perform the following code
	if(move == 1)
	{
		//If the sensor is farther away from an object than the target distance, the robot moves forward
		if(SensorValue[sonar] > targetDistance + accuracyMargin)
		{
			LeftMotorPower(50);
			RightMotorPower(50);
		}
		//If the sensor is closer to an object than the target distance, the robot moves backward
		else if(SensorValue[sonar] < targetDistance - accuracyMargin)
		{
			LeftMotorPower(-50);
			RightMotorPower(-50);
		}
		//If the robot is within the margin of error from the target distance, the motors stop and the function tells itself to stop
		else
		{
			LeftMotorPower(0);
			RightMotorPower(0);
			move = 0;
		}
	}
}
#endif
