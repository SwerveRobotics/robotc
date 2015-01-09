//
// RobotConfigSpaceElevator.h
//
//-------------------------------------------------------------------------------------------------------
// Motor and servo controllers
//-------------------------------------------------------------------------------------------------------
#define motorController     rgmotorctlr[0]

#define motorTreads           rgmotor[0]
#define motorWheels           rgmotor[1]
#define motorArmTread         rgmotor[2]
#define motorArmWheel         rgmotor[3]

void InitializeMotors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    InitializeMotorController(fOverallSuccess, motorController, I2CLINK_1, 1);

    InitializeMotor(fOverallSuccess, motorTreads,  motorController, 2, "Treads", MOTORPROP_REFLECTED | MOTORPROP_ENCODER);
    InitializeMotor(fOverallSuccess, motorWheels,  motorController, 1, "Wheels", MOTORPROP_NONE | MOTORPROP_ENCODER);
    //InitializeMotor(fOverallSuccess, motorArmTread, legoController, 1, "Arm Tread Side", MOTORPROP_NONE | MOTORPROP_ENCODER);
    //InitializeMotor(fOverallSuccess, motorArmWheel, legoController, 2, "Arm Wheel Side", MOTORPROP_NONE | MOTORPROP_ENCODER);
    }

//-------------------------------------------------------------------------------------------------------
// Definition and initialization of sensors (see also boilerplate.h)
//-------------------------------------------------------------------------------------------------------

TOUCHSENSOR touchTop;
TOUCHSENSOR touchBottom;
TOUCHSENSOR touchArmTread;
TOUCHSENSOR touchArmWheel;

void InitializeSensors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    InitializeTouchSensor(fOverallSuccess, "Touch Top", touchTop, SensorOnMux(2,1));
    InitializeTouchSensor(fOverallSuccess, "Touch Bottom", touchBottom, SensorOnMux(2,2));
    //InitializeTouchSensor(fOverallSuccess, "Touch Arm Tread Side", touchArmTread, SensorOnMux(2,3));
    //InitializeTouchSensor(fOverallSuccess, "Touch Arm Wheel Side", touchArmWheel, SensorOnMux(2,4));
    }

void ReadSensors(READ_SENSORS_CONTEXT& context)
	{
    ReadTouchSensor(touchTop, context);
    ReadTouchSensor(touchBottom, context);
    //ReadTouchSensor(touchArmTread, context);
    //ReadTouchSensor(touchArmWheel, context);
	}

void TriggerSensors(TRIGGER_SENSORS_CONTEXT& context)
	{
    TriggerTouchSensor(touchTop, context);
    TriggerTouchSensor(touchBottom, context);
    //TriggerTouchSensor(touchArmTread, context);
    //TriggerTouchSensor(touchArmWheel, context);
	}

//-------------------------------------------------------------------------------------------------------
// Servos
//-------------------------------------------------------------------------------------------------------

void InitializeServos(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // This robot has no servos, and so nothing needs to be done in InitializeServos
    }
