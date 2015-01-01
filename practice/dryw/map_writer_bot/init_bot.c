#ifndef INIT_BOT
#define INIT_BOT

#include "../../../Library/sensors/sonar.c"

const int DEFAULT_SPEED = 50;

void InitBot()
{
	RegisterSonar(sonarL, 1);
	RegisterSonar(sonarR, 2);
	RegisterDriveMotors(driveMtrL, drivemtrR);
	RegisterEncoderMotor(driveMtrL);
	RegisterGyroSensor(gyroSensor);
}

#endif
