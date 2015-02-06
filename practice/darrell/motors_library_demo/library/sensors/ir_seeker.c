#ifndef IR_SEEKER_C
#define IR_SEEKER_C


tSensors IR_SEEKER;
void RegisterIRSeeker(tSensors irSeekerName)
{
	IR_SEEKER = irSeekerName;
}

int ReadIR()
{
	return SensorValue[IR_SEEKER];
}

void MonitorIRSeeker()
{

}


#endif
