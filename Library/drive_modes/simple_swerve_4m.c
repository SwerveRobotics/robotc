#ifndef SWERVE_4M_C
#define SWERVE_4M_C

#include "../math/vector_math_2d.h"
#include "../motors/encoders.h"
#include "../motors/servos.c"
#include "../motors/motors.c"

const int MOTOR_POWER_PER_CMPS = 0.82;

bool driverRelativeMode = false; //if true, the robot will be relative to the field and driver. if false, it will drive like a car

typedef enumWord
{
	FRONT_LEFT = 0,
	FRONT_RIGHT,
	BACK_LEFT,
	BACK_RIGHT,
}CornerEnum;


//swerve module structure for storing all values specific to any given drive assembly
typedef struct
{
	float servoPosition;     	//in degrees (0 - 360)
	float servoSpeed;         //in magnitude (-1 - 1)
	float motorPower;         //in motor power units (-100 - 100)
	float currentPosition;
	int reverseMotorPower;

	//hardware names
	tMotor pMotor;
	TServoIndex pServo;
	tSensors pSensorZero;
	tMotor pEncoder;
}
DriveAssemblyState;

DriveAssemblyState Drive[4];

void RegisterDriveHardware(
tMotor mFL, tMotor mFR,
tMotor mBL, tMotor mBR,
TServoIndex sFL, TServoIndex sFR,
TServoIndex sBL, TServoIndex sBR
)
{
	Drive[FRONT_LEFT].pMotor = mFL;
	Drive[FRONT_LEFT].pServo = sFL;

	Drive[FRONT_RIGHT].pMotor = mFR;
	Drive[FRONT_RIGHT].pServo = sFR;

	Drive[BACK_LEFT].pMotor = mBL;
	Drive[BACK_LEFT].pServo = sBL;

	Drive[BACK_RIGHT].pMotor = mBR;
	Drive[BACK_RIGHT].pServo = sBR;

}

void initializeDrive()
{
	for (int p = 0; p < 4; p++)
	{
		Drive[p].servoPosition = 0;
		Drive[p].servoSpeed = 0;
		Drive[p].motorPower = 0;
		Drive[p].reverseMotorPower = 1;
	}
}

float SERVO_GEAR_RATIO = 0.5;

float GetDrivePosition(CornerEnum corner)
{
	float tick = GetEncoderValue(Drive[corner].pMotor);
	return (tick * ENC_TO_DEG * SERVO_GEAR_RATIO);
}


//call every main task cycle
void WriteToDrive()
{
	for (int p = 0; p < 4; p++)
	{
		SetServoSpeed(Drive[p].pServo, Drive[p].servoSpeed);
		SetMotorPower(Drive[p].pMotor, Drive[p].motorPower);
		Drive[p].currentPosition = GetDrivePosition(p);
	}
}

void SetDriveMotors(float cmps)
{
	Drive[FRONT_LEFT].motorPower  =      cmps * MOTOR_POWER_PER_CMPS;
	Drive[FRONT_RIGHT].motorPower = -1 * cmps * MOTOR_POWER_PER_CMPS;
	Drive[BACK_LEFT].motorPower   =      cmps * MOTOR_POWER_PER_CMPS;
	Drive[BACK_RIGHT].motorPower  = -1 * cmps * MOTOR_POWER_PER_CMPS;
}

void SetDriveServos(float angle)
{
	Drive[FRONT_LEFT].servoPosition = angle;
	Drive[FRONT_RIGHT].servoPosition = angle;
	Drive[BACK_LEFT].servoPosition = angle;
	Drive[BACK_RIGHT].servoPosition = angle;
}

void SetDrive(tVector velocity)
{
	SetDriveServos(velocity.direction);
	SetDriveMotors(velocity.magnitude);
}

void SetServosRotateMode()
{
	Drive[FRONT_LEFT].servoPosition = 45;
	Drive[FRONT_RIGHT].servoPosition = 135;
	Drive[BACK_LEFT].servoPosition = 225;
	Drive[BACK_RIGHT].servoPosition = 315;
}

#endif
