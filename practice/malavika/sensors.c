#ifndef SENSORS_C
#define SENSORS_C

task sensors ()
{
	if(joy1Btn(1))
	{
		OnColor(BLACK, SensorValue(colorSens));
	}
}

#endif
