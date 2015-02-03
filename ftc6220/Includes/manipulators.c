#ifndef MANIPULATORS_C
#define MANIPULATORS_C

#include "../../Library/motors/servos.c"
#include "../../Library/motors/motors.c"

// BEGIN FAN //

typedef struct
{
	tMotor MOTOR_1;
	tMotor MOTOR_2;
	bool running;
}tFan;

tFan FAN;

task RunFan()
{
	for (int p = MIN_MOTOR_POWER ; p < MAX_MOTOR_POWER; p++)
	{
		SetMotorPower(FAN.MOTOR_1,      p);
		SetMotorPower(FAN.MOTOR_2, -1 * p);
		wait10Msec( 500 - (MAX_MOTOR_POWER - MIN_MOTOR_POWER) );
	}
	StopTask(RunFan);
}

void StopFan()
{
	SetMotorPower(FAN.MOTOR_1, 0);
	SetMotorPower(FAN.MOTOR_2, 0);
}

void ToggleFan()
{
	if (!FAN.running)
	{
		StartTask(RunFan);
	}
	else
	{
		StopFan();
	}
	FAN.running = !FAN.running;
}

// END FAN //


// BEGIN GOAL GRABBER //

int GRAB_GOAL    = 50;
int RELEASE_GOAL =  8;

typedef struct
{
	TServoIndex SERVO;//this name may need to change based on if robotC confuses it with procedure "servo[]"
	bool grabbed;
}tGrabber;

tGrabber GRABBER;

void SetGoalGrabber(int position)
{
	SetServoPosition(GRABBER.SERVO, position);
}

void GrabGoal()
{
	SetGoalGrabber(GRAB_GOAL);
}

void ReleaseGoal()
{
	SetGoalGrabber(RELEASE_GOAL);
}

void ToggleGoalGrabber()
{
	if (!GRABBER.grabbed)
	{
		GrabGoal();
	}
	else
	{
		ReleaseGoal();
	}
	GRABBER.grabbed = !GRABBER.grabbed;
}

// END GOAL GRABBER //


// BEGIN SWEEPER //

int ARM_UP   = 255;
int ARM_DOWN = 127;

typedef struct
{
	tMotor MOTOR;//this name may need to change based on if robotC confuses it with procedure "motor[]"
	TServoIndex SERVO_1;
	TServoIndex SERVO_2;
	TServoIndex ARM_SERVO;
	bool running;
	bool raised;
}tSweeper;

tSweeper SWEEPER;


// BEGIN SWEEPER ARM //
void SetSweeperArm(int position)
{
	SetServoPosition(SWEEPER.ARM_SERVO, position);
}

void LowerSweeperArm()
{
	SetSweeperArm(ARM_DOWN);
}

void RaiseSweeperArm()
{
	SetSweeperArm(ARM_UP);
}

void ToggleSweeperArm()
{
	if(!SWEEPER.raised)
	{
		RaiseSweeperArm();
	}
	else
	{
		LowerSweeperArm();
	}
	SWEEPER.raised = !SWEEPER.raised;
}

//END SWEEPER ARM //

void RunSweeperMotor()
{
	SetMotorPower(SWEEPER.MOTOR, -1 * MAX_MOTOR_POWER);
}

void StopSweeperMotor()
{
	SetMotorPower(SWEEPER.MOTOR, 0);
}

void SetSweeperServos(float speed)
{
	SetServoSpeed(SWEEPER.SERVO_1, speed, CCW);
	SetServoSpeed(SWEEPER.SERVO_2, speed, CCW);
}

void RunSweeperServos()
{
	SetSweeperServos(1.0);
}

void StopSweeperServos()
{
	SetSweeperServos(0);
}

void ToggleSweeperServos()
{
	if (!SWEEPER.running)
	{
		RunSweeperServos();
	}
	else
	{
		StopSweeperServos();
	}
	SWEEPER.running = !SWEEPER.running;
}


// END SWEEPER //


// BEGIN TUBE //

const int RETRACTED = 184;
const int MEDIUM_GOAL_HEIGHT = RETRACTED;
const int HIGH_GOAL_HEIGHT = 133;
const int EXTENDED = 54;
const int CENTER_GOAL_HEIGHT = EXTENDED;

const int LOAD_POSITION_1 =  17;
const int LOAD_POSITION_2 = 249;

typedef struct
{
	TServoIndex SLIDE_SERVO;
	TServoIndex WINCH_SERVO;
	TServoIndex LOAD_SERVO;
	tSensors TOUCH_SENSOR;
	int position;
	bool loader;
}tTube;

tTube TUBE;

bool tubeRaised()
{
	bool state;
	if (SensorValue(TUBE.TOUCH_SENSOR) == 1023)
	{
		state = false;
	}
	else
	{
		state = true;
	}
	return state;
}

void SlideTubeRight()
{
	SetServoSpeed(TUBE.SLIDE_SERVO, 0.2, CCW);
}

void SlideTubeLeft()
{
	SetServoSpeed(TUBE.SLIDE_SERVO, 0.2, CW);
}

void StopSlide()
{
	SetServoSpeed(TUBE.SLIDE_SERVO, 0.0);
}

void SetTubeHeight(int height)
{
	SetServoPosition(TUBE.WINCH_SERVO, height);
}

void ExtendTube()
{
	SetTubeHeight(EXTENDED);
}

void RetractTube()
{
	SetTubeHeight(RETRACTED);
}

//raise the tube to be vertical and slide to the loader
task LiftTube()
{
	while(!tubeRaised())//drag the tube to the loader until it is in position
	{
		SlideTubeRight();
	}
	StopSlide();
	ExtendTube();//flip up the curvy thing by extending the tube by extending to top position
	wait10Msec(500);
	StopTask(LiftTube);
}

void ExtendTubeToPosition(int position)//alternate tube position setting. takes either 0, 1, or 2 as the three positions
{
	if (position == 0)
	{
		SetTubeHeight(MEDIUM_GOAL_HEIGHT);
	}
	else if (position == 1)
	{
		SetTubeHeight(HIGH_GOAL_HEIGHT);
	}
	else if (position == 2)
	{
		SetTubeHeight(CENTER_GOAL_HEIGHT);
	}
	TUBE.position = position;
}

void LoadPosition_1()
{
	SetServoPosition(TUBE.LOAD_SERVO, LOAD_POSITION_1);
}

void LoadPosition_2()
{
	SetServoPosition(TUBE.LOAD_SERVO, LOAD_POSITION_2);
}

void LoadTube()
{
	if (!TUBE.loader)
	{
		LoadPosition_1();
	}
	else
	{
		LoadPosition_2();
	}
	TUBE.loader = !TUBE.loader;
}
// END TUBE //

#endif
