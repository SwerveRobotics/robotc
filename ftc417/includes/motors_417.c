#ifndef MOTORS_417_C
#define MOTORS_417_C

#include "../../library/motors/motors.c"

// Arm Motor
const int ARM_MOTOR_POWER = 50;
void SetArmsMotorPower(int power)
{
	SetMotorPower(Arm, power);
}

void RaiseArm()
{
	SetArmsMotorPower(ARM_MOTOR_POWER);
}

void LowerArm()
{
	SetArmsMotorPower(-1*ARM_MOTOR_POWER);
}

void StopArm()
{
	SetArmsMotorPower(0);
}

#endif
