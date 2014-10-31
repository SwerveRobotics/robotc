
#define ROBOT_NAME  ROBOT_NAME_FTC417_2012_TASKBOT
          //\\
         //  \\
        //    \\
       //======\\
      //\\    //\\
     //  \\  //  \\
    //    \\//    \\
   //==============\\
#include "..\lib\MainPrelude.h"
#include "config\RobotConfig.h"
#include "..\lib\MainPostlude.h"
#include "TaskbotDUEL_TELE.h"

void DoAutonomous()
// to get in the way because were basically nonfunctional otherwise
	{
	DriveForwards(270);
	TurnRight(90);
	DriveForwards(200);
	TurnRight(90);
	DriveForwards(200);
	TurnRight(90);
	DriveForwards(200);
	TurnRight(90);
	}

/*BOOL DoDriveJoystick(int jyc)
    {
    DoManualDrivingControl(jyc, joystick);  // in DriveAids.h

    if (0)
        {
        }
    else if (joyBtnOnce(jyc, JOYBTN_LEFTTRIGGER_UPPER))
		    {
		    // Provide a means to correct from spontaneous motor controller reboots
		    STICKYFAILURE fOverallSuccess = true;
		    InitializeMotors(fOverallSuccess);
		    TRACE(("motors manually reinitialized"));
		    }
		else if (joyBtn(jyc, JOYBTN_RIGHTTRIGGER_LOWER))
		{

		Beep(NOTE_G_FLAT);
		}
		else if (joyBtn(jyc, JOYBTN_LEFTTRIGGER_LOWER))
		{
		 //MoveServo(svoLatch, svposLatch, true);
		}
		else if (joyBtn(jyc, JOYBTN_B))
		{
		  //MoveServo(svoLatch, svposLatchTurnBack, true);
		}
		else if (joyBtn(jyc, JOYBTN_A))
		{
		  MoveServo(svoPuller, svposPuller, true);
		}
		else if (joyBtn(jyc, JOYBTN_X))
		{
		  MoveServo(svoPuller, svposPullerBack, true);
		}

    return true;
    }*/

#if 0
void DoTeleOp()
    {
    DisplayMessage("<- tele op ->");
    SetHaltProgramOnMotorStall(false);

    for (;;)
        {
        if (getJoystickSettings(joystick))
            {
            DoDriveJoystick(1);
            }
        else if (nSysTime - joystick.msg.msReceived > MS_JOYSTICK_FCS_DISCONNECTED_THRESHOLD)
            {
            /* We haven't received a new message from the FCS in WAY too long  */
            /* So we have to consider ourselves disconnected. We take steps to */
            /* reign in a possibly runaway robot.                              */
            StopRobot();

            /* Sound an alarm if we've LOST communication rather than never    */
            /* seen it in the first place                                      */
            if (joystick.msg.serialNumber != 0)
                {
                /* SOMETHING audible for helpful debugging; could be better */
                Beep(NOTE_E);
                }
            }

        /* Be nice: let other tasks run */
        SpeculativelyUpdateBlackboard();
        }
    }
#endif

task main()
    {
    if (InitializeMain(true, true))
        {
        // Configure our telemetry
        TelemetryUse(true,false);       // Bluetooth, but no USB; change if necessary
        TelemetryEnable(false);         // *Note* disabled for now.

        // Put feedback on the screen during initialization
        fDisplaySonic = true;
        fDisplayEopdFront = true;

        // Wait until the FCS tells us to go
        waitForStart();

        // During game play avoid unecessary delays in reading sonic
        fDisplaySonic = false;
        fDisplayEopdFront = false;

        // Off to the races!
        if (PROGRAM_FLAVOR_TELEOP == programFlavor)
            {
            DoTeleOp();
            }
        else
            {
            DoAutonomous();
            }
        }
    else
        {
        InfiniteIdleLoop(); // Just sit there and update the display
        }
    }
