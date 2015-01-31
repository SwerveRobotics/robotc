#ifndef PID_C
#define PID_C

#include "../../library/sensors/gyro.c"
#include "../../library/drive_modes/simple_swerve_4m.c"

//servo constants
const float Sp = 0.008;
const	float Si = 0.015;
const	float Sd = 0.000;

//robot constants (rotation)
const float Rp = 0.1;
const float Ri = 0.0;
const float Rd = 0.0;


float RLastAngle;
float RError;
float RErrorPrev;
float RErrorSum;

task PID()
{
	resetGyro();
	startGyro();
	while (true)
	{
		//servo pid
		for (CornerEnum p; p <= 4; p++)
		{
			//update PID specific past values
			Drive[p].servoPositionPrev = Drive[p].servoPosition;
			Drive[p].errorPrev = Drive[p].error;
			Drive[p].errorSum += Drive[p].errorPrev * 0.005;

			//check to see if the new position is equivalent to a closer angle
			if (abs(Drive[p].servoPosition - Drive[p].servoPositionPrev) > 180)
			{
				Drive[p].n += 360 * sgn(Drive[p].servoPositionPrev - Drive[p].servoPosition);
			}
			//check to see if the new position can be reached faster by reversing the motor power
			else if (abs(Drive[p].servoPosition - Drive[p].servoPositionPrev) > 90)
			{
				reverseMotorFactor[p] *= -1;
				Drive[p].n += 180 * sgn(Drive[p].servoPositionPrev - Drive[p].servoPosition);
			}
			Drive[p].servoTgt = Drive[p].servoPosition + Drive[p].n;
			Drive[p].error = Drive[p].servoTgt - GetCRServoPosition(p);

			Drive[p].servoSpeed = (Sp * Drive[p].error) + (Si * Drive[p].errorSum) + (Sd * Drive[p].error - Drive[p].errorPrev);
			SetServo(Assembly[p].servo, Drive[p].servoSpeed);
		}

		//motors
		RLastAngle = readGyro();
		RErrorPrev = RError;
		RErrorSum += RErrorPrev;
		RError = RTgt - readGyro();
		if (rotateMode == True)
		{
			float mag = (Rp * RError) + (Ri * RErrorSum) + (Rd * RError - RErrorPrev);
			SimpleWriteToMotors(mag * MAX_MOTOR_SPEED_CMPS);
		}
		wait1Msec(100);
	}
}

#endif
