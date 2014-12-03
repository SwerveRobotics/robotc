#ifndef FTC8923_FUNCTIONS
#define FTC8923_FUNCTIONS

//Goal grabber functions
void GrabGoal()
{
	servo[goalGrabber] = 170;
}

void ReleaseGoal()
{
	servo[goalGrabber] = 100;
}

/*//Collector functions
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

//Lift functions

//Commented out as the motors haven't yet been declared. We can't declare them yet as we don't know how they will be wired

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
}

//Lift position functions
void LiftDownPos()
{
	const int downPos = 0;
	MoveLifter(downPos);
	StopLift();
}
void LiftLowPos()
{
	const int lowPos = 5000;
	MoveLifter(lowPos);
	StopLift();
}
void LiftMediumPos()
{
	const int mediumPos = 10000;
	MoveLifter(mediumPos);
	StopLift();
}
void LiftHighPos()
{
	const int highPos = 15000;
	MoveLifter(highPos);
	StopLift();
}
void LiftCenterPos()
{
	const int centerPos = 20000;
	MoveLifter(centerPos);
	StopLift();
}*/
#endif
