#ifndef PID_C
#define PID_C

float previousError = 0;
float proportional = 0;
float integral = 0;
float derivative = 0;

task PID()
{
	int changeTime = 200;
	int pConst;
	int iConst;
	int dConst;

	while(true)
	{
		int speed;
		int error = speed - nMotorEncoder[single];
		proportional = error;
		integral += (error * changeTime);
		derivative = (error - previousError) / changeTime;
		int finalMotorPower = (pConst * proportional) + (iConst * integral) + (dConst * derivative);
		SetSpeedIfAboveDeadZone(finalMotorPower, deadZone);
		previousError = error;
		wait1Msec(changeTime);
	}
}

#endif
