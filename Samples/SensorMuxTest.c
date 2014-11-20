//
// SensorMuxTest.c
//
#define ROBOT_NAME  ROBOT_NAME_SENSOR_MUX_TEST

#include "..\lib\MainPrelude.h"
#include "config\RobotConfig.h"
#include "..\lib\MainPostlude.h"


task main()
    {
    if (InitializeMain(true, true))
        {
        DisplayMessage("Success");
        InfiniteIdleLoop();
        }
    else
        {
        InfiniteIdleLoop(); // Just sit there and update the display
        }
    }
