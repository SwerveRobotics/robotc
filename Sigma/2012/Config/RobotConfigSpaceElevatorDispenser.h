//
// RobotSpaceElevatorDispenser.h
//
//-------------------------------------------------------------------------------------------------------
// Motor and servo controllers
//-------------------------------------------------------------------------------------------------------

#define motorController     rgmotorctlr[0]
#define motorRight          rgmotor[0]
#define motorLeft           rgmotor[1]

void InitializeMotors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    InitializeMotorController(fOverallSuccess, motorController, I2CLINK_1, 1);

    InitializeMotor(fOverallSuccess, motorLeft,  motorController, 1, "left",  MOTORPROP_NONE      | MOTORPROP_ENCODER);
    InitializeMotor(fOverallSuccess, motorRight, motorController, 2, "right", MOTORPROP_REFLECTED | MOTORPROP_ENCODER);
    }

//-------------------------------------------------------------------------------------------------------
// Definition and initialization of sensors (see also boilerplate.h)
//-------------------------------------------------------------------------------------------------------

TOUCHSENSOR touchDispenser;

void InitializeSensors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    InitializeTouchSensor(fOverallSuccess, "Touch Dispenser", touchDispenser, SensorOnMux(2,1));
    }

void ReadSensors(READ_SENSORS_CONTEXT& context)
	{
    ReadTouchSensor(touchDispenser, context);
	}

void TriggerSensors(TRIGGER_SENSORS_CONTEXT& context)
	{
    TriggerTouchSensor(touchDispenser, context);
	}

//-------------------------------------------------------------------------------------------------------
// Servos
//-------------------------------------------------------------------------------------------------------

void InitializeServos(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // This robot has no serovs, and so nothing needs to be done in InitializeServos
    }
