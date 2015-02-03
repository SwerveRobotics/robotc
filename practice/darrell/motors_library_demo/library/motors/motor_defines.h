#ifndef MOTOR_DEFINES_H
#define MOTOR_DEFINES_H

const float MAX_MOTOR_SPEED = 100.0;// maximum speed we should intentionally give the motor
const float MIN_MOTOR_SPEED = 20.0; // minimum speed at which motor will move

// true - all SetMotorSpeed functions will scale the motor output assuming input speed is
//        in the range of -128 to +127.
// false - all SetMotorSpeed functions will set the motor output directly to input speed
bool ASSUME_CONTROLLER_INPUT = true;











#endif
