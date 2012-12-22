//
// TeleOp.h
//

          //\\
         //  \\
        //    \\
       //======\\
      //\\    //\\
     //  \\  //  \\
    //    \\//    \\
   //==============\\

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
bool LeftTriggerLower = false;

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

//put TYPEDEF ENUMS HERE

//fUNCTIONS HERE

//#define REDEF_SLOW_MODE
#ifdef REDEF_SLOW_MODE
#define ALLOW_SLOW_MODE 1
#define MAP_LENGTH 101
int mapHermanTheTurtle[MAP_LENGTH];

void scaleHerman(float scale)
{
	int i;
	for (i = 0; i < 36; ++i)
	{
		mapHermanTheTurtle[i] = (int)(0.5 + 0.3 * scale * (i - 0));
	}
	for (; i < 65; ++i)
	{
		mapHermanTheTurtle[i] = (int)(11.0 + 0.5 * scale * (i - 36));
	}
	for (; i < 75; ++i)
	{
		mapHermanTheTurtle[i] = (int)(26.3 + (2 / (float)3) * scale * (i - 65));
	}
	for (; i < 89; ++i)
	{
		mapHermanTheTurtle[i] = (int)(33 + (1 / (float)1) * scale * (i - 75));
  }
	for (; i < 96; ++i)
	{
		mapHermanTheTurtle[i] = (int)(49 + (13 / (float)2) * scale * (i - 89));
	}
	for (; i < 100; ++i)
	{
		mapHermanTheTurtle[i] = (int)(72.5 + (8 / (float)1) * scale * (i - 96));
	}
	for (; i < MAP_LENGTH; ++i)
	{
		mapHermanTheTurtle[i] = (int)(100 * scale);
	}

/*push @test, int(( 11.0 + ( 1/ 2) * (@test -  36)) * $scale) for ( 36..64);
push @test, int(( 26.3 + ( 2/ 3) * (@test -  65)) * $scale) for ( 65..74);
push @test, int(( 33   + ( 1/ 1) * (@test -  75)) * $scale) for ( 75..88);
push @test, int(( 49   + ( 3/ 1) * (@test -  89)) * $scale) for ( 89..95);
push @test, int(( 72.5 + (13/ 2) * (@test -  96)) * $scale) for ( 96..99);
push @test, int(( 100  + ( 8/ 1) * (@test - 100)) * $scale) for (100..100);*/
}
#else
#define ALLOW_SLOW_MODE 1
    int mapHermanTheTurtle[] =
        {
         0,  0,  0,  0,  1,  1,  1,  1,  1,  2,
         2,  2,  2,  2,  2,  3,  3,  3,  3,  3,
         4,  4,  4,  4,  4,  4,  5,  5,  5,  5,
         5,  5,  6,  6,  6,  6,  6,  6,  7,  7,
         7,  8,  8,  8,  9,  9,  9,  9, 10, 10,
        10, 11, 11, 11, 12, 12, 12, 12, 13, 13,
        13, 14, 14, 14, 15, 15, 16, 16, 16, 17,
        17, 18, 18, 18, 19, 19, 19, 19, 19, 19,
        19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
        19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
        20};
#endif


//------------------------------------------------------------------------------
// Logic common to both joysticks
//------------------------------------------------------------------------------

BOOL DoCommonJoystick(int jyc)
    {
    return true;
    }

void DoMastControl(int jyc)
    {
    //DEFINE VARIABLES here

    if (0)
        {
        }
    //----------------------------------------------------------
    // Button pressing operations for second controller
    //---------------------------------------------------------
 	  /*else if (joyBtn(jyc, JOYBTN_RIGHTTRIGGER_LOWER))
		  {
		  Beep(NOTE_G_FLAT);
		  }*/
		/*else if (joyBtn(jyc, JOYBTN_LEFTTRIGGER_LOWER))
		{
		 MoveServo(svoLatch, svposLatch, true);
		}
		else if (joyBtn(jyc, JOYBTN_B))
		{
		  MoveServo(svoLatch, svposLatchTurnBack, true);
		}*/
		else if (joyBtn(jyc, JOYBTN_Y))
		{
		  svposPuller += 5;
		  MoveServo(svoPuller, svposPuller, true);
		  MoveServo(svoPuller2, 255 - svposPuller, true);
		  //TRACE(("mds"));*/
		}
		else if (joyBtn(jyc, JOYBTN_X))
		{
		  svposPuller -= 5;
		  MoveServo(svoPuller, svposPuller, true);
		  MoveServo(svoPuller2, 255 - svposPuller, true);
		  //TRACE(("asd"));*/
		}
		else if (joyHat(jyc, JOYHAT_UP))
		{
		  svposWrist += 10;
		  MoveServo(svoWrist, svposWrist, true);
		  MoveServo(svoWrist2, 255 - svposWrist, true);
		  TRACE(("bye"));
		}
		else if (joyHat(jyc, JOYHAT_DOWN))
		{
		  svposWrist -= 10;
		  MoveServo(svoWrist, svposWrist, true);
		  MoveServo(svoWrist2, 255 - svposWrist, true);
		  TRACE(("hi"));
		}

		int jycRightY = joyRightY(jyc);
		//int scale = (int)(100.0 / 128.0);
		//jycRightY = Rounded(jycRightY * scale, int);
		jycRightY = Rounded(jycRightY / 4, int);
		LockBlackboard();
		SetMotorPower(motorArm, jycRightY);
		SendMotorPowers();
		ReleaseBlackboard();

		if (joyBtn(jyc, JOYBTN_LEFTTRIGGER_LOWER))
		{
		  LockBlackboard();
		  SendOneMotorPower(motorRamp, 75);
		  ReleaseBlackboard();
		}
		else if (joyBtn(jyc, JOYBTN_RIGHTTRIGGER_LOWER))
		{
		  LockBlackboard();
		  SendOneMotorPower(motorRamp, -75);
		  ReleaseBlackboard();
		}
		else
	  {
	    LockBlackboard();
	    SendOneMotorPower(motorRamp, 0);
	    ReleaseBlackboard();
	  }

	  /*if (joyHat(jyc, JOYHAT_RIGHT))
	  {
	    SendOneMotorPower(motorArm, 75);
	  }
	  else if (joyHat(jyc, JOYHAT_LEFT))
	  {
	    SendOneMotorPower(motorArm, -75);
	  }
	  else
	  {
	    SendOneMotorPower(motorArm, 0);
	  }*/


    //----------------------------------------------------------
    // Cleanup
    //----------------------------------------------------------



    }

//------------------------------------------------------------------------------
// Logic for the main drive joystick
//------------------------------------------------------------------------------

void ManualDrivingControl(int joy, TJoystick& joystick)
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
		     0,  1,  2,  2,  3,  3,  4,  4,  5,  5,
         5,  6,  6,  7,  7,  8,  8,  9,  9, 10,
        10, 10, 10, 11, 11, 11, 12, 12, 14, 14,
        14, 16, 16, 17, 17, 17, 18, 19, 19, 19,
        20, 21, 21, 22, 22, 22, 24, 24, 25, 25,
        26, 26, 27, 27, 28, 28, 29, 29, 30, 30,
        31, 31, 32, 32, 33, 33, 34, 34, 35, 35,
        36, 36, 37, 38, 39, 40, 41, 43, 45, 47,
        49, 51, 54, 57, 60, 63, 66, 70, 73, 76,
        80, 83, 87, 90, 94, 95, 96, 97, 98, 99,
        100
		};
#endif
#define DoManual
#ifdef DoManual

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

    if (false) // set to false to disable
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
    if ((abs(powerLeft) > 100)||(abs(powerRight) > 100))
    {
      int SgnPowerLeft = Sign(powerLeft);
      int SgnPowerRight = Sign(powerRight);
      powerLeft = abs(powerLeft);
      powerRight = abs(powerRight);
      if (powerLeft > powerRight)
      {
        powerRight *= (100/powerLeft);
        powerLeft *= (100/powerLeft);
      }
      else
      {
        powerLeft *= (100/powerRight);
        powerRight *= (100/powerRight);
      }
      powerLeft *= SgnpowerLeft;
      powerRight *= SgnpowerRight;
    }

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
#endif
    }

    int16 min(int16 a, int16 b)
  {
    return a <= b ? a : b;
  }

    int16 max(int16 a, int16 b)
  {
    return a >= b ? a : b;
  }

 void DoManualTankDrivingControl(int joy, TJoystick& joystick, bool MapChange)
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
    int ctlLeft  =  joyLeftY(joy);      // -128 to 127
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
    ctlLeft  = Rounded((float)ctlLeft  * scaleLeft, int);
    ctlRight = Rounded((float)ctlRight * scaleRight, int);
    // if (ctlPower != 0 || ctlSteering != 0) {  TRACE(("power=%d steering=%d", ctlPower, ctlSteering));

    if (ALLOW_SLOW_MODE && MapChange)
    {

        ctlLeft  = ctlLeft  >= 0 ? mapHermanTheTurtle[ctlLeft]  : -mapHermanTheTurtle[-ctlLeft];
        ctlRight = ctlRight >= 0 ? mapHermanTheTurtle[ctlRight] : -mapHermanTheTurtle[-ctlRight];
         if (ctlLeft < 0 || ctlRight < 0)
          TRACE(("%d %d", ctlLeft, ctlRight));
    }
    else
    {
        ctlLeft  = ctlLeft  >= 0 ? map[ctlLeft]  : -map[-ctlLeft];
        ctlRight = ctlRight >= 0 ? map[ctlRight] : -map[-ctlRight];
    }
    /*if (MapChange)
    {
    ctlLeft  = min((int16)(sizeof(mapHermanTheTurtle) / 4), max(ctlLeft, 0));
    ctlRight = min((int16)(sizeof(mapHermanTheTurtle) / 4), max(ctlRight, 0));
          ctlLeft    =    ctlLeft >= 0 ? mapHermanTheTurtle[ctlLeft]    : -mapHermanTheTurtle[-ctlLeft];
    ctlRight = ctlRight >= 0 ? mapHermanTheTurtle[ctlRight] : -mapHermanTheTurtle[-ctlRight];
    }
    else
    {
    ctlLeft  = min((int16)(sizeof(map) / 4), max(ctlLeft, 0));
    ctlRight = min((int16)(sizeof(map) / 4), max(ctlRight, 0));*/
    /*ctlLeft    =    ctlLeft >= 0 ? map[ctlLeft]    : -map[-ctlLeft];
    ctlRight = ctlRight >= 0 ? map[ctlRight] : -map[-ctlRight];*/
     //}

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
    int powerLeft  = ctlLeft;
    int powerRight = ctlRight;

    // Correct the power balance to the wheels in order to better drive straight
    // Disabled because we need to be smarter regarding FORWARD vs BACKWARD
    // in this tank drive logic here and it's just not important enough.
    // float balance = BalanceFromDirection(ctlLeft >= 0 ? FORWARD : BACKWARD);
    // BalancePower(powerLeft, powerRight, balance);

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
    if (joyBtn(jyc, JOYBTN_LEFTTRIGGER_LOWER))
    {
      LeftTriggerLower = true;
    }
    else
    {
      LeftTriggerLower = false;
    }

    CheckJoy1ModeChange(jyc, joystick);
    if(joyBtn(jyc, JOYBTN_RIGHTTRIGGER_LOWER))
    {
      ManualDrivingControl(jyc, joystick);
    }
    else
    {
     DoManualTankDrivingControl(jyc, joystick, LeftTriggerLower);
    }
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
#ifdef REDEF_SLOW_MODE
    float slowScale = 0.25;
    scaleHerman(slowScale);
#endif
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
