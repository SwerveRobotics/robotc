//
// TeleV2.c
//
#define ROBOT_NAME  ROBOT_NAME_BOB

#include "..\lib\MainPrelude.h"
#include "config\RobotConfig.h"
#include "..\lib\MainPostlude.h"
#include "TeleOp6220.h"
//#include "C:\ftc\drivers\2.3\drivers\HTIRS2-driver.h"

void DoAutonomous()
	{
	msElapsedStart = nSysTime;
    TRACE(("**** begin autonomous ****"));
    DisplayMessage("<- autonomous ->");

    //drive away from wall
    LockBlackboard();
	SetMotorPower(motorLeft, 50);
	SetMotorPower(motorRight, 50);
	SendMotorPowers();
	ReleaseBlackboard();
	wait1Msec(500);
	LockBlackboard();
	SetMotorPower(motorLeft, 0);
	SetMotorPower(motorRight, 0);
	SendMotorPowers();
	ReleaseBlackboard();

    //move arm up so IR sensor is level with transmitter
    LockBlackboard();
    SetMotorPower(motorArm, -100);
    SendMotorPowers();
    ReleaseBlackboard();
    wait1Msec(4000);
    LockBlackboard();
    SetMotorPower(motorArm, 0);
    SendMotorPowers();
    ReleaseBlackboard();

    //wiggle robot back and forth until it faces the IR signal
    StartReadingIRSensor(irsensor);
    /*int dir = 0;
    int acs1, acs2, acs3, acs4, acs5 = 0;
    int maxSig = 0;
    int val = 0;
    //tHTIRS2DSPMode mode = DSP_1200;

    while(true)
    {
        //dirAC = HTIRS2readACDir(irsensor);
        dir = irsensor.dirAC[
        maxSig = (acs1 > acs2) ? acs1 : acs2;
        maxSig = (maxSig > acs3) ? maxSig : acs3;
        maxSig = (maxSig > acs4) ? maxSig : acs4;
        maxSig = (maxSig > acs5) ? maxSig : acs5;

        val = dir - 5;

        motor[motorLeft] = 50 + 30 * val;
        motor[motorRight] = 50 - 30 * val;

        wait10Msec(2);
    }*/
 /*   int maxSig = 0;
    while(true)
        {
        maxSig = (irsensor.signalAC[0] > irsensor.signalAC[1]) ? irsensor.signalAC[0] : irsensor.signalAC[1];
        maxSig = (maxSig > irsensor.signalAC[2]) ? maxSig : irsensor.signalAC[2];
        maxSig = (maxSig > irsensor.signalAC[3]) ? maxSig : irsensor.signalAC[3];
        maxSig = (maxSig > irsensor.signalAC[4]) ? maxSig : irsensor.signalAC[4];

        int val = irsensor.dirAC - 5;
        LockBlackboard();
	    SetMotorPower(motorLeft, 50 + 30 *val);
	    SetMotorPower(motorRight, 50 - 30 *val);
	    SendMotorPowers();
	    ReleaseBlackboard();
	    wait10Msec(2);
	    TRACE(("val %d", val));
	    TRACE(("maxSig %d", maxSig));
        }*/
 /*   int signalTarget = 240;
    while(irsensor.signalAC[2] < signalTarget)
	    {
	    TRACE(("%d", irsensor.signalAC[2]));
	    if(irsensor.dirAC < 5)
	        {
	        LockBlackboard();
	        SetMotorPower(motorLeft, 50);
	        SetMotorPower(motorRight, -50);
	        SendMotorPowers();
	        ReleaseBlackboard();
	        }
	    else if(irsensor.dirAC > 6)
	        {
	        LockBlackboard();
	        SetMotorPower(motorLeft, 50);
	        SetMotorPower(motorRight, -50);
	        SendMotorPowers();
	        ReleaseBlackboard();
	        }
	    else
	        {
	        LockBlackboard();
	        SetMotorPower(motorLeft, 50);
	        SetMotorPower(motorRight, 50);
	        SendMotorPowers();
	        ReleaseBlackboard();
	        }
	    wait1Msec(20);
	    }*/
	//put rings on
	//MoveServo(svoHand, 250);
	//DriveForwards(5);
	}

#if 0
void DoManualTankDrivingControl(int joy, TJoystick& joystick)
	{
	int map[] =
        {
         0,  1,  1,  1,  2,  2,  2,  2,  3,  3,
         3,  3,  4,  4,  4,  5,  5,  5,  6,  6,
         6,  7,  7,  7,  8,  8,  8,  9,  9,  9,
        10, 10, 10, 11, 11, 11, 12, 12, 13, 13,
        14, 14, 15, 15, 16, 16, 17, 17, 18, 18,
        19, 19, 20, 20, 21, 21, 22, 22, 23, 23,
        24, 24, 25, 25, 26, 27, 27, 28, 29, 29,
        30, 31, 31, 32, 32, 34, 35, 36, 37, 38,
        39, 40, 41, 42, 43, 44, 45, 46, 47, 49,
        50, 52, 54, 57, 61, 65, 69, 76, 84, 96,
        100};

    // Extract values from the joysticks that we find useful
    int ctlLeft    =  joyLeftY(joy);      // -128 to 127
    int ctlRight =  joyRightY(joy);     // -128 to 127

    // Remove sensitivity in the middle of the controls.
    // At the same time, avoid a big control jump at the
    // edge of the dead zone.
    const int sensitivityThreshold = joyThrottleDeadZone;
    int sgnLeft    = Sign(ctlLeft);
    int sgnRight = Sign(ctlRight);

    ctlLeft    = Max(0, abs(ctlLeft)    - sensitivityThreshold);
    ctlRight = Max(0, abs(ctlRight) - sensitivityThreshold);

    ctlLeft    = ctlLeft    * sgnLeft;
    ctlRight = ctlRight * sgnRight;

    // Convert the range of controls from +-128 to +-100. Do
    // so symmetrically for both positive and negative numbers.
    float scaleLeft = 100.0 / (128.0 - (float)sensitivityThreshold);
    float scaleRight = 100.0 / (128.0 - (float)sensitivityThreshold);
    ctlLeft    = Rounded((float)ctlLeft    * scaleLeft, int);
    ctlRight = Rounded((float)ctlRight * scaleRight, int);
    // if (ctlPower != 0 || ctlSteering != 0) {  TRACE(("power=%d steering=%d", ctlPower, ctlSteering));

    ctlLeft    =    ctlLeft >= 0 ? map[ctlLeft]    : -map[-ctlLeft];
    ctlRight = ctlRight >= 0 ? map[ctlRight] : -map[-ctlRight];

    /*if (true) // set to false to disable
        {
	    // Avoid clipping the power settings so we can still effectively
	    // steer even in under throttle.
	    //
	    // Want
	    //      -100 <= ctlPower - ctlSteering <= 100
	    //      -100 <= ctlPower + ctlSteering <= 100
	    //
	    // That is, we want
	    //      ctlSteering - 100 <= ctlPower <=  ctlSteering + 100
	    //     -ctlSteering - 100 <= ctlPower <= -ctlSteering + 100
	    //
	    if ( ctlSteering - 100 >  ctlPower)          ctlPower =  ctlSteering - 100;
	    if ( ctlPower          >  ctlSteering + 100) ctlPower =  ctlSteering + 100;
	    if (-ctlSteering - 100 >  ctlPower)          ctlPower = -ctlSteering - 100;
	    if ( ctlPower          > -ctlSteering + 100) ctlPower = -ctlSteering + 100;
	    }*/

    // Update the motor power. The SetMotorPower internals will
    // clamp the power provided to +-100.
    int16 powerLeft  = ctlLeft;
    int16 powerRight = ctlRight;

    // Correct the power balance to the wheels in order to better drive straight
    float balance = BalanceFromDirection(ctlLeft >= 0 ? FORWARD : BACKWARD);
    BalancePower(powerLeft, powerRight, balance);
    // if (powerLeft != 0 || powerRight != 0) { TRACE(("l=%d r=%d", powerLeft, powerRight)); }

// TRACE(("motorL %d", powerLeft));
// TRACE(("motorR %d", powerRight));
    LockBlackboard();
    SetMotorPower(motorLeft,  powerLeft);
    SetMotorPower(motorRight, powerRight);
    SendMotorPowers();
    ReleaseBlackboard();
	}
#endif

#if 0
BOOL DoDriveJoystick(int jyc)
    {
    DoManualTankDrivingControl(jyc, joystick);  // above

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

    return true;
    }
#endif

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
    //programFlavor = PROGRAM_FLAVOR_AUTONOMOUS;
    if (InitializeMain(true, true))
        {
        // Configure our telemetry
        TelemetryUse(true,false);       // Bluetooth, but no USB; change if necessary
        TelemetryEnable(false);         // *Note* disabled for now.

        // Put feedback on the screen during initialization
        /*fDisplaySonic = true;
        fDisplayEopdFront = true;*/

        //Read arm motor encoder
        ReadEncoder(OUT encStart, motorArm);

        // Wait until the FCS tells us to go
        waitForStart();

        // During game play avoid unecessary delays in reading sonic
        /*fDisplaySonic = false;
        fDisplayEopdFront = false;*/

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
