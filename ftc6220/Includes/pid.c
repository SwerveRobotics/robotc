#ifndef PID_C
#define PID_C

#include "../../Library/sensors/gyro.c"

float Kp = 0.009;
float Ki = 0.008;
float Kd = 0.005;
float errorPrevSum[4] = {0.0, 0.0, 0.0, 0.0};
float errorPrev[4]    = {0.0, 0.0, 0.0, 0.0};
float error[4]        = {0.0, 0.0, 0.0, 0.0};
float ang[4]          = {0.0, 0.0, 0.0, 0.0};
float newAng[4]       = {0.0, 0.0, 0.0, 0.0};
float n[4]            = {0.0, 0.0, 0.0, 0.0};
float angPrev[4]      = {0.0, 0.0, 0.0, 0.0};
float newAngPrev[4]   = {0.0, 0.0, 0.0, 0.0};
float servoSpeed[4]   = {0.0, 0.0, 0.0, 0.0};

#endif
