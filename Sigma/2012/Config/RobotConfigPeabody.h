//
// RobotConfigPeabody.h
//
#define INCH_WHEEL_DIAMETER             (4.0)

#define CM_WHEEL_CIRCUMFERENCE          (INCH_WHEEL_DIAMETER * 2.54 * PI)
//-------------------------------------------------------------------------------------------------------
// Motor and servo controllers
//-------------------------------------------------------------------------------------------------------

#define motorController     rgmotorctlr[0]
#define motorRight          rgmotor[0]
#define motorLeft           rgmotor[1]

#define motorForklift       rgmotor[2]

void InitializeMotors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // The one motor controller on this robot is controller #1 in the daisy
    // chain of controllers on sensor port S1 (and on this bot, that's the ONLY controller
    // in said daisy chain).
    InitializeMotorController(fOverallSuccess, motorController, I2CLINK_1, 1);

    // Our two motors are motors #1 and #2 respectively on our motor controller
    InitializeMotor(fOverallSuccess, motorLeft,  motorController, 1, "left",  MOTORPROP_NONE      | MOTORPROP_ENCODER);
    InitializeMotor(fOverallSuccess, motorRight, motorController, 2, "right", MOTORPROP_REFLECTED | MOTORPROP_ENCODER);
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

#define mpangledencScaleFactor (360.0/270.0 * (3.0/INCH_WHEEL_DIAMETER))

//-------------------------------------------------------------------------------------------------------
// Definition and initialization of sensors (see also boilerplate.h)
//-------------------------------------------------------------------------------------------------------

void InitializeSensors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // This robot has no sensors, and so nothing needs to be done here
    }

SONICSENSOR sonicFront;
SONICSENSOR sonicBack;
SONICSENSOR sonicLeft;
SONICSENSOR sonicRight;
TOUCHSENSOR touchForklift;

void ReadSensors(READ_SENSORS_CONTEXT& context)
	{
    // This robot has no sensors, and so nothing needs to be done here
	}

void TriggerSensors(TRIGGER_SENSORS_CONTEXT& context)
	{
    // This robot has no sensors, and so nothing needs to be done here
	}

//-------------------------------------------------------------------------------------------------------
// Servos
//-------------------------------------------------------------------------------------------------------

#define svposTineUp       (128-110)
#define svposTineDown     (128+60)

#define svoLeftTineOpenClose    rgsvo[0]
#define svoRightTineOpenClose   rgsvo[1]
#define svoLeftTineUpDown       rgsvo[2]
#define svoRightTineUpDown      rgsvo[3]

void InitializeServos(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // This robot has no servos, and so nothing needs to be done in InitializeServos
    }
