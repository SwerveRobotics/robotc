#ifndef STALL_PROTECTION_C
#define STALL_PROTECTION_C

// what is stall protection?
// stop motor before it loses it's magic smoke
// maximum power but the motor is stopped or slowed by some force - wall, robot, or other obstacle
// requirement - motor encoder on each motor you wish to protect unless they are connected by chains

// detect your speed

int LAST_ENCODER_VALUE = 0;
int CURRENT_ENCODER_VALUE = 0;

tMotor ENCODER_MOTOR;

void RegisterEncoderMotor(tMotor motorName)
{
	ENCODER_MOTOR = motorName;
}

int ReadMotorEncoder()
{
	return nMotorEncoder[ENCODER_MOTOR];
}
task MonitorEncoder()
{
	while(true)
	{
		LAST_ENCODER_VALUE = CURRENT_ENCODER_VALUE;
		CURRENT_ENCODER_VALUE = nMotorEncoder[ENCODER_MOTOR];
		wait1Msec(10);
	}
}

int CurrentSpeed() // ticks per second
{
	return (CURRENT_ENCODER_VALUE - LAST_ENCODER_VALUE) * 100;
}

int LAST_SPEED;
int CURRENT_SPEED;
int LAST_POWER;
int CURRENT_POWER;

task MonitorSpeed()
{
	while(true)
	{
		LAST_SPEED = CURRENT_SPEED;
		CURRENT_SPEED = CurrentSpeed();
		LAST_POWER = CURRENT_POWER;
		CURRENT_POWER = motor[myMotor];

		int speedDiff = CURRENT_SPEED-LAST_SPEED;
		int powerDiff = CURRENT_POWER-LAST_POWER;
		if(speedDiff == 0 && powerDiff > 10)
			// save leh motor

		wait1Msec(20);
	}
}


// 0
// 1400


#endif
