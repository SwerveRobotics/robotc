//
// RobotConfigFTC417.2011.v2.h
//
#define INCH_WHEEL_DIAMETER             (4.0)

#define CM_WHEEL_CIRCUMFERENCE          (INCH_WHEEL_DIAMETER * 2.54 * PI)

//-------------------------------------------------------------------------------------------------------
// Motor and servo controllers
//-------------------------------------------------------------------------------------------------------
#define motorControllerRight       rgmotorctlr[0]
#define motorControllerLeft        rgmotorctlr[1]

#define motorLeft                  rgmotor[0]
#define motorRight                 rgmotor[1]
#define motorRamp                  rgmotor[2]
#define motorArm                   rgmotor[3]

void InitializeMotors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    InitializeMotorController(fOverallSuccess, motorControllerRight,  I2CLINK_1, 1);
    InitializeMotorController(fOverallSuccess, motorControllerLeft,   I2CLINK_1, 2);

    LockDaisy();

    MOTORMODE modeHelperRight;
    BOOL fSuccess;
    SetControllerMtrRunMode(modeHelperRight, motorControllerRight, 0, MOTORMODE_RUN_WITH_POWER_ONLY);
    SetControllerMtrRunMode(modeHelperRight, motorControllerRight, 1, MOTORMODE_RUN_WITH_POWER_ONLY);
    SetControllerMtrRunMode(modeHelperRight, motorControllerRight, 2, MOTORMODE_RUN_WITH_POWER_ONLY);
    SendMotorModePower(fSuccess, motorControllerRight);
    waitForMotorControllerCommandCycle1(motorControllerRight);

    MOTORMODE modeHelperLeft;
    SetControllerMtrRunMode(modeHelperLeft, motorControllerLeft, 0, MOTORMODE_RUN_WITH_POWER_ONLY);
    SetControllerMtrRunMode(modeHelperLeft, motorControllerLeft, 1, MOTORMODE_RUN_WITH_POWER_ONLY);
    SetControllerMtrRunMode(modeHelperLeft, motorControllerLeft, 2, MOTORMODE_RUN_WITH_POWER_ONLY);
    SendMotorModePower(fSuccess, motorControllerLeft);
    waitForMotorControllerCommandCycle1(motorControllerLeft);

    ReleaseDaisy();

    InitializeMotor(fOverallSuccess, motorLeft,     motorControllerLeft,  1, "left",  MOTORPROP_REFLECTED | MOTORPROP_ENCODER | MOTORPROP_NOSTALLCHECK);
    InitializeMotor(fOverallSuccess, motorRight,    motorControllerRight, 1, "right", MOTORPROP_ENCODER | MOTORPROP_NOSTALLCHECK);
    InitializeMotor(fOverallSuccess, motorRamp,     motorControllerRight, 2, "Ramp",  MOTORPROP_NONE);
    InitializeMotor(fOverallSuccess, motorArm,      motorControllerLeft,  2, "Arm",   MOTORPROP_NONE);
    }

#define HAS_ENCODER_BASED_TURNING_TABLE 1

#define TURNFLAG_DEFAULT TURNFLAG_PROHIBIT_GYRO

// Note: Table was empirically built on a bot which had 3 inch wheels / treads
//       If using on a different bot, as a first rough cut one might try scaling
//       that linearly. This can be incorporated into mpangledencScaleFactor.
//
float mpangledenc[][3] =
    {
        { -180.0000, 3215.0, -3215.0 },
        { -90.0000,  1574.0, -1574.0 },
        { -45.0000,   709.0,  -709.0 },
        { -28.58,     400.0,  -400.0 },
        { -16.64,     200.0,  -200.0 },
        {  -4.00,      55.0,   -55.0 }, // manual fudge, linear = 48.1
        {   0.0,        0.0,     0.0 },
        {   4.00,     -55.0,    55.0 }, // manual fudge, linear = 50.0
        {  16.00,    -200.0,   200.0 },
        {  27.67,    -400.0,   400.0 },
        { 45.0000,   -748.0,   748.0 },
        { 90.0000,  -1644.0,  1644.0 },
        { 180.0000, -3403.0,  3403.0 },
    };

#define mpangledencScaleFactor (360.0/360.0 * (3.0/INCH_WHEEL_DIAMETER))

//-------------------------------------------------------------------------------------------------------
// Definition and initialization of sensors (see also boilerplate.h)
//-------------------------------------------------------------------------------------------------------

void InitializeSensors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // No sensors yet
    }

void ReadSensors(READ_SENSORS_CONTEXT& context)
	{

	}

void TriggerSensors(TRIGGER_SENSORS_CONTEXT& context)
	{

	}

//-------------------------------------------------------------------------------------------------------
// Servos
//-------------------------------------------------------------------------------------------------------
/*#define svposLatch      (64-64)
#define svposLatchTurnBack (66+69)
#define svposPuller     (128-128)
#define svposPullerBack (64+128)*/
int svposPuller = 64;
int svposWrist = 64;
//#define svoLatch    rgsvo[0]
#define svoPuller   rgsvo[1]
#define svoWrist    rgsvo[2]
#define svoPuller2  rgsvo[3]
#define svoWrist2   rgsvo[4]

#define servoController         rgsvoctlr[0]

void InitializeServos(IN OUT STICKYFAILURE& fOverallSuccess)
    {
      InitializeServoController(fOverallSuccess, servoController, I2CLINK_2, 1);
      //InitializeServo(fOverallSuccess, svoLatch,     "Latch", servoController,1,  servoControllerDummy,0,  SVOKIND_STANDARD, true);
      InitializeServo(fOverallSuccess, svoPuller,     "Puller", servoController,1, servoControllerDummy,0, SVOKIND_STANDARD, true);
      InitializeServo(fOverallSuccess, svoWrist,      "Wrist",  servoController,2, servoControllerDummy,0, SVOKIND_STANDARD, true);
      InitializeServo(fOverallSuccess, svoPuller2,     "Puller2", servoController,3, servoControllerDummy,0, SVOKIND_STANDARD, true);
      InitializeServo(fOverallSuccess, svoWrist2,      "Wrist2",  servoController,4, servoControllerDummy,0, SVOKIND_STANDARD, true);


    }
