//
// DownLift.c
//
#define ROBOT_NAME  ROBOT_NAME_FTC417_2011_V1

#include "..\lib\MainPrelude.h"
#include "config\RobotConfig.h"
#include "..\lib\MainPostlude.h"

task main()
    {
    if (InitializeMain(true, true))
        {
        StartReadingTouchSensor(touchForklift);
        SpeculativelyUpdateBlackboard();
        //
        for (;;)
            {
            if (touchForklift.fValue)
                {
                StopRobot();
                break;
                }
            //
            SendOneMotorPower(motorForklift, -2);     // down *slow*
            //
            EndTimeSlice();
            }
        }
    }
