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
		SetServo(GRABBER_SERVO, 0);
	}
}


//raise (disable) or lower (enable) the sweeper mechanism
void EnableSweeper(bool state)
{
	if (state == true)
	{
		SetServo(Sweeper.armServo, 127);
	}
	else
	{
		SetServo(Sweeper.armServo, 18);
	}
}

//begin or stop sweeping up balls
void RunSweeper(bool state)
{
	if (state == true)
	{
		SetMotorPower(Sweeper.motor1, -128);
		SetServo(Sweeper.servo1, 255);
		SetServo(Sweeper.servo2, 255);
	}
	else
	{
		SetMotorPower(Sweeper.motor1, 0);
		SetServo(Sweeper.servo1, 127);
		SetServo(Sweeper.servo2, 127);
	}
}

//activate both fan motors to run the fan
void RunFan(bool state)
{
	if (state == true)
	{
		SetMotorPower(FAN_MOTOR_1, -128);
		SetMotorPower(FAN_MOTOR_2, 128);
	}
	else
	{
		SetMotorPower(FAN_MOTOR_1, 0);
		SetMotorPower(FAN_MOTOR_2, 0);
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
	//verticalize tube?
	while(SensorValue(Tube.touchSensor) == 1023)//drag the tube to the loader
	{
		SetServo(Tube.slideServo, 0);
		wait10Msec(10);
	}
	SetServo(Tube.slideServo, 127);
	SetTubeHeight(HIGH_GOAL_HEIGHT);
}

task Manipulators()
{
	bool grabbed      = false;
	bool grabberReady = true;

	bool sweeperDown  = false;
	bool sweeperReady = true;

	bool tubeToggle   = false;
	bool tubeReady    = true;

	bool fanRunning   = false;
	bool fanReady     = true;
	LiftTube();
	RunFan(true);
	fanRunning = true;
	while(true)
	{
		//   !!!   begin goal grabber   !!!   //
		if ((joystick.joy1_Buttons == 1) & grabberReady == true)
		{
			grabberReady = false;
			if (grabbed == false)
			{
				grabbed = true;
				EnableGoalGrabber(true);
			}
			else
			{
				grabbed = false;
				EnableGoalGrabber(false);
			}
		}
		else if (joystick.joy1_Buttons != 1)
		{
			grabberReady = true;
		}
		///   !!!   end goal grabber   !!!   ///



		///   !!!   begin sweeper   !!!   ///
		if (joystick.joy1_Buttons == 2 & sweeperDown == true)
		{
			RunSweeper(true);
		}
		else
		{
			RunSweeper(false);
		}

		if ((joystick.joy1_Buttons == 3) & sweeperReady == true)
		{
			sweeperReady = false;
			if (sweeperDown == false)
			{
				sweeperDown = true;
				EnableSweeper(true);
			}
			else
			{
				sweeperDown = false;
				EnableSweeper(false);
			}
		}
		else if (joystick.joy1_Buttons != 3)
		{
			sweeperReady = true;
		}
		///   !!!   end sweeper   !!!   ///


		///   !!!   begin tube   !!!   ///
		if ((joystick.joy2_Buttons == 4) & tubeReady == true)
		{
			tubeReady = false;
			if (tubeToggle == false)
			{
				tubeToggle = true;
				LoadTube(true);
			}
			else
			{
				tubeToggle = false;
				LoadTube(false);
			}
		}
		else if (joystick.joy2_Buttons != 4)
		{
			tubeReady = true;
		}

		if (joystick.joy2_TopHat == 0)
		{
			SetTubeHeight(CENTER_GOAL_HEIGHT);
		}
		else if (joystick.joy2_TopHat == 6)
		{
			SetTubeHeight(HIGH_GOAL_HEIGHT);
		}
		else if (joystick.joy2_TopHat == 4)
		{
			SetTubeHeight(MEDIUM_GOAL_HEIGHT);
		}
		///   !!!   end tube   !!!   ///


		///   !!!   begin fan  !!!   ///
		if ((joystick.joy2_Buttons == 1) & fanReady == true)
		{
			fanReady = false;
			if (fanRunning == false)
			{
				fanRunning = true;
				RunFan(true);
			}
			else
			{
				fanRunning = false;
				RunFan(false);
			}
		}
		else if (joystick.joy2_Buttons != 1)
		{
			fanReady = true;
		}
		///   !!!   end fan    !!!   ///

	}
}
#endif
