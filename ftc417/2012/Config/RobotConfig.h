//
// RobotConfig.h
//
// Part of the FTC Team 417 Software Starter Kit: www.ftc417.org/ssk
//
// Header by which robot hardware configuration information (motors, sensors,
// servos, geometry, etc) is made known to programs.
//
// To do: create an appropriately named header file with your bot's configuration
// (we suggest a name of the form RobotConfigXXX.h). Then edit this file in the
// places indicated by #### below.

//--------------------------------------------------------------------------
// #### To do: edit the definition here of ROBOT_NAME to be one of the
// robot name constants defined below as appropriate for your bot.
// Note: if you happen to mistype and set the definition to something other
// than one of the defined robot name constants, you'll get a bunch of 'undefined
// preprocessor varaible errors on each of the #elif lines below

#ifndef ROBOT_NAME
#define ROBOT_NAME  ROBOT_NAME_SENSOR_MUX_TEST
#endif

//--------------------------------------------------------------------------
// #### To do: add a #define with a new name and numeric constant for your robot

#define ROBOT_NAME_NULL_BOT                     1
#define ROBOT_NAME_TWO_MOTORS_NO_ENCODERS       2
#define ROBOT_NAME_TWO_MOTORS_WITH_ENCODERS     3
#define ROBOT_NAME_OMNI_BOT                     4
#define ROBOT_NAME_TWO_LEGO_MOTORS              5
#define ROBOT_NAME_FTC417_2010_V11              6   // obsolete, only historical
#define ROBOT_NAME_FTC417_2010_V12              7
#define ROBOT_NAME_FTC417_2011_V1               8
#define ROBOT_NAME_PEABODY                      9
#define ROBOT_NAME_FTC417_2011_V2               10
#define ROBOT_NAME_SENSOR_MUX_TEST              11
#define ROBOT_NAME_SPACEELEVATOR                12
#define ROBOT_NAME_SPACEELEVATORDISPENSER       13
#define ROBOT_NAME_CAROLYNSTESTROBOT            14
#define ROBOT_NAME_FTC417_2012_TASKBOT          15
#define ROBOT_NAME_6401                         16


//--------------------------------------------------------------------------
// #### To do: add a clause to the cascade of #elif directives that includes
// the header file with your bot's configuration.

#if !defined(ROBOT_NAME)

    #error("RobotConfig.h: ROBOT_NAME is not defined")

#elif ROBOT_NAME==ROBOT_NAME_NULL_BOT

	#ifndef InitializeMotors
	void InitializeMotors(IN OUT STICKYFAILURE& fOverallSuccess)
		{
		}
	#endif
	#ifndef InitializeSensors
	void InitializeSensors(IN OUT STICKYFAILURE& fOverallSuccess)
		{
		}
	#endif
	#ifndef InitializeServos
	void InitializeServos(IN OUT STICKYFAILURE& fOverallSuccess)
		{
		}
	#endif
	#ifndef ReadSensors
	void ReadSensors(READ_SENSORS_CONTEXT& context)
		{
		}
	#endif
	#ifndef TriggerSensors
	void TriggerSensors(TRIGGER_SENSORS_CONTEXT& context)
		{
		}
	#endif

#elif ROBOT_NAME==ROBOT_NAME_TWO_MOTORS_NO_ENCODERS
    #include "RobotConfigTwoMotorsNoEncoders.h"

#elif ROBOT_NAME==ROBOT_NAME_TWO_MOTORS_WITH_ENCODERS
    #include "RobotConfigTwoMotorsWithEncoders.h"

#elif ROBOT_NAME==ROBOT_NAME_OMNI_BOT
    #include "RobotConfigOmnibot.h"

#elif ROBOT_NAME==ROBOT_NAME_TWO_LEGO_MOTORS
    #include "RobotConfigTwoLegoMotors.h"

#elif ROBOT_NAME==ROBOT_NAME_FTC417_2010_V12
    #include "RobotConfigFTC417.2010.v12.h"

#elif ROBOT_NAME==ROBOT_NAME_FTC417_2011_V1
    #include "RobotConfigFTC417.2011.v1.h"

#elif ROBOT_NAME==ROBOT_NAME_PEABODY
    #include "RobotConfigPeabody.h"

#elif ROBOT_NAME==ROBOT_NAME_FTC417_2011_V2
    #include "RobotConfigFTC417.2011.v2.h"

#elif ROBOT_NAME==ROBOT_NAME_SENSOR_MUX_TEST
    #include "RobotConfigSensorMuxTest.h"

#elif ROBOT_NAME==ROBOT_NAME_SPACEELEVATOR
    #include "RobotConfigSpaceElevator.h"

#elif ROBOT_NAME==ROBOT_NAME_SPACEELEVATORDISPENSER
    #include "RobotConfigSpaceElevatorDispenser.h"

#elif ROBOT_NAME==ROBOT_NAME_CAROLYNSTESTROBOT
    #include "RobotConfigCarolynsTestRobot.h"

#elif ROBOT_NAME==ROBOT_NAME_FTC417_2012_TASKBOT
    #include "RobotConfigFTC417.2012.taskbot.h"

#elif ROBOT_NAME==ROBOT_NAME_6401
    #include "RobotConfig6401.h"

#else

    #error("RobotConfig.h: unspecified robot configuration")

#endif
