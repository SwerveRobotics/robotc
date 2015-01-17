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
void GrabGoal()
{
	servo[goalGrabber] = 170;
}

void ReleaseGoal()
{
	servo[goalGrabber] = 100;
}

//Collector functions
void CollectBalls()
{
	motor[collector] = -100;
}

void ReleaseBalls()
{
	motor[collector] = 100;
}

void StopCollector()
{
	motor[collector] = 0;
}

//Container functoins
void HoldBalls()
{
	servo[container] = 0;
}

void DumpBalls()
{
	servo[container] = 100;
}

/* Code Review by Darrell
 - add a SetMotorPower(tMotor motorName, int power) function
 - add a SetLiftPower(int power) function which uses SetMotorPower()
 - adjust LowerLift() to call SetLiftPower()
 - etc etc
*/

//Lift functions
void LowerLift()
{
	motor[mtrLifterL] = -100;
	motor[mtrLifterR] = -100;
}
void RaiseLift()
{
	motor[mtrLifterL] = 100;
	motor[mtrLifterR] = 100;
}
void StopLift()
{
	motor[mtrLifterL] = 0;
	motor[mtrLifterR] = 0;
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
