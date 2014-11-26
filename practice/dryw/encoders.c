#ifndef ENCODERS_C
#define ENCODERS_C

int Encoders()
{
	nMotorEncoder[mtrL] = 0;
	nMotorEncoder[mtrR] = 0;
}

void ResetEncoder(tMotor motorAlias)
{

}

task EncoderTask()
{
	while(true)
	{

		wait1Msec(50);
	}
}
#endif
