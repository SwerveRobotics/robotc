#ifndef CONTROLLER_DEFINES_H
#define CONTROLLER_DEFINES_H

const float ANALOG_DEAD_ZONE = 15.0;
const float MAX_ANALOG = 128.0;

// Desired Controller Input and Motor Ouput is assumed to be as follows:
// INPUT             OUTPUT
// -MAX_ANALOG       -MAX_MOTOR_SPEED
// -ANALOG_DEAD_ZONE -MIN_MOTOR_SPEED
// +ANALOG_DEAD_ZONE +MIN_MOTOR_SPEED
// +MAX_ANALOG       +MAX_MOTOR_SPEED
// Motor defines are located in library/motors/motor_defines.h














#endif
