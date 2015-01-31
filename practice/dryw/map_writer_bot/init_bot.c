#ifndef INIT_BOT
#define INIT_BOT

const int DEFAULT_POWER = 20;

void InitBot()
{
	RegisterSonar(sonarL, 1);
	RegisterSonar(sonarR, 2);
	RegisterDriveMotors(driveMtrL, driveMtrR);
	RegisterEncoderMotor(driveMtrL);
	RegisterGyroSensor(gyroSensor);
}

#endif
