#ifndef FTC8923_FUNCTIONS
#define FTC8923_FUNCTIONS

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

//Goal grabber functions
const int GRAB_GOAL_SERVO_POS = 170;
const int RELEASE_GOAL_SERVO_POS = 100;

void SetGoalGrabberPos(int position)
{
	servo[goalGrabber] = position;
}

//Collector functions
const int RUN_COLLECTOR_FORWARD = 100;
const int RUN_COLLECTOR_BACKWARD = -100;
const int STOP_COLLECTOR = 0;

void RunCollector(int power)
{
	SetMotorPower(collector, power);
}

//Container functoins
const int HOLD_BALLS = 127;
const int DUMP_BALLS = 127;

void SetContainerPos(int pos)
{
	servo[container] = pos;
}

//Lift functions
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
