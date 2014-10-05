#define ROBOT_NAME ROBOT_NAME_SPACEELEVATOR

#include "..\lib\MainPrelude.h"
#include "config\RobotConfig.h"
#include "..\lib\MainPostlude.h"

task main()
{
    if (InitializeMain(true, true))
    {
        StartReadingTouchSensor(touchBottom);
        SpeculativelyUpdateBlackboard();

        for (;;)
        {
            if(touchBottom.fValue)
            {
                StopRobot();
                break;
            }

            LockBlackboard();
            SetMotorPower(motorTreads, -20);
            SetMotorPower(motorWheels, -20);
            SendMotorPowers();
            ReleaseBlackboard();

            EndTimeSlice();
        }

    }
}
