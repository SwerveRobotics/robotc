#ifndef AUTO_IR_RAMP_C
#define AUTO_IR_RAMP_C

void AutoIRBasketThenRamp()
{
	int DistanceToIr = 0;

	// Approach IR //
	DriveForwardUntilIR(9);
	DistanceToIr = nMotorEncoder[LeftMotor]; // Save Distance Driven

	// Drop Block //
	TurnLeft(50,THREE_QUARTER_IMPULSE); // approximate
	servo[Flipper] = 50;                      //drop block into basket

	// Return to Starting Position //
	TurnRight(50,THREE_QUARTER_IMPULSE);
	DriveDistanceBackwards(DistanceToIr, HALF_IMPULSE);

	// Go Around Ramp //
	TurnLeft(50, THREE_QUARTER_IMPULSE);
	DriveDistanceForward(4000, HALF_IMPULSE);

	// Drive Onto Ramp //
	TurnRight(50, THREE_QUARTER_IMPULSE);
	DriveDistanceForward(4000, THREE_QUARTER_IMPULSE);
}

#endif
