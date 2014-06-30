#ifndef PID_INCLUDES_H
#define PID_INCLUDES_H

// PID Tuning Constants //
float pidPConst = 1;
float pidIConst = 0;
float pidDConst = 0;

// PID Time Delta //
int pidChangeTime = 200;

// PID Left Control Values //
float pidLeftPreviousError = 0;
float pidLeftProportional = 0;
float pidLeftIntegral = 0;
float pidLeftDerivative = 0;

// PID Right Control Values //
float pidRightPreviousError = 0;
float pidRightProportional = 0;
float pidRightIntegral = 0;
float pidRightDerivative = 0;


// Motor Speed Values //
int leftMotorRequestedSpeed = 0;
int rightMotorRequestedSpeed = 0;

// Use this include file so that all needed files
// are included in the correct order every time
#include "pid_controllers.c"
#include "pid_motors.c"
#include "pid_task.c"

#endif
