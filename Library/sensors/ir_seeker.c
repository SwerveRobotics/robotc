#ifndef IR_SEKKER_C
#define IR_SEEKER_C

typedef enum
{
	SeekerOne,
	SeekerTwo,
	SeekerThree,
	SeekerFour
}SeekerEnum;
const int SEEKER_COUNT = 4;
tSensors IR_SEEKER[SEEKER_COUNT];

void RegisterIRSeeker(SeekerEnum seekerNum = 0, tSensors IRSeekerName)
{
	switch(seekerNum)
	{
		case SeekerOne:
			IR_SEEKER[SeekerOne] = IRSeekerName;
			break;
		case SeekerTwo:
			IR_SEEKER[SeekerTwo] = IRSeekerName;
			break;
		case SeekerThree:
			IR_SEEKER[SeekerThree] = IRSeekerName;
			break;
		case SeekerFour:
			IR_SEEKER[SeekerFour] = IRSeekerName;
			break;
	}
}

int ReadIRSensor(SeekerEnum seekerNum = 0)
{
	return SensorValue[IR_SEEKER[seekerNum]];
}

#endif
