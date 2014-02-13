//
// DownLift.c
//
#define ROBOT_NAME  ROBOT_NAME_BOB

#include "..\lib\MainPrelude.h"
#include "config\RobotConfig.h"
#include "..\lib\MainPostlude.h"

task main()
    {
    if (InitializeMain(true, true))
        {
        SpeculativelyUpdateBlackboard();
        //
        for (;;)
            {
            if (false)
                {
                StopRobot();
                break;
                }
            //
            SendOneMotorPower(motorArm, -2);     // down *slow*
            //
            EndTimeSlice();
            }
        }
    }
