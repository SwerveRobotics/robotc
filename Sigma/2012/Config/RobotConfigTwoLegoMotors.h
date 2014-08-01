//
// RobotTwoLegoMotors.h
//
//-------------------------------------------------------------------------------------------------------
// Motor and servo controllers
//-------------------------------------------------------------------------------------------------------

#define motorRight          rgmotor[0]
#define motorLeft           rgmotor[1]

void InitializeMotors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // Our two motors are Lego motors on 'A' and 'B'
    InitializeMotor(fOverallSuccess, motorLeft,  legoController, 1, "left",  MOTORPROP_NONE);
    InitializeMotor(fOverallSuccess, motorRight, legoController, 2, "right", MOTORPROP_REFLECTED);
    }

//-------------------------------------------------------------------------------------------------------
// Definition and initialization of sensors (see also boilerplate.h)
//-------------------------------------------------------------------------------------------------------

void InitializeSensors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // This robot has no sensors, and so nothing needs to be done here
    }

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

void InitializeServos(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    // This robot has no serovs, and so nothing needs to be done in InitializeServos
    }
