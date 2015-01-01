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

	startGyro();
	resetGyro();

	while(true)
	{
		//Robot position
		botCurrentXCoordinate = botLastXCoordinate + ReadEncoderValue() * cos(readGyro());
		botCurrentYCoordinate = botLastYCoordinate + ReadEncoderValue() * sin(readGyro());

		//Wall mapping
		wallXCoordinate = botCurrentXCoordinate + ReadSonar(2) * cos(readGyro());
		wallYCoordinate = botCurrentYCoordinate + ReadSonar(2) * sin(readGyro());

		nxtSetPixel(wallXCoordinate, wallYCoordinate);
		ResetEncoderValue();
		botLastXCoordinate = botCurrentXCoordinate;
		botLastYCoordinate = botCurrentYCoordinate;
		wait1Msec(25);
	}
}

#endif
