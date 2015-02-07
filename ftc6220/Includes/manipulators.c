#ifndef MANIPULATORS_C
#define MANIPULATORS_C

#include "../../Library/motors/servos.c"
#include "../../Library/motors/motors.c"

// BEGIN FAN //

typedef struct
{
	tMotor pMotor_1;
	tMotor pMotor_2;
	bool running;
}tFan;

tFan FAN;

task RunFan()
{
	for (int p = MIN_MOTOR_POWER ; p < MAX_MOTOR_POWER; p++)
	{
		SetMotorPower(FAN.pMotor_1,      p);
		SetMotorPower(FAN.pMotor_2, -1 * p);
		wait10Msec( 500 - (MAX_MOTOR_POWER - MIN_MOTOR_POWER) );
	}
	StopTask(RunFan);
}

void StopFan()
{
	SetMotorPower(FAN.pMotor_1, 0);
	SetMotorPower(FAN.pMotor_2, 0);
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
	TServoIndex pServo;//this name may need to change based on if robotC confuses it with procedure "servo[]"
	bool grabbed;
}tGrabber;

tGrabber GRABBER;

void SetGoalGrabber(int position)
{
	SetServoPosition(GRABBER.pServo, position);
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
	tMotor pMotor;//this name may need to change based on if robotC confuses it with procedure "motor[]"
	TServoIndex pServo_1;
	TServoIndex pServo_2;
	TServoIndex pServoArm;
	bool running;
	bool raised;
}tSweeper;

tSweeper SWEEPER;


// BEGIN SWEEPER ARM //
void SetSweeperArm(int position)
{
	SetServoPosition(SWEEPER.pServoArm, position);
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
	if(SWEEPER.raised) // NOTE: Switched from negative test to positive test.
	{
		LowerSweeperArm();
	}
	else
	{
		RaiseSweeperArm();
	}
	SWEEPER.raised = !SWEEPER.raised;
}

//END SWEEPER ARM //

void RunSweeperMotor()
{
	SetMotorPower(SWEEPER.pMotor, -1 * MAX_MOTOR_POWER);
}

void StopSweeperMotor()
{
	SetMotorPower(SWEEPER.pMotor, 0);
}

void SetSweeperServos(float speed)
{
	SetServoSpeed(SWEEPER.pServo_1, speed, CCW);
	SetServoSpeed(SWEEPER.pServo_2, speed, CCW);
}

void RunSweeperServos()
{
	SetSweeperServos(1.0); // 1.0 is max speed. Valid range is 0-1.
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
	TServoIndex pServoSlide;
	TServoIndex pServoWinch;
	TServoIndex pServoLoad;
	tSensors pSensorTouch;
	int position;
	bool loader;
}tTube;

tTube TUBE;

bool tubeRaised()
{
	bool state;
	if (SensorValue(TUBE.pSensorTouch) == 1023)
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
	SetServoSpeed(TUBE.pServoSlide, 0.2, CCW);
}

void SlideTubeLeft()
{
	SetServoSpeed(TUBE.pServoSlide, 0.2, CW);
}

void StopSlide()
{
	SetServoSpeed(TUBE.pServoSlide, 0.0);
}

void SetTubeHeight(int height)
{
	SetServoPosition(TUBE.pServoWinch, height);
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
	switch (position)
  {
  	case 0:
  	  SetTubeHeight(MEDIUM_GOAL_HEIGHT);
  	  break;

  	case 1:
  	  SetTubeHeight(HIGH_GOAL_HEIGHT);
  	  break;

  	case 2:
  	  SetTubeHeight(CENTER_GOAL_HEIGHT);
  	  break;

  	default:
  	  // Do nothing ...
  }

  TUBE.position = position;
}

void LoadPosition_1()
{
	SetServoPosition(TUBE.pServoLoad, LOAD_POSITION_1);
}

void LoadPosition_2()
{
	SetServoPosition(TUBE.pServoLoad, LOAD_POSITION_2);
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
