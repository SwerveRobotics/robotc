#ifndef SONAR_C
#define SONAR_C

#include "../drive_modes/drive_modes.h"

//Ratio between centimeters and inches
const float CENTIMETERS_TO_INCHES = 2.54;

typedef enum
{
	SonarOne,
	SonarTwo,
	SonarThree,
	SonarFour
}SonarEnum;
const int SONAR_COUNT = 4;
tSensors SONAR[SONAR_COUNT];

void RegisterSonar(tSensors SonarName, SonarEnum sonarNum = 0)
{
	switch(sonarNum)
	{
		case SonarOne:
			SONAR[SonarOne] = SonarName;
			break;
		case SonarTwo:
			SONAR[SonarTwo] = SonarName;
			break;
		case SonarThree:
			SONAR[SonarThree] = SonarName;
			break;
		case SonarFour:
			SONAR[SonarFour] = SonarName;
			break;
	}
}

int ReadSonar(SonarEnum sonarNum = 0)
{
	return SensorValue[SONAR[sonarNum]];
}

//Displays on the NXT screen how far away the sensor is from an object in inches
void DisplaySonarOnNXTDisplay()
{
	nxtDisplayTextLine(0, "Distance(Inches): %d", ReadSonar() / CENTIMETERS_TO_INCHES);
}

void FollowRightWall(int distanceFromWall, int power, int sonarNum)
{
	while(true)
	{
	 	DriveRightMotors(power + (ReadSonar(sonarNum) - distanceFromWall));
	 	DriveLeftMotors(power - (ReadSonar(sonarNum) - distanceFromWall));
	}
}

void FollowLeftWall(int distanceFromWall, int power, int sonarNum)
{
	while(true)
	{
	 	DriveRightMotors(power - (ReadSonar(sonarNum) - distanceFromWall));
	 	DriveLeftMotors(power + (ReadSonar(sonarNum) - distanceFromWall));
	}
}

void GoToObject(int power, int sonarNum)
{
	//The distance we want the robot to be away from an object
	const int targetDistance = 30;

	//The margin of error for the target distance
	const int accuracyMargin = 3;

	//If the sensor is farther away from an object than the target distance, the robot moves forward
	if(ReadSonar(sonarNum) > targetDistance + accuracyMargin)
	{
		DriveForward(power);
	}
	//If the sensor is closer to an object than the target distance, the robot moves backward
	else if(ReadSonar(sonarNum) < targetDistance - accuracyMargin)
	{
		DriveBackward(power);
	}
	//If the robot is within the margin of error from the target distance, the motors stop and the function tells itself to stop
	else
	{
		StopAllDriveMotors();
	}
}
#endif
