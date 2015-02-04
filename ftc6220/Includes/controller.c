#ifndef CONTROLLER_C
#define CONTROLLER_C


//joystickdriver.h causes compiling errors when included?
//#include "../../Library/controllers/joystickdriver.h"

#include "joystickdriver.c"

//this is used by the FIR filter, but is now maybe redundant
typedef enumWord
{
	JOY_X = 0,
	JOY_Y,
	JOY_Z
}AxisEnum;

//enum  to identify the buttons on the controller
typedef enumWord
{
	X_BTN = 0,
	A_BTN,
	B_BTN,
	Y_BTN,
	LEFT_BUMPER,
	RIGHT_BUMPER,
	LEFT_TRIGGER,
	RIGHT_TRIGGER,
	BACK,
	START,
	LEFT_STICK,
	RIGHT_STICK
}ButtonEnum;

typedef enumWord
{
	UP = 0,
	UP_LEFT,
	LEFT,
	DOWN_LEFT,
	DOWN,
	DOWN_RIGHT,
	RIGHT,
	UP_RIGHT,
}HatEnum;

typedef struct
{
	int button;
	bool pressed;
}tButton;

typedef struct
{
	int button;
	bool pressed;
}tHat;
//axis that controls the robot's movement relative to the robot in the X direction (right/left)
int X_TRANS_AXIS;

//axis that controls the robot's movement relative to the robot in the Y direction (forward/backward)
int Y_TRANS_AXIS;

//axis that controls the robot's rotation (CW / CCW)
int ROT_AXIS;
//button that runs the sweeper motor while held
tButton SWEEPER_BTN;

//button that toggles the sweeper arm between up and down position
tButton SWEEPER_ARM_BTN;

//button that grabs a goal when pressed
tButton GOAL_GRAB_BTN;

//button that releases a goal when pressed
tButton GOAL_RELEASE_BTN;

//button that rotates the bot CW about the goal while held
tButton RADIAL_DRIVE_CW_BTN;

//button that rotates  the bot CCW about the goal while held
tButton RADIAL_DRIVE_CCW_BTN;

//button that slows the rotation and movement of the robot while held
tButton SLOW_MODE_BTN;

//button that flips the tube loader when pressed
tHat TUBE_LOAD_BTN;

//button that extends the tube to the next position up when pressed
tHat TUBE_RAISE_BTN;

//button that extebds the tube to the next position down when pressed
tHat TUBE_LOWER_BTN;

//button that toggles the fan when pressed
tButton FAN_BTN;

//button that unwinds and zeros the drive assemblies
tButton UNWIND_DRIVE_BTN;

//call every drive task cycle; updates the axis
void UpdateAxis()
{
	getJoystickSettings(joystick);
	X_TRANS_AXIS = joystick.joy1_x2;
	Y_TRANS_AXIS = joystick.joy1_y2;
	ROT_AXIS     = joystick.joy1_x1;
}

bool PressedOnJoy1(tButton btn)
{
	return (joystick.joy1_Buttons == btn.button);
}

bool PressedOnJoy2(tButton btn)
{
	return (joystick.joy2_Buttons == btn.button);
}

bool RisingEdgeJoy1(tButton btn)
{
	bool stateChanged = false;
	if (btn.pressed != (bool)(joystick.joy1_Buttons == btn.button))
	{
		btn.pressed = !btn.pressed;
		stateChanged = true;
	}
	if (stateChanged)
	{
		return btn.pressed;
	}
	else
	{
		return false;
	}
}


bool RisingEdgeJoy2(tButton btn)
{
	bool stateChanged = false;
	if (btn.pressed != (bool)(joystick.joy2_Buttons == btn.button))
	{
		btn.pressed = !btn.pressed;
		stateChanged = true;
	}
	if (stateChanged)
	{
		return btn.pressed;
	}
	else
	{
		return false;
	}
}


bool RisingEdgeHat2(tHat btn)
{
	bool stateChanged = false;
	if (btn.pressed != (bool)(joystick.joy2_TopHat == btn.button))
	{
		btn.pressed = !btn.pressed;
		stateChanged = true;
	}
	if (stateChanged)
	{
		return btn.pressed;
	}
	else
	{
		return false;
	}
}

void RegisterButtons(
ButtonEnum sweeper, ButtonEnum sweeperArm,
ButtonEnum goalGrab, ButtonEnum goalRelease,
ButtonEnum radialCW, ButtonEnum radialCCW, ButtonEnum slowMode,
ButtonEnum fan
)
{
	SWEEPER_BTN.button            = sweeper;
	SWEEPER_ARM_BTN.button        = sweeperArm;

	GOAL_GRAB_BTN.button          = goalGrab;
	GOAL_RELEASE_BTN.button       = goalRelease;

	RADIAL_DRIVE_CCW_BTN.button   = radialCCW;
	RADIAL_DRIVE_CW_BTN.button    = radialCW;
	SLOW_MODE_BTN.button          = slowMode;

	FAN_BTN.button                = fan;
}

void RegisterHat(
HatEnum tubeLoad, HatEnum tubeLower, HatEnum tubeRaise,
HatEnum unwind
)
{
	TUBE_LOAD_BTN.button    = tubeLoad;
	TUBE_LOWER_BTN.button   = tubeLower;
	TUBE_RAISE_BTN.button   = tubeRaise;
	UNWIND_DRIVE_BTN.button = unwind;
}


#endif
