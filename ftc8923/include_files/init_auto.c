#ifndef INIT_AUTO_C
#define INIT_AUTO_C

void InitializeAuto()
{
	ASSUME_CONTROLLER_INPUT = false;
	RegisterDriveMotors(mtrFL, mtrBL, mtrFR, mtrBR);
	RegisterEncoderMotor(mtrFR);
	RegisterIRSeeker(IRSensor,1);
	RegisterGyroSensor(gyroSensor);
	WHEEL_DIAMETER = 4;
	GEAR_RATIO = 1.5;
	ReleaseGoal();
	servo[irRotator] = 255;
	MOTOR_POWER_SHAVE = 2;
	LEFT_TURN_GYRO_OVERRUN = 15;
	RIGHT_TURN_GYRO_OVERRUN = 20;
}
#endif
