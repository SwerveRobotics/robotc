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

// Wrist
const int RELEASE_BALLS_POS = 0;       //@todo calibrate these servo values
const int COLLECT_BALLS_POS = 255;
void SetWristOpenClose(int pos)
{
	SetServoPosition(wrist, pos);
}
void CollectBalls()
{
	SetWristOpenClose(COLLECT_BALLS_POS);
}
void ReleaseBalls()
{
	SetWristOpenClose(RELEASE_BALLS_POS);
}

// Ball Collector Angle // @todo needs completed - is ball collector angle servo continuous???
const int BALL_COLLECTOR_START_VERTICAL = 111;   //@todo calibration needed
void SetBallCollectorPosition(int pos)
{
	SetServoPosition(ballCollecter, pos);
}
void SetBallCollectorStartPosition()
{
	SetBallCollectorPosition(BALL_COLLECTOR_START_VERTICAL);
}
void MaintainBallCollectorVertical()
{
	// @todo will need to coordinate with the arm functions and angle to the ground in order to determine vertical position
}


// Extender Functions
const int LEFT_EXTENDER_RAISE_ARM = 0;
const int LEFT_EXTENDER_LOWER_ARM = 255;    //@todo calibrate these numbers correct for both arms
const int RIGHT_EXTENDER_RAISE_ARM = 255;
const int RIGHT_EXTENDER_LOWER_ARM = 0;
const int EXTENDER_FULL_STOP = 127;
void SetLeftArmServoPower(int power)
{
	SetServoSpeed417(leftExtender, power);
}
void SetRightArmServoPower(int power)
{
	SetServoSpeed417(rightExtender, power);
}
void RaiseArm()
{
	SetLeftArmServoPower(LEFT_EXTENDER_RAISE_ARM);
	SetRightArmServoPower(RIGHT_EXTENDER_RAISE_ARM);
}
void StopArm()
{
	SetLeftArmServoPower(EXTENDER_FULL_STOP);
	SetRightArmServoPower(EXTENDER_FULL_STOP);
}
void LowerArm()
{
	SetLeftArmServoPower(LEFT_EXTENDER_LOWER_ARM);
	SetRightArmServoPower(RIGHT_EXTENDER_LOWER_ARM);
}




#endif
