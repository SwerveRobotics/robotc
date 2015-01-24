#ifndef MANIPULATORS.C
#define MANIPULATORS.C

#include "read_write.c"
#include "JoystickDriver.c"

const tSensors tubeTouchSensor = (tSensors) S4;

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
		SetServo(SWEEPER_SERVO_ARM, 127);
	}
	else
	{
		SetServo(SWEEPER_SERVO_ARM, 18);
	}
}

//begin or stop sweeping up balls
void RunSweeper(bool state)
{
	if (state == true)
	{
		SetMotorPower(SWEEPER_MOTOR, 128);
	}
	else
	{
		SetMotorPower(SWEEPER_MOTOR, 0);
	}
}

//activate both fan motors to run the fan
void RunFan(bool state)
{
	if (state == true)
	{
		SetMotorPower(FAN_MOTOR_1, 128);
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
		SetServo(LOADER_SERVO, 0);
	}
	else
	{
		SetServo(LOADER_SERVO, 255);
	}
}

//needs changing to incorporate the exnding tube. also wrong servo.
void liftTube()
{
	SetStandardServoDegree(TUBE_SERVO_LIFT, 90);// lift the tube to vertical
	wait1Msec(50);
	SetStandardServoDegree(TUBE_SERVO_LIFT, 0);
	while(SensorValue(tubeTouchSensor) == 0)//drag the tube to the loader
	{
		SetServo(TUBE_SERVO_SLIDE, 255);
	}
	SetServo(TUBE_SERVO_SLIDE, 127);
	//extend tube?
}

task manipulators()
{
	bool grabbed      = false;
	bool grabberReady = true;

	bool sweeperDown  = false;
	bool sweeperReady = true;

	bool tubeToggle   = false;
	bool tubeReady    = true;
	liftTube();
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

		/*
		///   !!!   begin tube   !!!   ///
		if ((joystick.joy1_Buttons == 4) & tubeReady == true)
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
		else if (joystick.joy1_Buttons != 4)
		{
			tubeReady = true;
		}
		///   !!!   end tube   !!!   ///
		*/

	}
}
#endif
