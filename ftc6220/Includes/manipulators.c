#ifndef MANIPULATORS.C
#define MANIPULATORS.C

/* Code Review by Darrell
 - *Good use of includes.*
 - Servo positions lack explanations.
 - You use a single & at one point which is not doing what you may think. Please read this file:
   http://cdn.robotc.net/pdfs/natural-language/hp_boolean_logic.pdf
 - Setting of motors and servos should be using functions like SetServoPosition(servoName, position).
*/

#include "writing.c"
#include "JoystickDriver.c"


void EnableGoalGrabber(bool state)
{
	if (state == true)
	{
		servo[GRABBER_SERVO] = 255;
	}
	else
	{
		servo[GRABBER_SERVO] = 130;
	}
}



void EnableSweeper(bool state)
{
	if (state == true)
	{
		servo[SWEEPER_SERVO] = 127;
	}
	else
	{
		servo[SWEEPER_SERVO] = 18;
	}
}



void RunSweeper(bool state)
{
	if (state == true)
	{
		motor[SWEEPER_MOTOR] = 128;
	}
	else
	{
		motor[SWEEPER_MOTOR] = 0;
	}
}



void RunFan(bool state)
{
	if (state == true)
	{
		motor[FAN_MOTOR_1] = 128;
		motor[FAN_MOTOR_2] = 128;
	}
	else
	{
		motor[FAN_MOTOR_1] = 0;
		motor[FAN_MOTOR_2] = 0;
	}
}


void LoadTube(bool state)
{
	if (state == true)
	{
		servo[TUBE_SERVO] = 0;
	}
	else
	{
		servo[TUBE_SERVO] = 255;
	}
}
task manipulators()
{
	bool grabbed      = false;
	bool grabberReady = true;

	bool sweeperDown  = false;
	bool sweeperReady = true;

	bool tubeToggle   = false;
	bool tubeReady    = true;

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
		if ((joystick.joy1_Buttons == 4) & tubeReady == true) // wrong type of AND. You need to use "&&"
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


	}
}
#endif
