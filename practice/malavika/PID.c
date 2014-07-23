#ifndef PID_C
#define PID_C

float previousError = 0;
float proportional = 0;
float integral = 0;
float derivative = 0;

int changeTime = 200;
float pConst = 0.5292;
float iConst = 0.0000000075;
float dConst = 0.0375;

task pid()
{
	while(true)
	{
		int error = requestedSpeed - GetMotorSpeed();
		proportional = error;
		integral += (error * changeTime);
		derivative = (error - previousError) / changeTime;
		int finalMotorPower = (pConst * proportional) + (iConst * integral) + (dConst * derivative);
		previousError = error;
		SetMotorSpeed(finalMotorPower);
		wait1Msec(changeTime);
	}
}

#endif
