#ifndef SERVO_DEFINES_H
#define SERVO_DEFINES_H

const int SERVO_RANGE = 255;
const int CR_SERVO_ZERO = 128;//value at which CR servos should not move

const int WINCH_SERVO_MIN = 5;//value below which a winch servo will spin CW
const int WINCH_SERVO_MAX= 250;//value above which a winch servo will spin CCW

const int CLOCKWISE = -1;
const int CW = CLOCKWISE;
const int COUNTER_CLOCKWISE = 1;
const int CCW = COUNTER_CLOCKWISE;

#endif
