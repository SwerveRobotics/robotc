//
// RobotBob.h
//
//-------------------------------------------------------------------------------------------------------
// Motor controllers
//-------------------------------------------------------------------------------------------------------

#define motorController     rgmotorctlr[0]
#define motorController2    rgmotorctlr[1]
//#define motorControllerArm  rgmotorctlr[2]

#define motorRight          rgmotor[0]
#define motorLeft           rgmotor[1]
#define motorArm            rgmotor[2]

void InitializeMotors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // The one motor controller on this robot is controller #1 in the daisy
    // chain of controllers on sensor port S1 (and on this bot, that's the ONLY controller
    // in said daisy chain).
    InitializeMotorController(fOverallSuccess, motorController, I2CLINK_1, 1);
    InitializeMotorController(fOverallSuccess, motorController2, I2CLINK_1, 2);
    //InitializeMotorController(fOverallSuccess, motorControllerArm, I2CLINK_1, 3);

    // Our two motors are motors #1 and #2 respectively on our motor controller
    InitializeMotor(fOverallSuccess, motorLeft,  motorController,  1, "left",  MOTORPROP_NONE      | MOTORPROP_ENCODER | MOTORPROP_NOSTALLCHECK);
    InitializeMotor(fOverallSuccess, motorRight, motorController2, 1, "right", MOTORPROP_REFLECTED);
    InitializeMotor(fOverallSuccess, motorArm, motorController2, 2, "arm", MOTORPROP_NONE);
    }

//-------------------------------------------------------------------------------------------------------
// Definition and initialization of sensors (see also boilerplate.h)
//-------------------------------------------------------------------------------------------------------

IRSENSOR irsensor;

void InitializeSensors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    //InitializeIRSensor(fOverallSuccess, "IR Sensor", irsensor, SensorOnMux(2,4), IRSENSOR_MODE_AC);
    }

void ReadSensors(READ_SENSORS_CONTEXT& context)
	{
     ReadIRSensor(irsensor, context);
	}

void TriggerSensors(TRIGGER_SENSORS_CONTEXT& context)
	{
     TriggerIRSensor(irsensor, context);
	}

//-------------------------------------------------------------------------------------------------------
// Servos
//-------------------------------------------------------------------------------------------------------

/*#define svoAllClosed            0
#define svoAllOpen              150
#define svoBackClosed           120*/

#define svoOpenRight            50
#define svoOpenLeft             200
#define svoClosedRight          160
#define svoClosedLeft           100

#define svoRight                rgsvo[0]
#define svoLeft                 rgsvo[1]

#define servoController         rgsvoctlr[0]

void InitializeServos(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    InitializeServoController(fOverallSuccess, servoController, I2CLINK_1, 3);

    InitializeServo(fOverallSuccess, svoRight, "right hand", servoController, 2, servoControllerDummy, 0, SVOKIND_STANDARD, true);
    InitializeServo(fOverallSuccess, svoLeft, "left hand", servoController, 1, servoControllerDummy, 0, SVOKIND_STANDARD, true);
    }
