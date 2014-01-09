//
// RobotBob.h
//
//-------------------------------------------------------------------------------------------------------
// Motor and servo controllers
//-------------------------------------------------------------------------------------------------------

#define motorController     rgmotorctlr[0]
#define motorController2    rgmotorctlr[1]
#define motorControllerArm  rgmotorctlr[2]

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
    InitializeMotor(fOverallSuccess, motorLeft,  motorController,  1, "left",  MOTORPROP_NONE      | MOTORPROP_ENCODER);
    InitializeMotor(fOverallSuccess, motorRight, motorController2, 1, "right", MOTORPROP_REFLECTED);
    //InitializeMotor(fOverallSuccess, motorArm, motorControllerArm, 1, "arm", MOTORPROP_NONE      | MOTORPROP_ENCODER);
    }

//-------------------------------------------------------------------------------------------------------
// Definition and initialization of sensors (see also boilerplate.h)
//-------------------------------------------------------------------------------------------------------

IRSENSOR irsensor;

void InitializeSensors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    //InitializeIRSensor(fOverallSuccess, "IR Sensor", irsensor, SensorOnMux(2,1), IRSENSOR_MODE_AC);
    }

void ReadSensors(READ_SENSORS_CONTEXT& context)
	{
    // ReadIRSensor(irsensor, context);
	}

void TriggerSensors(TRIGGER_SENSORS_CONTEXT& context)
	{
    // TriggerIRSensor(irsensor, context);
	}

//-------------------------------------------------------------------------------------------------------
// Servos
//-------------------------------------------------------------------------------------------------------

#define svoAllClosed            0
#define svoAllOpen              60
#define svoBackClosed           120

#define svoHand                 rgsvo[0]

#define servoController         rgsvoctlr[0]

void InitializeServos(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    InitializeServoController(fOverallSuccess, servoController, I2CLINK_1, 3);

    InitializeServo(fOverallSuccess, svoHand, "hand", servoController, 1, servoControllerDummy, 0, SVOKIND_STANDARD, true);
    }
