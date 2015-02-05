#ifndef SERVOS_417_C
#define SERVOS_417_C

#include "../library/motors/servos.c"

//@todo confirm that the SetServoSpeed works correctly as designed in servos.c before using it
// temporary function until above @todo is complete
void SetServoSpeed417(TServoIndex servoName, int speed)
{
	servo[servoName] = speed;
}

//Goal grabber functions
const int GRAB_GOAL_POS = 45;
const int RELEASE_GOAL_POS = 150;
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

// Ball Collector Angle // @todo needs completed - is ball collector angle servo continuous???
const int BALL_COLLECTOR_START_VERTICAL = 111;   //@todo calibration needed
void SetBallCollectorPosition(int val)
{
	SetServoPosition(ballCollecter, val);
}
void SetBallCollectorStartPosition()
{
	SetBallCollectorPosition(BALL_COLLECTOR_START_VERTICAL);
}
int GetBallCollectorPosition()
{
	return servo[ballCollecter];
}
// rotates so top goes TOWARDS ground when arms are at start position
void LowerBallCollector(int increment = 1)
{
	int oldPosition = GetBallCollectorPosition();
	SetBallcollectorPosition(oldPosition+increment);
}
// rotates so top goes AWAY FROM ground when arms are at start position
void RaiseBallCollector(int increment = -1)
{
	int oldPosition = GetBallCollectorPosition();
	SetBallcollectorPosition(oldPosition+increment);
}

// Wrist
const int RELEASE_BALLS_POS = 0;       //@todo calibrate these servo values
const int COLLECT_BALLS_POS = 255;
void SetWristPosition(int val)
{
	SetServoPosition(wrist, val);
}
void CollectBalls()
{
	SetWristPosition(COLLECT_BALLS_POS);
}
void ReleaseBalls()
{
	SetWristPosition(RELEASE_BALLS_POS);
}


// Extender Functions
const int LEFT_EXTENDER_RAISE_ARM = 0;
const int LEFT_EXTENDER_LOWER_ARM = 255;    //@todo calibrate these numbers correct for both arms
const int EXTENDER_FULL_STOP = 128;
// RIGHT_EXTENDER_ARM Positions are calculated based on Left Arm Motor
int GetRightArmPower(int leftArmPower)
{
	return 255-leftArmPower;
}
void SetLeftArmServoPower(int power)
{
	SetServoSpeed417(leftExtender, power);
}
void SetRightArmServoPower(int power)
{
	SetServoSpeed417(rightExtender, power);
}
void MoveExtenderOut(int power = LEFT_EXTENDER_RAISE_ARM)
{
	SetLeftArmServoPower(power);
	SetRightArmServoPower(GetRightArmPower(power));
}
void MoveExtenderIn(int power = LEFT_EXTENDER_LOWER_ARM)
{
	SetLeftArmServoPower(power);
	SetRightArmServoPower(GetRightArmPower(power));
}
void StopExtender()
{
	SetLeftArmServoPower(EXTENDER_FULL_STOP);
	SetRightArmServoPower(EXTENDER_FULL_STOP);
}




#endif
