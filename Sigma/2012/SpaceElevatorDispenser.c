#define ROBOT_NAME ROBOT_NAME_SPACEELEVATOR

#include "..\lib\MainPrelude.h"
#include "config\RobotConfig.h"
#include "..\lib\MainPostlude.h"

task main()
{
    if (InitializeMain(true, true))
    {
        ClearTimer(T1);

    }
}
