//
// TeleOp6220.h
//

//------------------------------------------------------------------------------
// Joystick switching management
//------------------------------------------------------------------------------

#ifndef USE_JOYSTICK_CONTROLLER_MODES
#define USE_JOYSTICK_CONTROLLER_MODES 1
#endif

typedef enum { JYC1_MODE_PASSIVE, JYC1_MODE_DRIVE, JYC1_MODE_ARM } JYC1_MODE;
typedef enum { JYC2_MODE_PASSIVE,                  JYC2_MODE_ARM } JYC2_MODE;

JYC1_MODE jyc1Mode = JYC1_MODE_DRIVE;
JYC2_MODE jyc2Mode = JYC2_MODE_ARM;

// Changes mode from drive to arm or arm to drive
void SetJoy1Mode(JYC1_MODE mode)
    {
    if (JYC1_MODE_DRIVE == mode && JYC1_MODE_DRIVE != jyc1Mode)
        {
        jyc1Mode = JYC1_MODE_DRIVE;
        jyc2Mode = JYC2_MODE_ARM;
        }
    else if (JYC1_MODE_ARM == mode && JYC1_MODE_ARM != jyc1Mode)
        {
        jyc1Mode = JYC1_MODE_ARM;
        jyc2Mode = JYC2_MODE_PASSIVE;
        }
    }

void CheckJoy1ModeChange(int jyc, TJoystick& joystick)
    {
#if USE_JOYSTICK_CONTROLLER_MODES
    if (joyBtnOnce(jyc, JOYBTN_TOP_LEFT))
        {
        Beep(NOTE_C,30);
        SetJoy1Mode(JYC1_MODE_DRIVE);
        }
    else if (joyBtnOnce(jyc, JOYBTN_TOP_RIGHT))
        {
        Beep(NOTE_G,30);
        SetJoy1Mode(JYC1_MODE_ARM);
        }
#endif
    }

typedef enum
    {
    HAND_DIR_NONE,
    HAND_DIR_OPEN,
    HAND_DIR_CLOSE,
    }HAND_DIR;

typedef enum
    {
    ARM_DIR_NONE,
    ARM_DIR_UP,
    ARM_DIR_DOWN,
    } ARM_DIR;

void MoveHand(HAND_DIR dir)
	{
	switch(dir)
		{
    case HAND_DIR_NONE:
        break;
    case HAND_DIR_OPEN:
        MoveServo(svoRight, svoOpenRight, true);
        MoveServo(svoLeft, svoOpenLeft, true);
        break;
    case HAND_DIR_CLOSE:
        MoveServo(svoRight, svoClosedRight, true);
        MoveServo(svoLeft, svoClosedLeft, true);
        break;
		}
	}

void UpDownArm(MOTOR& mtr, ARM_DIR dir, int speed)
	{
	LockBlackboard();
	switch(dir)
		{
    case ARM_DIR_NONE:
        SetMotorPower(motorArm, 0);
        break;
    case ARM_DIR_UP:
        SetMotorPower(motorArm, speed);
        break;
    case ARM_DIR_DOWN:
        SetMotorPower(motorArm, speed);
        break;
		}
    SendMotorPowers();
    ReleaseBlackboard();
	}

ENCOD encStart;
ENCOD encCur;

//------------------------------------------------------------------------------
// Logic common to both joysticks
//------------------------------------------------------------------------------

BOOL DoCommonJoystick(int jyc)
    {
    return true;
    }

BOOL DoArmControl(int jyc)
    {
    BOOL fSuccess = true;

    HAND_DIR handDir = HAND_DIR_NONE;
    ARM_DIR armDir = ARM_DIR_NONE;
    int joyPos = joyRightY(jyc);
    int svoPos;

    if(0)
        {
        }
    //Buttons to control arm/lift
	else if(joyHat(jyc, JOYHAT_UP))
		{
		armDir = ARM_DIR_UP;
		}
    else if(joyHat(jyc, JOYHAT_DOWN))
	    {
	    armDir = ARM_DIR_DOWN;
	    }
	//buttons to control hand
	else if(joyBtn(jyc, JOYBTN_1))
	    {
	    handDir=HAND_DIR_OPEN;
	    }
	else if (joyBtn(jyc, JOYBTN_3))
	    {
	    handDir= HAND_DIR_CLOSE;
	    }

//make joystick values into servo values
    // if(joyPos > 126)
        // {
        // svoPos = 270;
        // handDir = HAND_DIR_MOVE;
        // }
    // else if(joyPos < 127 && joyPos > -150 )
        // {
        // svoPos = joyPos+ 150;
        // handDir = HAND_DIR_MOVE;
        // }

    //----------------------------------------------------------
    // Cleanup
    //----------------------------------------------------------

    else
        fSuccess = false;

    int speed = 100;

    if(armDir==ARM_DIR_UP)
        {
        speed = -speed;
        }

    //Move arm
    UpDownArm(motorArm, armDir, speed);
    //Move hand servo
    MoveHand(handDir);

    return fSuccess;
    }

//------------------------------------------------------------------------------
// Logic for the main drive joystick
//------------------------------------------------------------------------------
//BOOL buttonPressed = false;
void DoManualTankDrivingControl(int joy, TJoystick& joystick)
	{
	int mapTank[] =
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

    ctlLeft    =    ctlLeft >= 0 ? mapTank[ctlLeft]    : -mapTank[-ctlLeft];
    ctlRight = ctlRight >= 0 ? mapTank[ctlRight] : -mapTank[-ctlRight];

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

	// fine speed control
    /*if(joyBtnOnce(joy, JOYBTN_RIGHTTRIGGER_LOWER))
    {
        ctlLeft = ctlLeft >> 2;
        ctlRight = ctlRight >> 2;
        buttonPressed = true;
        TRACE(("button"));
    }
    else if(joyBtnOnce(joy, JOYBTN_LEFTTRIGGER_LOWER) && buttonPressed == true)
    {
        buttonPressed = false;
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

BOOL DoDriveJoystick(int jyc)
    {
    CheckJoy1ModeChange(jyc, joystick);
    DoManualTankDrivingControl(jyc, joystick);
    DoCommonJoystick(jyc);

    if (0)
        {
        }

    else if (joyBtnOnce(jyc, JOYBTN_LEFTTRIGGER_UPPER))
        {
        // Provide a means to correct from spontaneous motor controller reboots
        STICKYFAILURE fOverallSuccess = true;
        InitializeMotors(fOverallSuccess);
        TRACE(("motors man. reinit."));
        }

    return true;
    }

//------------------------------------------------------------------------------
// Logic for the 'arm' joystick, the one for the second driver / other mode.
// Perhaps we could find a better name for that :-).
//------------------------------------------------------------------------------

/*MILLI msTelemetryBias;
BOOL  fmsTelemetryBiasSet = false;

// Given a displacement on a joystick how far should that move a servo
float ScaleJoystickThrottle(float djoy, float range)
    {
    float scale  = range / (128.0 - (float)joyThrottleDeadZone);
    float result = (float)(abs(djoy) - joyThrottleDeadZone) * scale * sgn(djoy);
    return result;
    }*/

void DoArmJoystick(int jyc)
    {
    CheckJoy1ModeChange(jyc, joystick);
    DoCommonJoystick(jyc);
    DoArmControl(jyc);

    if (0)
        {
        }
    }

//------------------------------------------------------------------------------
// Main teleop logic
//------------------------------------------------------------------------------

/*#if 0
#define DoTeleOpTelemetry()
#else
void DoTeleOpTelemetry()
    {
    if (TelemetryIsEnabled())
        {
        MILLI msNow = nSysTime;
        ENCOD encLeft, encRight;
        ReadLeftRightEncoders(encLeft, encRight);
        LockBlackboard();
        int powerLeft  = MtrOf(motorLeft).power;
        int powerRight = MtrOf(motorRight).power;
        ReleaseBlackboard();

        TelemetryAddInt32(telemetry.serialNumber);
        TelemetryAddInt32(msNow - msTelemetryBias);
        TelemetryAddInt32(encLeft);
        TelemetryAddInt32(encRight);
        TelemetryAddInt16(powerLeft);
        TelemetryAddInt16(powerRight);
        TelemetryAddInt16(joystick.msg.serialNumber);
        TelemetryAddInt32(msNow - joystick.msg.msReceived);
        TelemetrySend();

        telemetry.serialNumber++;
        }
    }
#endif*/

void DoTeleOp()
    {
    DisplayMessage("<- tele op ->");
    SetHaltProgramOnMotorStall(false); // in teleop, stall stops are temporary, not fatal

    // Process the joystick messages as they come in!
    for (;;)
        {
        if (getJoystickSettings(joystick))
            {
            /* Do Joystick Controller #1 */
            switch (jyc1Mode)
                {
            case JYC1_MODE_DRIVE:           DoDriveJoystick(1); break;
            case JYC1_MODE_ARM:             DoArmJoystick(1); break;
            case JYC1_MODE_PASSIVE:         break;
                }

            /* Do Joystick Controller #2 */
            /*switch (jyc2Mode)
                {
            case JYC2_MODE_ARM:             DoArmJoystick(2); break;
            case JYC2_MODE_PASSIVE:         break;
                }*/
                DoArmJoystick(2);
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

        // DoTeleOpTelemetry();

        /* Be nice: let other tasks run */
        SpeculativelyUpdateBlackboard();
        }
    }
