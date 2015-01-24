#ifndef FTC8923_FUNCTIONS
#define FTC8923_FUNCTIONS

#include "../../Library/servos/servos.c"
#include "../../Library/motors/motors.c"

const int GRAB_GOAL_POS = 170;
const int RELEASE_GOAL_POS = 100;

//Goal grabber functions
void SetGoalGrabberPosition(int pos)
{
	SetServoPosition(goalGrabber, pos);
}
void GrabGoal()
{
	SetGoalGrabberPosition(GRAB_GOAL_POS);
}
void ReleaseGoal()
{
	SetGoalGrabberPosition(RELEASE_GOAL_POS);
}

//Collector functions
const int RUN_COLLECTOR_FORWARD = -100;
const int RUN_COLLECTOR_BACKWARD = 100;
const int STOP_COLLECTOR = 0;

void RunCollector(int power)
{
	SetMotorPower(collector, power);
}
void CollectBalls()
{
	RunCollector(RUN_COLLECTOR_FORWARD);
}
void ReleaseBalls()
{
	RunCollector(RUN_COLLECTOR_BACKWARD);
}
void StopCollector()
{
	RunCollector(STOP_COLLECTOR);
}

//Container functoins
const int HOLD_BALLS = 127;
const int DUMP_BALLS = 127;

void SetContainerPos(int pos)
{
	SetServoPosition(container, pos);
}
void HoldBalls()
{
	SetContainerPos(HOLD_BALLS);
}
void DumpBalls()
{
	SetContainerPos(DUMP_BALLS);
}

//Lift functions

//Positions of lift
typedef enum
{
	DownPos = 0,
	LowGoalPos = 5000,
	MediumGoalPos = 10000,
	HighGoalPos = 15000,
	CenterGoalPos = 20000
}
LiftPositionsEnum;

void SetLiftPower(int power)
{
	SetMotorPower(mtrLifterL, power);
	SetMotorPower(mtrLifterR, power);
}

void LowerLift()
{
	SetLiftPower(-100);
}
void RaiseLift()
{
	SetLiftPower(100);
}
void StopLift()
{
	SetLiftPower(0);
}

bool LiftAboveDetect(int pos)
{
	if(nMotorEncoder[mtrLifterL] > pos)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool LiftBelowDetect(int pos)
{
	if(nMotorEncoder[mtrLifterL] < pos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MoveLifter(int pos)
{
	while(LiftAboveDetect(pos))
	{
		LowerLift();
	}
	while(LiftBelowDetect(pos))
	{
		RaiseLift();
	}
	StopLift();
}
#endif
