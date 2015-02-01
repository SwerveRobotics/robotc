#ifndef MANIPULATORS.C
#define MANIPULATORS.C

#include "read_write.c"
#include "JoystickDriver.c"


//either enable or disable the goal grabber by raising and lowering the "hook" servo
void EnableGoalGrabber(bool state)
{
	if (state == true)
	{
		SetServo(GRABBER_SERVO, 50);
	}
	else
	{
		SetServo(GRABBER_SERVO, 8);
	}
}


//raise (disable) or lower (enable) the sweeper mechanism
void EnableSweeper(bool state)
{
	if (state == true)
	{
		SetServo(Sweeper.armServo, 255);
	}
	else
	{
		SetServo(Sweeper.armServo, 255);
	}
}

//begin or stop sweeping up balls
void RunSweeper(bool state)
{
	if (state == true)
	{
		motor[Sweeper.motor1] = -128;
		SetServo(Sweeper.servo1, 255);
		SetServo(Sweeper.servo2, 255);
	}
	else
	{
		motor[Sweeper.motor1] = 0;
		SetServo(Sweeper.servo1, 127);
		SetServo(Sweeper.servo2, 127);
	}
}

//activate both fan motors to run the fan
void RunFan(bool state)
{

	if (state == true)
	{
		for (int p = 20; p < 127; p++)
		{
			motor[FAN_MOTOR_1] = -1 * p;
			motor[FAN_MOTOR_2] = -1 * p;
			wait10Msec(15);
		}
	}
	else
	{
		for (int p = 0; p < 128; p++)
		{
			SetMotorPower(FAN_MOTOR_1, -128 + p);
			SetMotorPower(FAN_MOTOR_2, -128 + p);
			wait10Msec(5);
		}
	}
}

//rotate the tube loading mechanism. "continous" loading would mean that this fucntion is alternately called with true and false
void LoadTube(bool state)
{
	if (state == true)
	{
		SetServo(Tube.loaderServo, 17);
	}
	else
	{
		SetServo(Tube.loaderServo, 249);
	}
}

void SetTubeHeight(float h)
{
	int n = h;//needs to be recongfigured for cm
	SetServo(Tube.winchServo, n);
}

//needs changing to incorporate the exnding tube. also wrong servo.
void LiftTube()
{
	//verticalize tube
	wait10Msec(100);
	SetServo(Tube.liftServo, 0);
	wait10Msec(100);
	SetServo(Tube.liftServo, 80);
	while(SensorValue(Tube.touchSensor) == 1023)//drag the tube to the loader
	{
		SetServo(Tube.slideServo, 0);
		wait10Msec(10);
	}
	SetServo(Tube.slideServo, 127);
	SetTubeHeight(HIGH_GOAL_HEIGHT);
	wait10Msec(300);
}

#endif
