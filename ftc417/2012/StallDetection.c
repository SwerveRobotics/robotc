#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Left,          tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorC,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     ForkLift,      tmotorTetrix, PIDControl, encoder)

//////////////////////////////////////////////////////////////////////////////////////////
//
// As of April 2013, SWERVE Robotics had determined that a function intended to avoid
// burining out motors was not functioning as intended.
//
// The logic was difficualt to follow and the loops were never being entered.
//
// This file contains the new "I did not budge last time, I am most likely stuck" code
// intended to reduce burning out motors.
//
//////////////////////////////////////////////////////////////////////////////////////////

// int StallCode(string motorSentTo, int wantedPower);

//////////////////////////////////////////////////////////////////////////////////////////
//
// This has to be called even when the power desired is below the dead zone
// so that it can see a transition from no power to significant power.
//
// The timer T1 must be reset at the start of the program.
//////////////////////////////////////////////////////////////////////////////////////////

// Control variables used to define behavior.  These should be set in Task Main
// long now = time1[T1];
// long currentEncoder = ;
// int deadZone = 10;  // Set this in the main task
long tooLong = 150;  // millisecond threshod for time to pass
long sigMove = 1000; // How many encoder ticks is a 'significant' movement
// string motorSentTo;  // There should be some way to get this out of pragma
// int motorIndex;  // This should be able to be derived somehow

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

	if ( abs(encLastSigMove[motorIndex]) – nMotorEncoder[motorSentTo] > sigMove)  // Moved far enough to be considered significant, mark
		{
			timeLastSigMove[motorIndex]	= time1[T1];
			encLastSigMove[motorIndex] = nMotorEncoder[motorSentTo];

			return wantedPower;
		}

	if ( (time1[T1] – timeLastSigMove[motorIndex]) > tooLong )  // Time since last significant move too long, stalled
		{
			return 0;
		}

	return wantedPower;	// Haven’t moved far enough yet to be significant but haven’t timed out yet
}
