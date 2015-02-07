#ifndef MOTORS_417_C
#define MOTORS_417_C

#include "../../library/motors/motors.c"

// Arm Motor
const int ARM_MOTOR_POWER_DEFAULT = 50;
void SetArmsMotorPower(int power)
{
	SetMotorPower(Arm, power);
}

void MoveArmUp(int power = ARM_MOTOR_POWER_DEFAULT)
{
	SetArmsMotorPower(power);
}

void MoveArmDown(int power = ARM_MOTOR_POWER_DEFAULT)
{
	SetArmsMotorPower(-1*power);
}

// named so that caller controls direction
void SetArmPower(int power = ARM_MOTOR_POWER_DEFAULT)
{
	SetArmsMotorPower(power);
}

void StopArmMovement()
{
	SetArmsMotorPower(0);
}

#endif
