#ifndef FTC8923_FUNCTIONS
#define FTC8923_FUNCTIONS

/* Code Review by Darrell
 - Should adjust the GrabGoal() and ReleaseGoal() functions to call a single function named SetGoalServoPosition().
 - Apply this concept to the rest of the serve set functions too. This will further reduce code redundancy so that you call the single function.
*/

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
#define GRAB_GOAL_SERVO_POS 170
#define RELEASE_GOAL_SERVO_POS 100

void SetGoalGrabberPos(int position)
{
	servo[goalGrabber] = position;
}

//Collector functions
#define RUN_COLLECTOR_FORWARD 100
#define RUN_COLLECTOR_BACKWARD -100
#define STOP_COLLECTOR 0

void RunCollector(int power)
{
	SetMotorPower(collector, power);
}

//Container functoins
#define HOLD_BALLS 127
#define DUMP_BALLS 127

void SetContainerPos(int pos)
{
	servo[container] = pos;
}

/* Code Review by Darrell
 - add a SetMotorPower(tMotor motorName, int power) function
 - add a SetLiftPower(int power) function which uses SetMotorPower()
 - adjust LowerLift() to call SetLiftPower()
 - etc etc
*/

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
