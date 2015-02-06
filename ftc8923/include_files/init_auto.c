#ifndef INIT_AUTO_C
#define INIT_AUTO_C

void InitializeAuto()
{
	ASSUME_CONTROLLER_INPUT = false;
	RegisterDriveMotorPair(mtrFL, mtrFR, 0);
	RegisterDriveMotorPair(mtrBL, mtrBR, 1);
	RegisterEncoderMotor(mtrFR);
	RegisterIRSeeker((tSensors) irSensor,1);
	RegisterGyroSensor(gyroSensor);
	nMotorEncoder[mtrLifterL] = 0;
	WHEEL_DIAMETER = 4;
	GEAR_RATIO = 1.5;
	ReleaseGoal();
	LEFT_TURN_GYRO_OVERRUN = 15;
	RIGHT_TURN_GYRO_OVERRUN = 20;
}
#endif
