#ifndef MANIPULATORS.C
#define MANIPULATORS.C

#include "read_write.c"
#include "JoystickDriver.c"

const tSensors tubeTouchSensor = (tSensors) S4;

const int GRAB_GOAL = 50;
const int RELEASE_GOAL = 0;

bool GRABBER_GRABBED = true;
void SetGrabberServo(int position)
{
	SetServo(GRABBER_SERVO, position);
}
int GrabberTarget()
{
	return (GRABBER_GRABBED ? RELEASE_GOAL : GRAB_GOAL);
}
void ToggleGoalGrabber()
{
	SetGrabberServo(GrabberTarget());
	GRABBER_GRABBED = !GRABBER_GRABBED;
}

//either enable or disable the goal grabber by raising and lowering the "hook" servo
void EnableGoalGrabber(bool state)
{
	if (state == true)
	{
		SetServo(GRABBER_SERVO, GRAB_GOAL);
	}
	else
	{
		SetServo(GRABBER_SERVO, RELEASE_GOAL);
	}
}


//raise (disable) or lower (enable) the sweeper mechanism
void EnableSweeper(bool state)
{
	if (state == true)
	{
		SetServo(SWEEPER_SERVO, 127);
	}
	else
	{
		SetServo(SWEEPER_SERVO, 18);
	}
}

//begin or stop sweeping up balls
void RunSweeper(bool state)
{
	if (state == true)
	{
		setMotorPower(SWEEPER_MOTOR, 128);
	}
	else
	{
		setMotorPower(SWEEPER_MOTOR, 0);
	}
}

//activate both fan motors to run the fan
void RunFan(bool state)
{
	if (state == true)
	{
		setMotorPower(FAN_MOTOR_1, 128);
		setMotorPower(FAN_MOTOR_2, 128);
	}
	else
	{
		setMotorPower(FAN_MOTOR_1, 0);
		setMotorPower(FAN_MOTOR_2, 0);
	}
}

//rotate the tube loading mechanism. "continous" loading would mean that this fucntion is alternately called with true and false
void LoadTube(bool state)
{
	if (state == true)
	{
		SetServo(TUBE_SERVO, 0);
	}
	else
	{
		SetServo(TUBE_SERVO, 255);
	}
}

//needs changing to incorporate the exnding tube. also wrong servo.
void liftTube()
{
	while(SensorValue(tubeTouchSensor) == 0)
	{
		SetServo(TUBE_SERVO, 255);
	}
	SetServo(TUBE_SERVO, 127);
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
		if ((joystick.joy1_Buttons == 1) && grabberReady)
		{
			grabberReady = false; // event disabler
			ToggleGoalGrabber();
		}
		else if (joystick.joy1_Buttons != 1)
		{
			// wait for button to be released
			grabberReady = true;
		}
		///   !!!   end goal grabber   !!!   ///



		///   !!!   begin sweeper   !!!   ///
		if (joystick.joy1_Buttons == 2 && sweeperDown)
		{
			RunSweeper(true);
		}
		else
		{
			RunSweeper(false);
		}

		if ((joystick.joy1_Buttons == 3) && sweeperReady)
		{
			sweeperReady = false;
			sweeperDown = !sweeperDown;
			EnableSweeper(!sweeperDown);
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
