#ifndef SERVOS_C
#define SERVOS_C

int GOAL_GRABBER_GRAB_GOAL = 45;
int GOAL_GRABBER_RELEASE_GOAL = 150;

void SetServoPosition(tMotor servoName, int servoPosition)
{
  servo[servoName] = servoPosition;
}
void SetGoalGrabberPosition(int position)
{
	SetServoPosition(goalGrabber, position);
}
void GrabGoal()
{
	SetGoalGrabberPosition(GOAL_GRABBER_GRAB_GOAL);
}
void ReleaseGoal()
{
	SetGoalGrabberPosition(GOAL_GRABBER_RELEASE_GOAL);
}

#endif
