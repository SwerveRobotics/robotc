//
// TeleOp.h
//
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
#define SetJoy1Mode(mode)                                           \
    {                                                               \
    if (JYC1_MODE_DRIVE == mode && JYC1_MODE_DRIVE != jyc1Mode)     \
        {                                                           \
        jyc1Mode = JYC1_MODE_DRIVE;                                 \
        jyc2Mode = JYC2_MODE_ARM;                                   \
        }                                                           \
    else if (JYC1_MODE_ARM == mode && JYC1_MODE_ARM != jyc1Mode)    \
        {                                                           \
        jyc1Mode = JYC1_MODE_ARM;                                   \
        jyc2Mode = JYC2_MODE_PASSIVE;                               \
        }                                                           \
    }

#if USE_JOYSTICK_CONTROLLER_MODES
#define CheckJoy1ModeChange(jyc,joystick)                           \
    {                                                               \
    if (joyBtnOnce(jyc, JOYBTN_TOP_LEFT))                           \
        {                                                           \
        Beep(NOTE_C,30);                                            \
        SetJoy1Mode(JYC1_MODE_DRIVE);                               \
        }                                                           \
    else if (joyBtnOnce(jyc, JOYBTN_TOP_RIGHT))                     \
        {                                                           \
        Beep(NOTE_G,30);                                            \
        SetJoy1Mode(JYC1_MODE_ARM);                                 \
        }                                                           \
    }
#else
#define CheckJoy1ModeChange(jyc,joystick)
#endif

typedef enum
    {
    TINE_DIR_NONE,
    TINE_DIR_LEFT,
    TINE_DIR_RIGHT,
    } TINE_DIR;

typedef enum
    {
    TINE_LOC_NONE,
    TINE_LOC_UP,
    TINE_LOC_DOWN,
    } TINE_LOC;

typedef enum
    {
    MAST_DIR_NONE,
    MAST_DIR_UP,
    MAST_DIR_DOWN,
    } MAST_DIR;

#define svposCRStopped 128
#define svposCRForward 255
#define svposCRReverse 0

void OpenCloseTine(SERVO& svo, TINE_DIR dir)
    // Make this tine svo go in the indicated direction
    {
    switch (dir)
        {
    case TINE_DIR_NONE:
        MoveServo(svo, svposCRStopped, true);
        break;
    case TINE_DIR_LEFT:
        MoveServo(svo, svposCRReverse, true);
        break;
    case TINE_DIR_RIGHT:
        MoveServo(svo, svposCRForward, true);
        break;
        }
    }

void UpDownTine(SERVO& svo, TINE_LOC loc)
    {
    switch (loc)
        {
    case TINE_LOC_UP:
        MoveServo(svo, svposTineUp, true);
        break;
    case TINE_LOC_DOWN:
        MoveServo(svo, svposTineDown, true);
        break;
        }
    }

MAST_DIR mastDirPrev = MAST_DIR_NONE;

void UpDownMast(MOTOR& mtr, MAST_DIR dir, int speed)
    {
    if (MAST_DIR_NONE==mastDirPrev)
        {
        if (MAST_DIR_NONE != dir)
            {
          //  TRACE(("starting mast"));
            StartReadingTouchSensor(touchForklift);
            SpeculativelyUpdateBlackboard();        // make sure we *see* the current reading
            }
        }
    else if (MAST_DIR_NONE!=mastDirPrev)
        {
        if (MAST_DIR_NONE== dir)
            {
          //  TRACE(("stopping mast"));
            StopReadingTouchSensor(touchForklift);
            }
        }
    mastDirPrev = dir;

    if (motorForklift.fActive)
        {
		    LockBlackboard();
		    switch (dir)
		        {
		    case MAST_DIR_NONE:
		        SetMotorPower(motorForklift, 0);
		        break;
		    case MAST_DIR_UP:
		        SetMotorPower(motorForklift, speed);
		        break;
		    case MAST_DIR_DOWN:
		        SetMotorPower(motorForklift, speed);      // NB: currently down slowly
		        break;
		        }
		    SendMotorPowers();
		    ReleaseBlackboard();
		    }
    }

void RaiseMastSlightly() // not yet tested
    {
    ENCOD encStart;
    ReadEncoder(OUT encStart, motorForklift);
    //
    SendOneMotorPower(motorForklift, 30);
    //
    for (;;)
        {
        ENCOD encCur;
        ReadEncoder(OUT encCur, motorForklift);
        if (encCur - encStart > 360 * 4)        // REVIEW: are signs correct? is one rev correct?
            break;
        }
    //
    SendOneMotorPower(motorForklift, 0);
    }

void LowerMastSlowlyToLimitSwitch()
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
        SendOneMotorPower(motorForklift, -5);     // down *slow*
        EndTimeSlice();
        }
    //
    StopReadingTouchSensor(touchForklift);
    }

// The reading on the mast motor's encoder when the mast is all the way down
ENCOD encMastBottom = 0;

ENCOD encAnchorUp = 0;
ENCOD encAnchorDown = (120 * 1440) / 360;
//------------------------------------------------------------------------------
// Logic common to both joysticks
//------------------------------------------------------------------------------

BOOL DoCommonJoystick(int jyc)
    {
    return true;
    }

BOOL DoMastControl(int jyc)
    {
    BOOL fSuccess = true;

    TINE_DIR tineDirLeft  = TINE_DIR_NONE;
    TINE_DIR tineDirRight = TINE_DIR_NONE;
    TINE_LOC tineLocLeft  = TINE_LOC_NONE;
    TINE_LOC tineLocRight = TINE_LOC_NONE;
    MAST_DIR mastDir      = MAST_DIR_NONE;

    if (0)
        {
        }
    //----------------------------------------------------------
    // Tine opening and closing
    //----------------------------------------------------------

    else if (joyBtn(jyc, JOYBTN_1))
        {
        tineDirLeft  = TINE_DIR_RIGHT;
        tineDirRight = TINE_DIR_LEFT;
        }

    else if (joyBtn(jyc, JOYBTN_3))
        {
        tineDirLeft  = TINE_DIR_LEFT;
        tineDirRight = TINE_DIR_RIGHT;
        }
    else if (joyHat(jyc, JOYHAT_LEFT))
        {
        tineDirLeft  = TINE_DIR_LEFT;
        tineDirRight = TINE_DIR_LEFT;
        }

    else if (joyHat(jyc, JOYHAT_RIGHT))
        {
        tineDirLeft  = TINE_DIR_RIGHT;
        tineDirRight = TINE_DIR_RIGHT;
        }

    //----------------------------------------------------------
    // Tine up and down
    //----------------------------------------------------------

    else if (joyBtn(jyc, JOYBTN_2))
        {
        tineLocLeft  = TINE_LOC_DOWN;
        tineLocRight = TINE_LOC_DOWN;
        }

    else if (joyBtn(jyc, JOYBTN_4))
        {
        tineLocLeft  = TINE_LOC_UP;
        tineLocRight = TINE_LOC_UP;
        }

    //----------------------------------------------------------
    // Mast up and down
    //----------------------------------------------------------

    else if (joyBtn(jyc, JOYBTN_LEFTTRIGGER_LOWER))
        {
        mastDir = MAST_DIR_UP;
        }

    else if (joyBtn(jyc, JOYBTN_RIGHTTRIGGER_LOWER))
        {
        mastDir = MAST_DIR_DOWN;
        }

    //----------------------------------------------------------
    // Anchor up and down
    //----------------------------------------------------------

    else if (joyBtn(jyc, JOYBTN_LEFTTRIGGER_UPPER))
	    {
		LockBlackboard();
		SetMotorPower(motorAnchor, 100);
		SendMotorPowers();
		ReleaseBlackboard();
	    }

	else if (joyBtn(jyc, JOYBTN_RIGHTTRIGGER_UPPER))
		{
		LockBlackboard();
		SetMotorPower(motorAnchor, -100);
		SendMotorPowers();
		ReleaseBlackboard();
	    }

    //----------------------------------------------------------
    // Cleanup
    //----------------------------------------------------------

    else
        fSuccess = false;

    //----------------------------------------------------------
    // Having processed the joystick controller, we now adjust
    // the forklift motors and servos to match the indicated intent
    //----------------------------------------------------------

    /*   // Read the tine limit EOPDs
    LockBlackboard();
    int posLeftTine  = eopdLeftTine.value;
    int posRightTine = eopdRightTine.value;
    ReleaseBlackboard();
    TRACE(("ltinepos %d", posLeftTine));
    TRACE(("rtinepos %d", posRightTine));

    // Do limit checks on tine movement
    int leftTineMax  = 2000;  // REVIEW: these variables need to be calibrated
    int rightTineMax = 2000;
    int leftTineMin  = 0;
    int rightTineMin = 0;

    if (posLeftTine > leftTineMax || posLeftTine < leftTineMin)
    {
    tineDirLeft = TINE_DIR_NONE;
    }

    if (posRightTine > rightTineMax || posRightTine < rightTineMin)
    {
    tineDirRight = TINE_DIR_NONE;
    }*/

    // Do limit checks on mast
    /*   int mastMax = 100000; // REVIEW: these need to be calibrated
    int mastMin = 0;
    int mastCur = ReadEncoder(motorForklift) - encMastBottom; // how high is the mast above it's absolute bottom?
    TRACE(("mast %d", mastCur));

    if (mastCur > mastMax || mastCur < mastMin)
    {
    mastDir = MAST_DIR_NONE;
    }

    // Do limit checks on tine movement when mast is up
    if (mastCur > mastMin)
    {
    tineDirLeft  = TINE_DIR_NONE;
    tineDirRight = TINE_DIR_NONE;
    }*/

     /* in case the touch sensor breaks
     if(touchForklift.fvalue)
                {
                TRACE(("touch sensor hit"));
                }*/

    ENCOD encCur;
    ReadEncoder(OUT encCur, motorForklift);

    if (touchForklift.fValue && mastDir == MAST_DIR_DOWN)
        {
        encMastBottom = encCur;
        mastDir = MAST_DIR_NONE;
        //TRACE(("mast limit hit"));
        }

   /* I (Malavika) attempted to change the mast speed control to use the left joystick.
    int speed = joyLeftY(jyc); // getting values from left joystick
    const int sensitivityThreshold = joyThrottleDeadZone; // set dead zone
    int sgnSpeed = Sign(speed);
    speed = Max(0, abs(speed) - sensitivityThreshold);
    speed = speed * sgnSpeed;
    float scaleSpeed = 100.0 / (128.0 - (float)sensitivityThreshold); // scaling down values
    speed = Rounded((float)speed * scaleSpeed, int);
    int map[] =
        {
		 0,  0,  1,  2,  2,  3,  3,  4,  4,  5,
         5,  6,  6,  7,  7,  8,  8,  9,  9, 10,
        10, 11, 11, 12, 12, 13, 13, 14, 14, 15,
        15, 16, 16, 17, 17, 18, 18, 19, 19, 20,
        20, 21, 21, 22, 22, 23, 24, 24, 25, 26,
        27, 28, 29, 30, 31, 32, 33, 34, 35, 37,
        39, 41, 44, 47, 50, 53, 56, 59, 61, 64,
        66, 69, 71, 72, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
        90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
        100
		};
    speed = speed >= 0 ? map[speed] : -map[-speed];*/

    int speed = 100;
    ENCOD encSlow = encMastBottom + 1440 * 3/2;
    if (encCur < encSlow && mastDir==MAST_DIR_DOWN)
        {
        speed = 35;
        // TRACE(("slow down"));
        }


    if(mastDir == MAST_DIR_DOWN)
        {
        //speed = 20;
        speed = -speed;
        }

    // Carry out the orders as specified by the driver and the limit checks.
    OpenCloseTine(svoLeftTineOpenClose,  tineDirLeft);
    OpenCloseTine(svoRightTineOpenClose, tineDirRight);
    UpDownTine(svoLeftTineUpDown,  tineLocLeft);
    UpDownTine(svoRightTineUpDown, tineLocRight);
    UpDownMast(motorForklift, mastDir, speed);

    return fSuccess;
    }

//------------------------------------------------------------------------------
// Logic for the main drive joystick
//------------------------------------------------------------------------------

BOOL DoDriveJoystick(int jyc)
    {
    CheckJoy1ModeChange(jyc, joystick);
    DoManualDrivingControl(jyc, joystick);  // in DriveAids.h
    DoCommonJoystick(jyc);

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

//------------------------------------------------------------------------------
// Logic for the 'arm' joystick, the one for the second driver / other mode.
// Perhaps we could find a better name for that :-).
//------------------------------------------------------------------------------

MILLI msTelemetryBias;
BOOL  fmsTelemetryBiasSet = false;

// Given a displacement on a joystick how far should that move a servo
float ScaleJoystickThrottle(float djoy, float range)
    {
    float scale  = range / (128.0 - (float)joyThrottleDeadZone);
    float result = (float)(abs(djoy) - joyThrottleDeadZone) * scale * sgn(djoy);
    return result;
    }

void DoArmJoystick(int jyc)
    {
    CheckJoy1ModeChange(jyc, joystick);
    DoCommonJoystick(jyc);
    DoMastControl(jyc);

    if (0)
        {
        }
    }

//------------------------------------------------------------------------------
// Main teleop logic
//------------------------------------------------------------------------------

#if 0
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
#endif

void DoTeleOp()
    {
    DisplayMessage("<- tele op ->");
    SetHaltProgramOnMotorStall(false); // in teleop, stall stops are temporary, not fatal

    // Read EOPD sensors on tines so we'll have data we can use to make sure
    // that the tines don't go past their limits. REVIEW: we might consider
    // in future doing this only when the tines are actually in motion, but
    // that's not worth the effort right at the moment.
    // StartReadingEopdSensor(eopdLeftTine);        none yet attached
    // StartReadingEopdSensor(eopdRightTine);       none yet attached

    // Process the joystick messages as they come in!
    for (;;)
        {
        if (getJoystickSettings(joystick))
            {
            /* Do Joystick Controller #1 */
            switch (jyc1Mode)
                {
            case JYC1_MODE_PASSIVE:         break;
            case JYC1_MODE_DRIVE:           DoDriveJoystick(1); break;
            case JYC1_MODE_ARM:             DoArmJoystick(1); break;
                }

            /* Do Joystick Controller #2 */
            switch (jyc2Mode)
                {
            case JYC2_MODE_PASSIVE:         break;
            case JYC2_MODE_ARM:             DoArmJoystick(2); break;
                }
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
