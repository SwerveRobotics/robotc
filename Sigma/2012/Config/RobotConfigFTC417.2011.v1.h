//
// RobotConfigFTC417.2011.v1.h
//
#define INCH_WHEEL_DIAMETER             (4.0)
#define CM_WHEEL_CIRCUMFERENCE          (INCH_WHEEL_DIAMETER * 2.54 * PI)
#define MOTOR_GEARING                   (24.0/16.0)     // medium sprocket / small sprocket

//-------------------------------------------------------------------------------------------------------
// Motor and servo controllers
//-------------------------------------------------------------------------------------------------------

#define motorController                rgmotorctlr[0]
#define motorControllerForklift        rgmotorctlr[1]

#define motorRight                     rgmotor[0]
#define motorLeft                      rgmotor[1]
#define motorForklift                  rgmotor[2]
#define motorAnchor                    rgmotor[3]

void InitializeMotors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // The one motor controller on this robot is controller #1 in the daisy
    // chain of controllers on sensor port S1 (and on this bot, that's the ONLY controller
    // in said daisy chain).
    InitializeMotorController(fOverallSuccess, motorController,         I2CLINK_1, 1);
    InitializeMotorController(fOverallSuccess, motorControllerForklift, I2CLINK_1, 2);

    // Our two motors are motors #1 and #2 respectively on our motor controller
    // REVIEW: we should enable stall check for the tread drive motors
    InitializeMotor(fOverallSuccess, motorLeft,  motorController, 1, "left",  MOTORPROP_REFLECTED       | MOTORPROP_ENCODER);
    InitializeMotor(fOverallSuccess, motorRight, motorController, 2, "right", MOTORPROP_NONE | MOTORPROP_ENCODER);
    InitializeMotor(fOverallSuccess, motorForklift, motorControllerForklift, 2, "forklift", MOTORPROP_ENCODER);
    InitializeMotor(fOverallSuccess, motorAnchor, legoController, 1, "anchor", MOTORPROP_ENCODER | MOTORPROP_NOSTALLCHECK);
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

SONICSENSOR sonicBack;
SONICSENSOR sonicLeft;
SONICSENSOR sonicRight;
SONICSENSOR sonicFront;
IRSENSOR irsensor;
EOPDSENSOR eopdLeftTine;
EOPDSENSOR eopdRightTine;
EOPDSENSOR eopdBottom;
TOUCHSENSOR touchForklift;
GYROSENSOR sensGyroHorz;
#define sensnmGyroHorz SensorOnMux(4,3)

void InitializeSensors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
   /* InitializeSonicSensor(fOverallSuccess, "Back Sonic", sonicBack, SensorOnMux(4,1));
    InitializeSonicSensor(fOverallSuccess, "Left Sonic", sonicLeft, SensorOnMux(2,1));
    InitializeSonicSensor(fOverallSuccess, "Right Sonic", sonicRight, SensorOnMux(3,2));
    InitializeSonicSensor(fOverallSuccess, "Front Sonic", sonicFront, SensorOnMux(3,1));*/
    InitializeTouchSensor(fOverallSuccess, "Touch Forklift", touchForklift, SensorOnMux(4,1));
    //InitializeGyroSensor(fOverallSuccess, "Gyro Horizontal", sensGyroHorz, sensnmGyroHorz, 2000, 0);
   // InitializeEopdSensor(fOverallSuccess, "Bottom EOPD", eopdBottom, SensorOnMux(2,2), EOPD_RAW, EOPD_LONG);
   // InitializeIRSensor(fOverallSuccess, "IR Sensor", irsensor, SensorOnMux(3,1), IRSENSOR_MODE_ACDC);
   // InitializeIRSensor(fOverallSuccess, "IR Sensor", irsensor, SensorDirect(4), IRSENSOR_MODE_ACDC);
   // InitializeEopdSensor(fOverallSuccess, "EOPD Left Tine", eopdLeftTine, SensorOnMux(4,2), EOPD_RAW, EOPD_LONG);
   // InitializeEopdSensor(fOverallSuccess, "EOPD Right Tine", eopdRightTine, SensorOnMux(4,3), EOPD_RAW, EOPD_LONG);
    }

void ReadSensors(READ_SENSORS_CONTEXT& context)
	{
  ReadIRSensor(irsensor, context);
  ReadEOPDSensor(eopdLeftTine, context);
  ReadEOPDSensor(eopdRightTine, context);
  ReadEOPDSensor(eopdBottom, context);
  ReadTouchSensor(touchForklift, context);
  ReadGyroSensor(sensGyroHorz, context);
	}

void TriggerSensors(TRIGGER_SENSORS_CONTEXT& context)
	{
  TriggerIRSensor(irsensor, context);
  TriggerEopdSensor(eopdLeftTine, context);
  TriggerEopdSensor(eopdRightTine, context);
  TriggerEopdSensor(eopdBottom, context);
  TriggerTouchSensor(touchForklift, context);
  TriggerGyroSensor(sensGyroHorz, context);
	}

//-------------------------------------------------------------------------------------------------------
// Servos
//-------------------------------------------------------------------------------------------------------

#define svposTineUp       (128-128)
#define svposTineDown     (128+112)

#define svoLeftTineOpenClose    rgsvo[0]
#define svoRightTineOpenClose   rgsvo[1]
#define svoLeftTineUpDown       rgsvo[2]
#define svoRightTineUpDown      rgsvo[3]

#define servoController         rgsvoctlr[0]

void InitializeServos(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    InitializeServoController(fOverallSuccess, servoController, I2CLINK_1, 3);
    //
    // REVIEW: servo initialization needs to be tested
    //
    // Note: the last parameter to InitializeServo, a boolean, will simply turn off use of the
    // servo if set to false. Sometimes that's a handy thing to be able to do :-).
    //
    InitializeServo(fOverallSuccess, svoLeftTineOpenClose,  "tineL",   servoController,4,  servoControllerDummy,0,  SVOKIND_CNTROT, true);
    InitializeServo(fOverallSuccess, svoRightTineOpenClose, "tineR",   servoController,2,  servoControllerDummy,0,  SVOKIND_CNTROT, true);
    //
    InitializeServo(fOverallSuccess, svoLeftTineUpDown,     "tineLUD", servoController,1,  servoControllerDummy,0,  SVOKIND_STANDARD, true);
    InitializeServo(fOverallSuccess, svoRightTineUpDown,    "tineRUD", servoController,3,  servoControllerDummy,0,  SVOKIND_STANDARD, true);

    svoRightTineUpDown.fReversed = true;
    svoRightTineOpenClose.fReversed = true;
    }
