#ifndef INIT_AUTO_C
#define INIT_AUTO_C

void InitializeAuto()
{
	ASSUME_CONTROLLER_INPUT = false;
	RegisterDriveMotors(mtrFL, mtrBL, mtrFR, mtrBR);
	RegisterEncoderMotor(mtrFR);
	RegisterIRSeeker(IRSensor);
	RegisterGyroSensor(gyroSensor);
	WHEEL_DIAMETER = 4;
	GEAR_RATIO = 1.5;
	ReleaseGoal();
	servo[irRotator] = 255;

	LEFT_TURN_GYRO_OVERRUN = 5;
	RIGHT_TURN_GYRO_OVERRUN = 5;
}
#endif
