#define ROBOT_NAME ROBOT_NAME_SPACEELEVATOR

#include "..\lib\MainPrelude.h"
#include "config\RobotConfig.h"
#include "..\lib\MainPostlude.h"

task main()
{
    if (InitializeMain(true, true))
    {
        ClearTimer(T1);
        int powerTreadsStart = 38;
        int powerWheelsStart = 38;
        int powerTreadsCur = powerTreadsStart;
        int powerWheelsCur = powerWheelsStart;
        StartReadingTouchSensor(touchTop);
        StartReadingTouchSensor(touchBottom);
        //StartReadingTouchSensor(touchArmTread);
        //StartReadingTouchSensor(touchArmWheel);
        BOOL touchTopLast = touchTop.fValue;
        BOOL touchBottomLast = touchBottom.fValue;

        /*ENCOD encArmTreadStart;
        ReadEncoder(OUT encArmTreadStart, motorArmTread);
        ENCOD encArmWheelStart;
        ReadEncoder(OUT encArmWheelStart, motorArmWheel);
        ENCOD encArmTreadCur;
        ENCOD encArmWheelCur;
        ENCOD encArmTreadLast;
        ReadEncoder(OUT encArmTreadLast, motorArmTread);
        ENCOD encArmWheelLast;
        ReadEncoder(OUT encArmWheelLast, motorArmWheel);*/

        ENCOD encWheelsCur;
        ReadEncoder(OUT encWheelsCur, motorWheels);
        ENCOD encBottom = 0;
        ENCOD encSlow;

        // First four times the robot hits the bottom, stop at the bottom hopefully... needs testing
/*        for (int i = 1; i <=4;)
        {
            ReadEncoder(OUT encWheelsCur, motorWheels);
            encSlow = encBottom + 1440 * 3;
            powerTreadsCur = 38;
            powerWheelsCur = 38;

            if ((touchTop.fValue != touchTopLast) && touchTop.fValue)
            {
                touchTopLast = touchTop.fValue;
                powerTreadsCur = -powerTreadsCur;
                powerWheelsCur = -powerWheelsCur;
            }
            else if (!touchTop.fValue)
            {
                touchTopLast = touchTop.fValue;
            }

            if ((touchBottom.fValue != touchBottomLast) && touchBottom.fValue)
            {
                touchBottomLast = touchBottom.fValue;
                encBottom = encWheelsCur;
                i++;

                // Stop robot
                LockBlackboard();
                SetMotorPower(motorTreads, 0);
                SetMotorPower(motorWheels, 0);
                SendMotorPowers();
                ReleaseBlackboard();

                // Wait for signal to go, then go
                while(!(touchArmTread.fValue && touchArmWheel.fValue))
                {
                    LockBlackboard();
                    SetMotorPower(motorTreads, 0);
                    SetMotorPower(motorWheels, 0);
                    SendMotorPowers();
                    ReleaseBlackboard();

                    if (!touchArmTread.fValue && !touchArmWheel.fValue)
                    {
                        LockBlackboard();
                        SetMotorPower(motorArmTread, 50);
                        SetMotorPower(motorArmWheel, 50);
                        SendMotorPowers();
                        ReleaseBlackboard();
                    }
                    else if (touchArmTread.fValue && !touchArmWheel.fValue)
                    {
                        LockBlackboard();
                        SetMotorPower(motorArmTread, 0);
                        SetMotorPower(motorArmWheel, 50);
                        SendMotorPowers();
                        ReleaseBlackboard();
                    }
                    else if (!touchArmTread.fValue && touchArmWheel.fValue)
                    {
                        LockBlackboard();
                        SetMotorPower(motorArmTread, 50);
                        SetMotorPower(motorArmWheel, 0);
                        SendMotorPowers();
                        ReleaseBlackboard();
                    }
                    else if (touchArmTread.fValue && touchArmWheel.fValue)
                    {
                        LockBlackboard();
                        SetMotorPower(motorArmTread, 0);
                        SetMotorPower(motorArmWheel, 0);
                        SendMotorPowers();
                        ReleaseBlackboard();
                    }
                }
            }
            else if (!touchBottom.fValue && encWheelsCur > encSlow)
            {
                touchBottomLast = touchBottom.fValue;
            }
            else if (!touchBottom.fValue && (encWheelsCur < encSlow) && powerTreadsCur == -38)
            {
                touchBottomLast = touchBottom.fValue;
                powerTreadsCur = -5;
                powerWheelsCur = -5;
            }

            LockBlackboard();
            SetMotorPower(motorTreads, powerTreadsCur);
            SetMotorPower(motorWheels, powerWheelsCur);
            SendMotorPowers();
            ReleaseBlackboard();
        }
*/
        while(time10[T1] < (30000 - 175))
        {
            // Go up and down continuously
            LockBlackboard();
            ReadEncoder(OUT encWheelsCur, motorWheels);
            ReleaseBlackboard();
            encSlow = encBottom + 1440 * 2;
            motorStallBehavior = MOTOR_STALL_BEHAVIOR_ONLY_SET_FLAG;

            if (fMotorStallDetected == true)
            {
                fMotorStallDetected = false;
                if (powerTreadsCur < 0 && powerWheelsCur < 0)
                {
                    powerTreadsCur = 38;
                    powerWheelsCur = 38;
                }
                else if (powerTreadsCur > 0 && powerWheelsCur > 0)
                {
                    powerTreadsCur = -38;
                    powerWheelsCur = -38;
                }

                //powerTreadsCur = -38;
                //powerWheelsCur = -38;

                LockBlackboard();
                SetMotorPower(motorTreads, 0);
                SetMotorPower(motorWheels, 0);
                SendMotorPowers();
                ReleaseBlackboard();
                TRACE(("stall"));

                //wait10Msec(250);        //introduced a delay between detecting a stall and reversing direction. -RMS

                LockBlackboard();
                SetMotorPower(motorTreads, powerTreadsCur);
                SetMotorPower(motorWheels, powerWheelsCur);
                SendMotorPowers();
                ReleaseBlackboard();
                TRACE(("stall"));
            }

            if ((touchTop.fValue != touchTopLast) && touchTop.fValue)
            {
                touchTopLast = touchTop.fValue;
                powerTreadsCur = -38;
                powerWheelsCur = -38;
                LockBlackboard();
                SetMotorPower(motorTreads, 0);
                SetMotorPower(motorWheels, 0);
                SendMotorPowers();
                ReleaseBlackboard();
                wait1Msec(250);
                TRACE(("top"));
            }
            else if (!touchTop.fValue)
            {
                touchTopLast = touchTop.fValue;
            }

            if ((touchBottom.fValue != touchBottomLast) && touchBottom.fValue)
            {
                touchBottomLast = touchBottom.fValue;
                powerTreadsCur = 38;
                powerWheelsCur = 38;
                LockBlackboard();
                SetMotorPower(motorTreads, 0);
                SetMotorPower(motorWheels, 0);
                SendMotorPowers();
                ReleaseBlackboard();
                wait1Msec(250);
                TRACE(("bottom"));
            }
            else if (!touchBottom.fValue)
            {
                touchBottomLast = touchBottom.fValue;
                if ((encWheelsCur < encSlow) && (powerTreadsCur < -20))
                {
                    powerTreadsCur = -20;
                    powerWheelsCur = -20;
                }
            }

            LockBlackboard();
            SetMotorPower(motorTreads, powerTreadsCur);
            SetMotorPower(motorWheels, powerWheelsCur);
            SendMotorPowers();
            ReleaseBlackboard();
        }
    }
}

/* ReadEncoder(OUT encArmTreadCur, motorArmTread);
ReadEncoder(OUT encArmWheelCur, motorArmWheel);

if ((encArmTreadCur < (encArmTreadLast + 60)) && !touchTop.fValue)
{
LockBlackboard();
SetMotorPower(motorArmTread, 50);
SendMotorPowers();
ReleaseBlackboard();
}
else
{
ReadEncoder(OUT encArmTreadLast, motorArmTread);
LockBlackboard();
SetMotorPower(motorArmTread, 0);
SendMotorPowers();
ReleaseBlackboard();
}

if ((encArmWheelCur < (encArmWheelLast + 60)) && !touchTop.fValue)
{
LockBlackboard();
SetMotorPower(motorArmWheel, 50);
SendMotorPowers();
ReleaseBlackboard();
}
else
{
ReadEncoder(OUT encArmWheelLast, motorArmWheel);
LockBlackboard();
SetMotorPower(motorArmWheel, 0);
SendMotorPowers();
ReleaseBlackboard();
}
*/
