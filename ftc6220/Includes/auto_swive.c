#ifndef AUTO_SWIVE_C
#define AUTO_SWIVE_C

#include "JoystickDriver.c"
#include "controller.c"
#include "../../Library/drive_modes/simple_swerve_4m.c"
#include "../../Library/motors/motors.c"
#include "../../Library/motors/servos.c"
#include "../../Library/math/vector_math_2d.h"
#include "pid.c"

float robotDir;

task DriveTask()
{
	initializeDrive();

	//PID loop for the drive servos
	for(int p = 0; p < 4; p++)
	{
		//update previous values
		angPrev[p]       = ang[p];
		newAngPrev[p]    = newAng[p];
		errorPrev[p]     = error[p];
		errorPrevSum[p] += error[p];

		//update current values
		ang[p] = Drive[p].servoPosition;
		error[p] = ang[p] - GetDrivePosition(p);

		//calculate the servo speed with PID
		Drive[p].servoSpeed = (Kp * error[p]) + (Ki * errorPrevSum[p]) + (Kd * ( error[p] - errorPrev[p] ) );
	}

}

void RotateBot(float angle, float speed)
{
	SetServosRotateMode();
	wait10Msec(100);
	while( abs(readGyro() - angle) > 1)
	{
		//porportionality loop
		SetDriveMotors( 20 * (readGyro() - angle) );
	}
	SetDriveMotors(0);
}

void SetDriveVelocity(float speed, float direction)
{
	SetDriveMotors(speed);
	SetDriveServos(direction);
}

float GetRobotOrientation()
{
	return readGyro();
}

//specify a location relative to the robot in x, y, and a final rotation
//and it will go there
void DriveForTime(float time)
{
	SetMotorPower(Drive[FRONT_LEFT].pMotor,  80);
	SetMotorPower(Drive[FRONT_RIGHT].pMotor, -80);
	SetMotorPower(Drive[BACK_LEFT].pMotor,   80);
	SetMotorPower(Drive[BACK_RIGHT].pMotor,  -80);
	wait10Msec(100 * time);
	SetMotorPower(Drive[FRONT_LEFT].pMotor,  0);
	SetMotorPower(Drive[FRONT_RIGHT].pMotor, 0);
	SetMotorPower(Drive[BACK_LEFT].pMotor,   0);
	SetMotorPower(Drive[BACK_RIGHT].pMotor,  0);

}
#endif
