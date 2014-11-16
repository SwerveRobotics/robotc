//
// RobotConfigFTC417.2011.v2.h
//
#define INCH_WHEEL_DIAMETER             (4.0)

#define CM_WHEEL_CIRCUMFERENCE          (INCH_WHEEL_DIAMETER * 2.54 * PI)

//-------------------------------------------------------------------------------------------------------
// Motor and servo controllers
//-------------------------------------------------------------------------------------------------------

#define motorControllerLeft        rgmotorctlr[0]
#define motorControllerRight       rgmotorctlr[1]

#define motorLeft                  rgmotor[0]
#define motorLeftAux               rgmotor[1]
#define motorRight                 rgmotor[2]
#define motorRightAux              rgmotor[3]

void InitializeMotors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    InitializeMotorController(fOverallSuccess, motorControllerLeft,   I2CLINK_1, 1);
    InitializeMotorController(fOverallSuccess, motorControllerRight,  I2CLINK_1, 2);

    InitializeMotor(fOverallSuccess, motorLeft,     motorControllerLeft,  1, "left front",  MOTORPROP_REFLECTED | MOTORPROP_ENCODER);
    InitializeMotor(fOverallSuccess, motorLeftAux,  motorControllerLeft,  2, "left back",   MOTORPROP_REFLECTED | MOTORPROP_ENCODER);
    InitializeMotor(fOverallSuccess, motorRight,    motorControllerRight, 2, "right front", MOTORPROP_ENCODER);
    InitializeMotor(fOverallSuccess, motorRightAux, motorControllerRight, 1, "right back",  MOTORPROP_ENCODER);

    motorLeft.imotorPaired = motorLeftAux.imotor;
    motorRight.imotorPaired = motorRightAux.imotor;
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

void InitializeServos(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // No servos yet
    }
