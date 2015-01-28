#ifndef TANK_CONTROLLER_OPTIONS_C
#define TANK_CONTROLLER_OPTIONS_C

int BACKWARD_BUTTON = -1; // Set to non-button so no accidental backwards driving ensues
int SLOW_MODE_BUTTON = -1;
float DRIVE_POWER_MULTIPLIER = 1;

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

void RegisterSlowModeButton(int button)
{
	SLOW_MODE_BUTTON = button;
}

void SetSlowModeMultiplier(int multiplier)
{
	DRIVE_POWER_MULTIPLIER = multiplier;
}

#endif
