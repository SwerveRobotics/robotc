#ifndef MAP_DESIGNER
#define MAP_DESIGNER

task MapRoom()
{

	float botLastXCoordinate = 0.0;
	float botLastYCoordinate = 0.0;
	float botCurrentXCoordinate = 0.0;
	float botCurrentYCoordinate = 0.0;
	int wallXCoordinate = 0;
	int wallYCoordinate = 0;
	int xCoordinateDisplayOffset = 50;
	int yCoordinateDisplayOffset = 40;

	startGyro();
	resetGyro();
	eraseDisplay();

	while(true)
	{
		//Robot position
		botCurrentXCoordinate = botLastXCoordinate + EncoderDistance(ReadEncoderValue()) * sinDegrees(readGyro());
		botCurrentYCoordinate = botLastYCoordinate + EncoderDistance(ReadEncoderValue()) * cosDegrees(readGyro());

		//Wall mapping
		wallXCoordinate = botCurrentXCoordinate + ReadSonar(2) * CENTIMETERS_TO_INCHES * cosDegrees(readGyro());
		wallYCoordinate = botCurrentYCoordinate + ReadSonar(2) * CENTIMETERS_TO_INCHES * sinDegrees(readGyro());

		nxtSetPixel(wallXCoordinate + xCoordinateDisplayOffset, wallYCoordinate + yCoordinateDisplayOffset);
		ResetEncoderValue();
		botLastXCoordinate = botCurrentXCoordinate;
		botLastYCoordinate = botCurrentYCoordinate;
		wait1Msec(20);
	}
}

#endif
