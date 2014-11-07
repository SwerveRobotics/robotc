#ifndef IR_SEKKER_C
#define IR_SEEKER_C

tSensors IR_SEEKER;

void RegisterIRSeeker(tSensors IRSeekerName)
{
	IR_SEEKER = IRSeekerName;
}

int ReadIRSensor()
{
	return SensorValue[IR_SEEKER];
}

#endif
