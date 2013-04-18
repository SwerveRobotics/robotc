#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Left,          tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorC,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     ForkLift,      tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//All comments to most of this code is in TeleOpJarrod.c
#include "JoystickDriver.c"


int deadZone = 15;
long Peg1 = 2196;//peg 1 encoder value
long Peg2 = 5203;//peg 2 encoder value
long Peg3 = 8584;//peg 3 encoder value
long Zero = 0;
long goPosition;

long tooLong = 150;  // millisecond threshod for time to pass
long sigMove = 1000; // How many encoder ticks is a 'significant' movement

//variables used for stall code need to be initialized
bool powerHasBeenOn[] = {false, false, false}; // True after significant power has been applied
long timeLastSigMove[] = {0, 0, 0}; // Time last significant move occurred
long encLastSigMove[] = {0, 0, 0}; // Encoder reading at last significant move

int StallCode(tMotor motorSentTo, int wantedPower)
{
	int motorIndex;  //index value for the arrays we are storing values in.
	switch(motorSentTo) //which motor power is being sent to
	{
		case Left: // This is the name of one of the motors as referenced in the configuraiton.
			motorIndex = 0;
			break;
		case Right:
			motorIndex = 1;
			break;
		case ForkLift:
			motorIndex = 2;
			break;
		default:
			break;
	}

	if (abs(wantedPower) < deadZone)  // Power below threshold, mark as no power.
		{
			powerHasBeenOn[motorIndex] = false;

			return wantedPower;
		}

	if (powerHasBeenOn[motorIndex] == false)  // Power transitioned above threshold, start monitoring power.	Allow whatever power desired this time.
		{
			powerHasBeenOn[motorIndex] = true;
			timeLastSigMove[motorIndex]	 = time1[T1];
			encLastSigMove[motorIndex] = nMotorEncoder[motorSentTo];

			return wantedPower;
		}

	if ( ( abs(encLastSigMove[motorIndex]) - nMotorEncoder[motorSentTo]) > sigMove)  // Moved far enough to be considered significant, mark
		{
			timeLastSigMove[motorIndex]	= time1[T1];
			encLastSigMove[motorIndex] = nMotorEncoder[motorSentTo];

			return wantedPower;
		}

	if ( (time1[T1] - timeLastSigMove[motorIndex]) > tooLong )  // Time since last significant move too long, stalled
		{
			return 0;
		}

	return wantedPower;	// Haven�t moved far enough yet to be significant but haven�t timed out yet
}


task Joystick2()
{
	while(true)
	{
		getJoystickSettings(joystick);
		//D-pad fork-lift control
		if(joystick.joy2_TopHat ==0)
		{
			motor[ForkLift] = StallCode(ForkLift, 75);
			//motor[ForkLift] = 100;
		}
		else if(joystick.joy2_TopHat ==4)
		{
			motor[ForkLift] = StallCode(ForkLift, -75);
			//motor[ForkLift] = -100;
		}
		else
		{
			motor[ForkLift] = StallCode(ForkLift, 0);
			//motor[ForkLift] = 0;
		}
		//going to peg 1
		if(joystick.joy2_Buttons == 2)
		{
			goPosition = (Peg1 - nMotorEncoder[ForkLift]);
			if (goPosition > 0) // go up
			{
				while(nMotorEncoder[ForkLift] < Peg1) // to position
				{
					motor[ForkLift] = 75;  // speed
				}
				motor[ForkLift] = 0; // stop
			}
			else if (goPosition < 0) // go down
			{
				while(nMotorEncoder[ForkLift] > Peg1) // to position
				{
					motor[ForkLift] = -75; // speed
				}
				motor[ForkLift] = 0; // stop
			}
		}
		//going to peg 2
		else if(joystick.joy2_Buttons == 1)
		{
			goPosition = (Peg2 - nMotorEncoder[ForkLift]);
			if (goPosition > 0) // go up
			{
				while(nMotorEncoder[ForkLift] < Peg2) // to position
				{
					motor[ForkLift] = 75;  // speed
				}
				motor[ForkLift] = 0; // stop
			}
			else if (goPosition < 0) // go down
			{
				while(nMotorEncoder[ForkLift] > Peg2) // to position
				{
					motor[ForkLift] = -75; // speed
				}
				motor[ForkLift] = 0; // stop
			}
		}
		//going to peg 3
		else if(joystick.joy2_Buttons == 4)
		{
			goPosition = (Peg3 - nMotorEncoder[ForkLift]);
			if (goPosition > 0) // go up
			{
				while(nMotorEncoder[ForkLift] < Peg3) // to position
				{
					motor[ForkLift] = 75;  // speed
				}
				motor[ForkLift] = 0; // stop
			}
			else if (goPosition < 0) // go down
			{
				while(nMotorEncoder[ForkLift] > Peg3) // to position
				{
					motor[ForkLift] = -75; // speed
				}
				motor[ForkLift] = 0; // stop
			}
		}

		else if(joystick.joy2_Buttons == 3)
		{
			goPosition = (Zero - nMotorEncoder[ForkLift]);
			if (goPosition > 0) // go up
			{
				while(nMotorEncoder[ForkLift] > Zero) // to position
				{
					motor[ForkLift] = -75;  // speed
				}
				motor[ForkLift] = 0; // stop
			}
			else if (goPosition < 0) // go down
			{
				while(nMotorEncoder[ForkLift] < Zero) // to position
				{
					motor[ForkLift] = 75; // speed
				}
				motor[ForkLift] = 0; // stop
			}
		}
	}
}


task main()
{
	waitForStart();
	StartTask(Joystick2);
	ClearTimer(T1);
	nMotorEncoder[ForkLift] = 0;
	//slow mode
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(7) == 1)
		{
			if(abs(joystick.joy1_y1) > deadZone)
			{
				motor[Left] = StallCode(Left, (joystick.joy1_y1) / 5);
			}
			else
			{
				motor[Left] = StallCode(Left, 0);
			}

			if(abs(joystick.joy1_y2) > deadZone)
			{
				motor[Right] = StallCode(Right, (joystick.joy1_y2) / 5);
			}
			else
			{
				motor[Right] = StallCode(Right, 0);
			}
		}
		else
		{
			if(abs(joystick.joy1_y1) > deadZone)
			{
				motor[Left] = StallCode(Left, (joystick.joy1_y1));
			}
			else
			{
				motor[Left] = StallCode(Left, 0);
			}

			if(abs(joystick.joy1_y2) > deadZone)
			{
				motor[Right] = StallCode(Right, (joystick.joy1_y2));
			}
			else
			{
				motor[Right] = StallCode(Right, 0);
			}
		}
	}
}
