#ifndef SONAR_C
#define SONAR_C

#define TANK_2M

#ifndef TANK_2M
#include "../drive_modes/tank_2m.c"
#else
#ifndef TANK_4M
#include "../drive_modes/tank_4m.c"
#else
#ifndef TANK_6M
#include "../drive_modes/tank_6m.c"
#endif
#endif
#endif

//Ratio between centimeters and inches
float const CENTIMETERS_TO_INCHES = 2.54;
tSensors SONAR_SENSOR;

void RegisterSonarSensor(tSensors sonarSensorName)
{
	SONAR_SENSOR = sonarSensorName;
}

int ReadSonar()
{
	return SensorValue[SONAR_SENSOR];
}

//Displays on the NXT screen how far away the sensor is from an object in inches
void DisplaySonarOnNXTDisplay()
{
	nxtDisplayTextLine(0, "Distance(Inches): %d", ReadSonar() / CENTIMETERS_TO_INCHES);
}

void GoToObject()
{
	//The distance we want the robot to be away from an object
	const int targetDistance = 30;

	//The margin of error for the target distance
	const int accuracyMargin = 3;

	//If the sensor is farther away from an object than the target distance, the robot moves forward
	if(ReadSonar() > targetDistance + accuracyMargin)
	{
		DriveForward(power);
	}
	//If the sensor is closer to an object than the target distance, the robot moves backward
	else if(ReadSonar() < targetDistance - accuracyMargin)
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
