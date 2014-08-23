#ifndef SONAR_C
#define SONAR_C

#include "../toWall.c"

void Sonar()
{
	float distance = SensorValue[sonar] * 0.4;
	nxtDisplayTextLine(0, "Distance(Inches): %d", distance);
}
#endif
