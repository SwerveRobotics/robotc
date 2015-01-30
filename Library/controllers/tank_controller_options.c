#ifndef TANK_CONTROLLER_OPTIONS_C
#define TANK_CONTROLLER_OPTIONS_C

/// @todo rename file to generic options.c
/// @todo make naming the same (reverse vs backward)

////// REVERSE MODE /////////
int BACKWARD_BUTTON = -1; // Set to non-button so no accidental backwards driving ensues

void RegisterBackwardButton(int button)
{
	BACKWARD_BUTTON = button;
}

// This function assumes the current state of the joystick as it is read is correct
bool ReverseDrive()
{
	// note that short-circuit may cause second term to not get evaluated
	// if backward button is not set
	return (BACKWARD_BUTTON >= 0 && joy1Btn(BACKWARD_BUTTON) == 1);
}

int ReverseDriveMultiplier()
{
	return (ReverseDrive() ? -1 : 1);
}


////// SLOW MODE /////////
int SLOW_MODE_BUTTON = -1;
float SLOW_MODE_DIVISOR = 1;

void RegisterSlowModeButton(int button)
{
	SLOW_MODE_BUTTON = button;
}

void SetSlowModeDivisor(int divisor)
{
	SLOW_MODE_DIVISOR = divisor;
}

bool DriveSlow()
{
	return (SLOW_MODE_BUTTON >= 0 && joy1Btn(SLOW_MODE_BUTTON) == 1);
}

int SlowModeDivisor()
{
	return (DriveSlow() ? SLOW_MODE_DIVISOR : 1);
}

#endif
