#ifndef TOWALL_C
#define TOWALL_C

void ToWall(int move = 0)
{
	int target = 30;

	if(move == 1)
	{
		if(SensorValue[sonar] > target + 3)
		{
			LeftMotorPower(50);
			RightMotorPower(50);
		}
		else if(SensorValue[sonar] < target - 3)
		{
			LeftMotorPower(-50);
			RightMotorPower(-50);
		}
		else
		{
			move = 0;
		}
	}
}
#endif
