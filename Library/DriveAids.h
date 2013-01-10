//
// DriveAids.h
//
//----------------------------------------------------------------------------------------------
// Configuration
//----------------------------------------------------------------------------------------------

#ifndef TURN_POWER_STRAIGHTEN
#define TURN_POWER_STRAIGHTEN TURN_POWER_FAST
#endif

#ifndef TURN_BALANCE_STRAIGHTEN
#define TURN_BALANCE_STRAIGHTEN TURN_BALANCE
#endif

#ifndef TURN_BALANCE_ADJUSTLATERAL
#define TURN_BALANCE_ADJUSTLATERAL TURN_BALANCE
#endif

//----------------------------------------------------------------------------------------------
// Simple aids
//----------------------------------------------------------------------------------------------

// To do: correct geomerty for left vs right
BOOL DriveForwardsAndStraightenUsingLeftSonic(SONICSENSOR& sonic, float cmDistance, int powerLevel)
// Drive forwards the indicated amount, then straighten using the delta
// in reading on the left sonic sensor. Note: it would be reasonable to
// generalize this to be able to use the right sensor instead: we'd just
// have to turn the other direction.
    {
    TRACE(("StraightenLeft(%f,%d)", cmDistance, powerLevel));
    //
    int  cmSonicStart = ReadSonic_Main(sonic,true);
    TRACE(("cmSonicStart = %d", cmSonicStart));

    BOOL fSuccess     = DriveForwards(cmDistance, powerLevel);

    int  cmSonicCur   = ReadSonic_Main(sonic,true);
    TRACE(("cmSonicCur = %d", cmSonicCur));
    //
    if (fSuccess)
        {
        float dy = (float)cmSonicCur - (float)cmSonicStart;
        //
        ANGLE angle = atan(dy / cmDistance);      // in radians
        angle = oneEightyOverPi * angle;          // to degrees
        TRACE(("straighten = %f", angle));
        //
        fSuccess = TurnRight(-angle, TURN_POWER_STRAIGHTEN, TURN_BALANCE_STRAIGHTEN);
        }
    //
    return fSuccess;
    }

BOOL DriveForwardsAndStraightenUsingRightSonic(SONICSENSOR& sonic, float cmDistance, int powerLevel)
    {
    TRACE(("StraightenRight(%f,%d)", cmDistance, powerLevel));

    int  cmSonicStart = ReadSonic_Main(sonic,true);
    TRACE(("cmSonicStart = %d", cmSonicStart));

    BOOL fSuccess     = DriveForwards(cmDistance, powerLevel);

    int  cmSonicCur   = ReadSonic_Main(sonic,true);
    TRACE(("cmSonicCur = %d", cmSonicCur));
    //
    if (fSuccess)
        {
        float dy = (float)cmSonicCur - (float)cmSonicStart;
        //
        ANGLE angle = atan(dy / cmDistance);      // in radians
        angle = oneEightyOverPi * angle * -1;     // to degrees. REVIEW: why -1? could use a comment documenting :-)....
        TRACE(("straighten %f", angle));
        //
        fSuccess = TurnRight(-angle, TURN_POWER_STRAIGHTEN, TURN_BALANCE_STRAIGHTEN);
        }
    //
    return fSuccess;
    }

BOOL AdjustLaterally(float dcm)
// Adjust our position laterally by the indicated delta. We to this by
// executing a 45deg turn, driving the hypotenuse of the triangle, turning
// back 45deg, then driving back to position.
//
// Note that dcm may be positive or negative.
    {
    RET_IF_FAIL(TurnRight(-45, TURN_POWER_FAST, TURN_BALANCE_ADJUSTLATERAL),   "TurnRight");
    RET_IF_FAIL(DriveForwards(-sqrtTwo * dcm, DRIVE_POWER_SLOW),               "DriveForwards");
    RET_IF_FAIL(TurnRight(45, TURN_POWER_FAST, TURN_BALANCE_ADJUSTLATERAL),    "TurnBack");
    RET_IF_FAIL(DriveForwards(dcm, DRIVE_POWER_SLOW),                          "DriveBackwards");
    //
    return true;
    }

BOOL AdjustLaterallyUsingAngle(float dcm, ANGLE degAngle)
    {
    float radAngle   = degreesToRadians(degAngle);
    float hypotenuse = dcm / sin(radAngle);
    float leg        = dcm * cos(radAngle) / sin(radAngle);

    // Refuse to drive way too far to do the adjustment
    if (hypotenuse > 30)
        return false;

    RET_IF_FAIL(TurnRight(-degAngle, TURN_POWER_FAST, TURN_BALANCE_ADJUSTLATERAL),   "TurnRight");
    RET_IF_FAIL(DriveForwards(hypotenuse, DRIVE_POWER_SLOW),                         "DriveForwards");
    RET_IF_FAIL(TurnRight(degAngle, TURN_POWER_FAST, TURN_BALANCE_ADJUSTLATERAL),    "TurnBack");
    RET_IF_FAIL(DriveForwards(leg, DRIVE_POWER_SLOW),                                "DriveBackwards");

    return true;
    }

//----------------------------------------------------------------------------------------------
// Manual driving
//----------------------------------------------------------------------------------------------

#if USE_JOYSTICK_DRIVER

#if ROBOT_NAME==ROBOT_NAME_OMNI_BOT

void DoManualDrivingControl(int joy, TJoystick& joystick)
    {
    int ctlMoveX = joyLeftX(joy);
    int ctlMoveY = joyLeftY(joy);      // -128 to  127
    int ctlTurn = -joyRightX(joy);     //  128 to -127

    // Implement the deadzone in the middle
    const int sensitivityThreshold = 15;
    int sgnMoveX = Sign(ctlMoveX);
    int sgnMoveY = Sign(ctlMoveY);
    int sgnTurn = Sign(ctlTurn);
    ctlMoveX = Max(0, abs(ctlMoveX) - sensitivityThreshold);
    ctlMoveY = Max(0, abs(ctlMoveY) - sensitivityThreshold);
    ctlTurn = Max(0, abs(ctlTurn) - sensitivityThreshold);
    ctlMoveX = ctlMoveX * sgnMoveX;
    ctlMoveY = ctlMoveY * sgnMoveY;
    ctlTurn = ctlTurn   * sgnTurn;

    // scale to +- 100
    float scale = 50.0 / (128.0 - (float)sensitivityThreshold);
    ctlMoveX = Rounded((float)ctlMoveX * scale, int);
    ctlMoveY = Rounded((float)ctlMoveY * scale, int);
    ctlTurn  = Rounded((float)ctlTurn  * scale, int);

    int powerLeftFront  = -ctlMoveY -ctlMoveX -ctlTurn;
    int powerRightFront =  ctlMoveY -ctlMoveX -ctlTurn;
    int powerLeftBack   = -ctlMoveY +ctlMoveX -ctlTurn;
    int powerRightBack  =  ctlMoveY +ctlMoveX -ctlTurn;

    LockBlackboard();
    SetMotorPower(motorLeftFront,  powerLeftFront);
    SetMotorPower(motorRightFront, powerRightFront);
    SetMotorPower(motorLeftBack,   powerLeftBack);
    SetMotorPower(motorRightBack,  powerRightBack);
    SendMotorPowers();
    ReleaseBlackboard();
    }

#else

void DoManualDrivingControl(int joy, TJoystick& joystick)
// Interpret the joysticks and manually drive the bot
    {
    // This is a map that is used to provide much more control over the low range speeds (inverse log table)...

#if ((ROBOT_NAME == ROBOT_NAME_TWO_MOTORS_NO_ENCODERS) || (ROBOT_NAME == ROBOT_NAME_TWO_MOTORS_WITH_ENCODERS))
    // base: empirically tweaked inverse log transfer function
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

/*#elif 0                                         May use later
    // base function < 50, linear > 50
    int map[] =
        {
         0,  1,  1,  1,  2,  2,  2,  2,  3,  3,
         3,  3,  4,  4,  4,  5,  5,  5,  6,  6,
         6,  7,  7,  7,  8,  8,  8,  9,  9,  9,
        10, 10, 10, 11, 11, 11, 12, 12, 13, 13,
        14, 14, 15, 15, 16, 16, 17, 17, 18, 18,
		50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
		60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
		70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
		90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
        100
        };
#elif 0
    // base function < 50, linear > 75, spline between
    int map[] =
        {
         0,  1,  1,  1,  2,  2,  2,  2,  3,  3,
		 3,  3,  4,  4,  4,  5,  5,  5,  5,  6,
		 6,  6,  7,  7,  7,  8,  8,  8,  9,  9,
		10, 10, 10, 11, 11, 11, 12, 12, 13, 13,
		14, 14, 14, 15, 15, 16, 16, 17, 17, 18,
		18, 19, 20, 21, 23, 25, 27, 30, 32, 35,
		38, 41, 44, 47, 50, 53, 56, 59, 61, 64,
		66, 69, 71, 72, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
		90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
		100
        };
*/
#else
    // The bottom half of the previous table was adjusted
    // to give Sam more power at lower speeds
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
#endif

    // Extract values from the joysticks that we find useful
    int ctlPower    =  joyLeftY(joy);      // -128 to  127
    int ctlSteering =  -joyRightX(joy);     //  128 to -127

    // Remove sensitivity in the middle of the controls.
    // At the same time, avoid a big control jump at the
    // edge of the dead zone.
    const int sensitivityThreshold = joyThrottleDeadZone;
    int sgnPower    = Sign(ctlPower);
    int sgnSteering = Sign(ctlSteering);

    ctlPower    = Max(0, abs(ctlPower)    - sensitivityThreshold);
    ctlSteering = Max(0, abs(ctlSteering) - sensitivityThreshold);

    ctlPower    = ctlPower    * sgnPower;
    ctlSteering = ctlSteering * sgnSteering;

    // Convert the range of controls from +-128 to +-100. Do
    // so symmetrically for both positive and negative numbers.
    float scalePower = 100.0 / (128.0 - (float)sensitivityThreshold);
    float scaleSteering = 100.0 / (128.0 - (float)sensitivityThreshold);
    ctlPower    = Rounded((float)ctlPower    * scalePower, int);
    ctlSteering = Rounded((float)ctlSteering * scaleSteering, int);
    // if (ctlPower != 0 || ctlSteering != 0) {  TRACE(("power=%d steering=%d", ctlPower, ctlSteering));

    ctlPower    =    ctlPower >= 0 ? map[ctlPower]    : -map[-ctlPower];
    ctlSteering = ctlSteering >= 0 ? map[ctlSteering] : -map[-ctlSteering];

    if (true) // set to false to disable
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
	    }

    // Update the motor power. The SetMotorPower internals will
    // clamp the power provided to +-100.
    int16 powerLeft  = ctlPower - ctlSteering;
    int16 powerRight = ctlPower + ctlSteering;

    // Correct the power balance to the wheels in order to better drive straight
    float balance = BalanceFromDirection(ctlPower >= 0 ? FORWARD : BACKWARD);
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
#endif
