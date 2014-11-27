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

//Lift functions

//Commented out as the motors haven't yet been declared. We can't declare them yet as we don't know how they will be wired
/*
void LowerLift()
{
	motor[lifter] = -100;
}

void RaiseLift()
{
	motor[lifter] = 100;
}

void StopLift()
{
	motor[lifter] = 0;
}

//Lift position functions
void LiftDownPos()
{
	if(above)
	{
		while(above)
		{
			LowerLift();
		}
	}
	StopLift();
}

void LiftSmallPos()
{
	if(above)
	{
		while(above)
		{
			LowerLift();
		}
	}
	if(below)
	{
		while(below)
		{
			RaiseLift();
		}
	}
	StopLift();
}

void LiftMediumPos()
{
	if(above)
	{
		while(above)
		{
			LowerLift();
		}
	}
	if(below)
	{
		while(below)
		{
			RaiseLift();
		}
	}
	StopLift();
}

void LiftHighPos()
{
	if(above)
	{
		while(above)
		{
			LowerLift();
		}
	}
	if(below)
	{
		while(below)
		{
			RaiseLift();
		}
	}
	StopLift();
}

void LiftCenterPos()
{
	if(below)
	{
		while(below)
		{
			RaiseLift();
		}
	}
	StopLift();
}
*/
#endif
