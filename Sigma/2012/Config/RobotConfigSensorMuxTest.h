//
// RobotTwoSensorMuxTest.h
//
//-------------------------------------------------------------------------------------------------------
// Motor and servo controllers
//-------------------------------------------------------------------------------------------------------

void InitializeMotors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
    }

//-------------------------------------------------------------------------------------------------------
// Definition and initialization of sensors (see also boilerplate.h)
//-------------------------------------------------------------------------------------------------------
EOPDSENSOR eopdOne;
EOPDSENSOR eopdTwo;
void InitializeSensors(IN OUT STICKYFAILURE& fOverallSuccess)
    {
      InitializeEopdSensor(fOverallSuccess, "EOPD Port 01", eopdOne, SensorOnMux(1,3), EOPD_RAW, EOPD_LONG);
      InitializeEopdSensor(fOverallSuccess, "EOPD Port 02", eopdTwo, SensorOnMux(1,4), EOPD_RAW, EOPD_LONG);
    //This Test is designed to test a sensor MUX, so it needs EOPD's on each port of a Mux on port one(1).
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
