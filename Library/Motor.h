//
// Motor.h
//
// Implementation of motor functionality.

#define ControllerOfMotor(motor)                rgmotorctlr[motor.imotorctlr]
#define ControllerFieldOfMotor(motor,field)     ControllerOfMotor(motor).field
#define MtrOf(motor)                            ControllerOfMotor(motor).rgmtr[motor.imtr]

#define IsLeftMotor(motor)                      (motor.imotor == motorLeft.imotor  && motorLeft.fActive)
#define IsRightMotor(motor)                     (motor.imotor == motorRight.imotor && motorRight.fActive)

void StopLegoMotor(int imtr)
    {
    motor[imtr] = 0;
    }

void InitializeMotor(IN OUT STICKYFAILURE& fOverallSuccess, MOTOR& motor, MOTORCONTROLLER& controllerParam, ubyte jmtr /*one based*/, string displayNameParam, int prop)
    {
    BOOL fSuccess = true;
    LockDaisy();

    InitializeLegoControllerIfNecessary();

    motor.imotorPaired = -1;

    /* Figure out which index this motor is in the rgmotor array */
    motor.imotor = -1;
    int i = 0;
    while (rgmotor[i].imotor >= 0)
        i++;
    motor.imotor = i;

    // Remember (one more than) the last value we see
    if (imotorMac <= i)
        imotorMac = i+1;

    motor.imotorctlr    = controllerParam.imotorctlr;
    motor.imtr          = jmtr-1;
    motor.displayName   = displayNameParam;
    motor.encStallPrev  = 0;
    motor.msLastOkStall = 0;
    motor.msLastEncStall = 0;
    MtrOf(motor).power  = 0;
    motor.fReflected    = !!(MOTORPROP_REFLECTED & prop);
    if (motor.fReflected)
        {
        MtrOf(motor).mode |= MOTORMODE_REFLECTED;
        }

    motor.fActive = true;
    MtrOf(motor).fActive = true;

    motor.powerScaling = 1.0;

    motor.fHasEncoder   = !!(MOTORPROP_ENCODER & prop) || ControllerOfMotor(motor).fLegoController;
    motor.encoder       = 0;
    motor.fDoStallCheck = (motor.fHasEncoder && !(MOTORPROP_NOSTALLCHECK & prop));

    SendMotorModePower(fSuccess, ControllerOfMotor(motor));
    waitForMotorControllerCommandCycle1(ControllerOfMotor(motor));

    if (controllerParam.fLegoController)
	    {
	    StopLegoMotor(motor.imtr);
	    }

    ReleaseDaisy();
    if (fOverallSuccess) fOverallSuccess = fSuccess;
    TraceInitializationResult1("motor[%s]", displayNameParam, fOverallSuccess);
    }

void ZeroEncoders(int imotorMask=0xFFFF)
// Zero the encoders of the motors indicated in the mask.
// REVIEW: do we need the blackboard lock for this guy?
    {
    LockDaisy();
    BOOL fSuccess = true;

    BOOL      rgfSent[imotorctlrMax]; memset(rgfSent, false, sizeof(rgfSent));
    MOTORMODE rgmodePrev[imotorMax];

    // Reset the encoders on all the Tetrix motors and zero the encoders on lego motors
    //
    BOOL fNonLego = false;
    for (int imotor = 0; imotor < imotorMac; imotor++)
        {
        if (!rgmotor[imotor].fActive) continue;
        if (imotorMask & (1<<imotor))
            {
            if (ControllerOfMotor(rgmotor[imotor]).fLegoController)
                {
                nMotorEncoder[rgmotor[imotor].imtr] = 0;
                // Remember that we zero'd the guy
                MtrOf(rgmotor[imotor]).encoder = 0;
                rgmotor[imotor].encoder = 0;
                }
            else
                {
                fNonLego = true;
                SetControllerMtrRunMode(OUT rgmodePrev[imotor], ControllerOfMotor(rgmotor[imotor]), rgmotor[imotor].imtr, MOTORMODE_RESET_CURRENT_ENCODER);
                }
            }
        }

    // Send things out to the tetrix motor controllers
    if (fNonLego)
        {
        for (int imotor = 0; imotor < imotorMac; imotor++)
            {
            if (!rgmotor[imotor].fActive) continue;
            if (imotorMask & (1<<imotor))
                {
                if (!ControllerOfMotor(rgmotor[imotor]).fLegoController)
                    {
                    if (!rgfSent[ControllerOfMotor(rgmotor[imotor]).imotorctlr])
                        {
                        rgfSent[ControllerOfMotor(rgmotor[imotor]).imotorctlr] = true;
                        SendMotorModePower(fSuccess, ControllerOfMotor(rgmotor[imotor]));
                        }
                    }

                // Remember that we zero'd the guy
                MtrOf(rgmotor[imotor]).encoder = 0;
                rgmotor[imotor].encoder = 0;
                }
            }
        waitForMotorControllerCommandCycle0();
        }

    // Restore the previous modes
    fNonLego = false; memset(rgfSent, false, sizeof(rgfSent));
    for (int imotor = 0; imotor < imotorMac; imotor++)
        {
        if (!rgmotor[imotor].fActive) continue;
        if (imotorMask & (1<<imotor))
            {
            if (!ControllerOfMotor(rgmotor[imotor]).fLegoController)
                {
                fNonLego = true;
                MtrOf(rgmotor[imotor]).mode = rgmodePrev[imotor];
                }
            }
        }

    // Send things out to the tetrix motor controllers
    if (fNonLego)
        {
        for (int imotor = 0; imotor < imotorMac; imotor++)
            {
            if (!rgmotor[imotor].fActive) continue;
            if (imotorMask & (1<<imotor))
                {
                if (!ControllerOfMotor(rgmotor[imotor]).fLegoController)
                    {
                    if (!rgfSent[ControllerOfMotor(rgmotor[imotor]).imotorctlr])
                        {
                        rgfSent[ControllerOfMotor(rgmotor[imotor]).imotorctlr] = true;
                        SendMotorModePower(fSuccess, ControllerOfMotor(rgmotor[imotor]));
                        }
                    }
                }
            }
        waitForMotorControllerCommandCycle0();
        }

    ReleaseDaisy();
    }

void ZeroEncoders()
    {
    ZeroEncoders( (1<<motorLeft.imotor) | (1<<motorRight.imotor));
    }

#define ALL_MOTORS_MASK 0xFFFF

#define ReadEncoders(imotorMask, imotorctlrMask)    \
	{                                               \
	LockBlackboard();                               \
	ReadEncoders_(imotorMask, imotorctlrMask);      \
	ReleaseBlackboard();                            \
	}

void ReadEncoders_(int imotorMask, OUT int& imotorctlrMask)
// Update the MtrOf(motor).encoder values of all the indicated motors. Return
// a mask of all the contollers that we touched.
    {
    CheckLockHeld(lockBlackboard);

    imotorctlrMask = 0;
    BOOL rgfRead[imotorctlrMax]; memset(rgfRead, false, sizeof(rgfRead));

    LockDaisy();
    for (int imotor = 0; imotor < imotorMac; imotor++)
        {
        if (!rgmotor[imotor].fActive) continue;
        if (!rgmotor[imotor].fHasEncoder) continue;
        if (imotorMask & ((int)1<<imotor))
            {
            int imotorctlr = rgmotor[imotor].imotorctlr;
            if (!rgfRead[imotorctlr])
                {
                BOOL fSuccess = false;
                // If the motor controller isn't active, then we'll just skip it rather than do an infinite loop
                if (rgmotorctlr[imotorctlr].fActive)
                    {
	                while (true)
	                    {
	                    ReadControllerEncoders(OUT fSuccess, rgmotorctlr[imotorctlr]);
	                    if (fSuccess)
	                        {
	                        imotorctlrMask |= ((int)1 << imotorctlr);
	                        break;
	                        }
	                    ReleaseDaisy();
	                    EndTimeSlice();
	                    LockDaisy();
	                    }
	                  }
                rgfRead[imotorctlr] = true;
                }
            rgmotor[imotor].encoder = MtrOf(rgmotor[imotor]).encoder;
            }
        }
    ReleaseDaisy();
    }

#define ReadEncoder(enc, motor)                   \
	{                                               \
	LockBlackboard();                               \
	ReadEncoder_(enc, motor);                       \
	ReleaseBlackboard();                            \
	}

void ReadEncoder_(OUT ENCOD& enc, MOTOR& motor)
// Read the encoder of the indicated motor
    {
    int imotorctlrMask;
    ReadEncoders_((int)1 << motor.imotor, OUT imotorctlrMask);
    enc = MtrOf(motor).encoder;
    }

#define ReadLeftRightEncoders(encLeft, encRight)    \
	{                                               \
	LockBlackboard();                               \
	ReadLeftRightEncoders_(encLeft, encRight);      \
	ReleaseBlackboard();                            \
	}

void ReadLeftRightEncoders_(OUT ENCOD& encLeft, OUT ENCOD& encRight)
// Read the encoders of the left and right motors
    {
    int imotorctlrMask;
    ReadEncoders_( (1<<motorLeft.imotor) | (1<<motorRight.imotor), OUT imotorctlrMask);
    encLeft  = MtrOf(motorLeft).encoder;
    encRight = MtrOf(motorRight).encoder;
    }

//---------------------------------------------------------------------------------------
// Managing motor power levels
//---------------------------------------------------------------------------------------

// This needs to change according to whether or not we need to do manual
// reversing of the motor power and encoder values or whether we've managed
// to get the motor controller to do that for us.
#define InternalPowerForMotor(motor, power)     (power)


// The documentation to the HiTechnic Motor Controller has the following to say about
// how it interprets power levels:
//
//      This field may be set in the range of -100 to +100. 0 is used to set Off/Brake.
//      Any value above 100 will be treated as 100, except –128 which is used to set
//      Off/Float. Negative values run the motor in the reverse direction. The power
//      should be set positive when being used as a parameter for the 'Run to position'
//      command. This field sets the rotation rate in 'Run with constant speed' and maximum
//      rotation rate in 'Run to position' in the range of -1000 – +1000 degrees per second
//      represented by the range -100 – +100. As with 'PWM mode', 0 is used to set Off/Brake
//      while –128 is used to set Off/Float.
//
// We here use motors in the 'Run with constant speed' mode (see MOTORMODE_RUN_WITH_CONSTANT_SPEED).
// Thus, our power levels are interpreted as a requested rotation rate in units of tens of
// degrees per second: power==10 -> 100 deg/s, power==50 -> 500 deg/s, etc.
//
// That's the requested speed. However, on some robots it has been observed that, due to friction,
// etc, the maximum speed that can be achieved on one or more of its motors is somewhat less than
// 1000 deg/s. If one of the motors has significantly less such friction that the other, then this
// can cause problems when the motors are both commanded to go at, say, a power level of 100: the
// right motor (say) may actually be able to achieve a speed of 1000 deg/s, whereas the left motor
// may max out at 720 deg/s, causing the robot to veer left when a straight-ahead motion was
// expected.
//
// This issue is exacerbated by fluctuating power levels.
//
// This issue could be addressed by simply using lower power-levels all around in higher levels
// of the software. While viable, this approach is tedious.
//
// As an alternative, we provide here the motor.powerScaling variable. This floating point value is
// used to compress the normal [-100,100] power range to a smaller one (or possibly a larger one
// with a clipped upper range, though that would be weird). In our example above, setting the
// value of motor.powerScaling to 0.72 would avoid maxing out either motor, resulting in straighter
// driving behaviour, though at the cost, of course, of somewhat reduced overall speed.
//
// The motor.powerScaling variable bears a conceptual resemblance to the (non-functional, documentation
// to the contrary notwithstanding) RobotC built-in variable nMaxRegulatedSpeed12V.

void SetMotorPower(MOTOR& motor, int powerArg)
// Record the desire that this motor have the indicated power level. Note that this
// doesn't actually take effect until a subsequent SendMotorPowers().
//
// Note that the blackboard lock is (currently) required for calling this function,
// though that should reasonably change to be the daisy lock.
    {
    CheckLockHeld(lockBlackboard);

    short power_ = Rounded((float)powerArg * motor.powerScaling, short);
    ClampVar(power_, -100, 100);
    RecordMotorPower(
            motor.imotorctlr,
            motor.imtr,
            InternalPowerForMotor(motor,power_));
    if (motor.imotorPaired != -1)
        {
        RecordMotorPower(
            rgmotor[motor.imotorPaired].imotorctlr,
            rgmotor[motor.imotorPaired].imtr,
            InternalPowerForMotor(rgmotor[motor.imotorPaired], power_));
        }
    }

// Send the current power levels to all the active controllers.
#define SendMotorPowers()                                                       \
    {                                                                           \
    BOOL fSuccess = true;                                                       \
    LockDaisy();                                                                \
    for (int imotorctlr = 0; imotorctlr < imotorctlrMax; imotorctlr++)          \
        {                                                                       \
        SendMotorPower(OUT fSuccess, rgmotorctlr[imotorctlr]);                  \
        }                                                                       \
    ReleaseDaisy();                                                             \
    }

void SendOneMotorPower(MOTOR& motor, int power)
	{
	LockBlackboard();
	SetMotorPower(motor, power);
	SendMotorPowers();
	ReleaseBlackboard();
	}

void StopRobot()
// Halt all the motors on the robot. REVIEW: should we have a variation that
// only stopped the *drive* motors?
    {
    LockBlackboard();
    for (int imotor=0; imotor < imotorMac; imotor++)
        {
        SetMotorPower(rgmotor[imotor],0);
        }
    SendMotorPowers();
    ReleaseBlackboard();
    }

//---------------------------------------------------------------------------------------
// Stall detection logic: avoiding motor burnout
//---------------------------------------------------------------------------------------

// Our behaviour when we encounter a motor stall can be adjusted

typedef enum MOTOR_STALL_BEHAVIOR
	{
    MOTOR_STALL_BEHAVIOR_ABORT_PROGRAM,
    MOTOR_STALL_BEHAVIOR_REINIT_MOTORS,
    MOTOR_STALL_BEHAVIOR_ONLY_SET_FLAG,
	} MOTOR_STALL_BEHAVIOR;

MOTOR_STALL_BEHAVIOR motorStallBehavior = MOTOR_STALL_BEHAVIOR_ABORT_PROGRAM;
BOOL fMotorStallDetected = false;

// A historical legacy API for the situation where we could only abort or reinit
void SetHaltProgramOnMotorStall(bool fHalt)
    {
    if (fHalt)
        motorStallBehavior = MOTOR_STALL_BEHAVIOR_ABORT_PROGRAM;
    else
        motorStallBehavior = MOTOR_STALL_BEHAVIOR_REINIT_MOTORS;
    }

MILLI msLastMotorStallCheck = 0;
MILLI msLastMotorControllerTickle = 0;

// Does this motor effectively not have enough power to be worried about a stall thereon?
#define FMotorNotPoweredStallCheck(motor)   (abs(MtrOf(motor).power) <= 5)

// Check for motor stall, and 'abort' if stall is detected.
// Further, be sure in all cases to tickle all the active
// motor controllers, lest they time out and reset themselves.
void CheckForMotorStall(MILLI msNow)
    {
    BOOL fFirstTime = (0 == msLastMotorStallCheck);
    /* We have a throttle on how often we check for stall due to a worry about reading the motor encoders too frequently (eh?) */
    const int msStallCheckInterval = 200;   /* 200 is just a rule of thumb */
    if (fFirstTime || msNow > msLastMotorStallCheck + msStallCheckInterval)
        {
        // Loop through all the motors, seeing if any have stalled
        //
        BOOL fAnyStalled = false;
        int imotorctlrMask;
        ReadEncoders(ALL_MOTORS_MASK, OUT imotorctlrMask);    // returns which motor controllers it touched
        for (int imotor = 0; imotor < imotorMac; imotor++)
            {
            // Simple check of some static properties that only are set during motor initialization
            if (!rgmotor[imotor].fActive) continue;
            if (!rgmotor[imotor].fDoStallCheck) continue;

            const int msAbortStall = 100;   //750 orig

            // The motor is ok if this is the first time through, it doesn't have enough power to worry about,
            // or it's moved since the last time we checked.
            BOOL fOK = fFirstTime
              || rgmotor[imotor].msLastOkStall == 0
              || FMotorNotPoweredStallCheck(rgmotor[imotor])
              || rgmotor[imotor].encStallPrev != MtrOf(rgmotor[imotor]).encoder;
            //
            if (fOK)
                {
                rgmotor[imotor].msLastOkStall = msNow;
                }
            else
                {
                MILLI dms = msNow - rgmotor[imotor].msLastOkStall;
                if (dms > msAbortStall)
                    {
                    fAnyStalled = true;
                    TRACE(("stall: %dms %s %d", dms, rgmotor[imotor].displayName, rgmotor[imotor].msLastOkStall));
                    TRACE((" prev: %d",  rgmotor[imotor].encStallPrev));
                    TRACE(("  cur: %d",  MtrOf(rgmotor[imotor]).encoder));
                    TRACE((" batt: %fv", vExternalBattery));
                    }
                }

            rgmotor[imotor].encStallPrev = MtrOf(rgmotor[imotor]).encoder;
            }
        //
        // If any have stalled, then deal with that. We first stop the robot, then we either abort
        // the program entirely or wait a little while to see if the problem goes away.
        //
        if (fAnyStalled)
            {
            hogCpuNestable();  /* paranoia: we don't want another task to restart the motors after we turn them off */

            PlayFifthNoWait();

            switch (motorStallBehavior)
	            {
            case MOTOR_STALL_BEHAVIOR_ABORT_PROGRAM:
                StopRobot();       /* REVIEW: is this too much? Do we just want to stop some subset of the motors? */
                StopAllTasks();
                break;

            case MOTOR_STALL_BEHAVIOR_REINIT_MOTORS:
                StopRobot();       /* REVIEW: is this too much? Do we just want to stop some subset of the motors? */
                wait1Msec(300);

                // Reinit the motors after the stall in an attempt to diagnose odd
                // bug seen in pushing war wherein motors appears to lose config
                // and so, e.,g, we don't know which motors are to be reversed.
                STICKYFAILURE fOverallSuccess = true;
                InitializeMotors(fOverallSuccess);
                break;

            case MOTOR_STALL_BEHAVIOR_ONLY_SET_FLAG:
                fMotorStallDetected = true;
                //
                // Don't immediately retrigger a check
                //
                msLastMotorStallCheck = 0;
                break;
                }

            releaseCpuNestable();
            }

        /* Tickle motor contollers that haven't be tickled by ReadEncoders. */
        /* But we only have to avoid the 2.5s timeout.                      */
        const int msMotorControllerTickleInterval = 1000;
        if (msNow > msLastMotorControllerTickle + msMotorControllerTickleInterval)
            {
            LockDaisy();
            for (int imotorctlr = 0; imotorctlr < imotorctlrMac; imotorctlr++)
                {
                if (rgmotorctlr[imotorctlr].fActive && !(imotorctlrMask & (1 << imotorctlr)))
                    {
                    TouchMotorController(rgmotorctlr[imotorctlr]);
                    }
                }
            ReleaseDaisy();
            msLastMotorControllerTickle = msNow;
            }

        msLastMotorStallCheck = msNow;
        }
    }
