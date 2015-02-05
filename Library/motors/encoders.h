#ifndef ENCODERS_H
#define ENCODERS_H

const int ENC_TICKS_PER_REVOLUTION = 1440;

const float ENC_TO_DEG = 360 / ENC_TICKS_PER_REVOLUTION;

int GetEncoderValue(tMotor enc)
{
	return nMotorEncoder[enc];
}

void ZeroEncoder(tMotor enc)
{
	nMotorEncoder[enc] = 0;
}

#endif
