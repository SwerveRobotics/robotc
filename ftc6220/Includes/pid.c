#ifndef PID_C
#define PID_C

//#include "../../library/sensors/gyro.c"
#include "../../library/drive_modes/simple_swerve_4m.c"
/*
//robot constants (rotation)
const float Rp = 0.1;
const float Ri = 0.0;
const float Rd = 0.0;


float RLastAngle;
float RError;
float RErrorPrev;
float RErrorSum;
*/
float Kp = 0.009;
float Ki = 0.008;
float Kd = 0.005;
float errorPrevSum[4] = {0.0, 0.0, 0.0, 0.0};
float errorPrev[4] = {0.0, 0.0, 0.0, 0.0};
float error[4];
float ang[4] = {0.0, 0.0, 0.0, 0.0};
float newAng[4] = {0.0, 0.0, 0.0, 0.0};
float n[4] = {0.0, 0.0, 0.0, 0.0};
float angPrev[4] = {0.0, 0.0, 0.0, 0.0};
float newAngPrev[4] = {0.0, 0.0, 0.0, 0.0};
float servoSpeed[4] = {0.0, 0.0, 0.0, 0.0};

task PID()
{
	while (true)
	{
		joyX = joystick.joy1_x2;
		joyY = joystick.joy1_y2;
		joyZ = joystick.joy1_x1;
		joyDistance = sqrt( pow(joyX, 2) + pow( joyY, 2) );
		joyAngle = -57.3 * atan2(joyY, joyX);

		for (int p = 0; p < 4; p++)
		{
			angPrev[p] = ang[p];
			newAngPrev[p] = newAng[p];
			if (JoystickToRotRate(joyZ) > 0)
			{
				if (p == 0)
				{
					newAng[p] = -45.0 + n[p];
				}
				else if (p == 1)
				{
					newAng[p] = 45 + n[p];
				}
				else if (p == 1)
				{
					newAng[p] = 225 + n[p];
				}
				else
				{
					newAng[p] = 135 + n[p];
				}
			}
			else if (JoystickToMagnitude(joyDistance) > 0)
			{
				ang[p] = joyAngle;

				if (abs(ang[p] - angPrev[p]) > 180)
				{
					n[p] = n[p] + -360 * sgn(ang[p]-angPrev[p]);
				}

				else if (abs(ang[p] - angPrev[p]) > 90)
				{
					n[p] = n[p] + -180 * sgn(ang[p]-angPrev[p]);
					reverseMotorFactor[p] = -1 * reverseMotorFactor[p];
				}
				if (abs(n[p]) > 1440)
				{
					n[p] = sgn(n[p]) * 1440;
				}
				newAng[p] = ang[p] + n[p] - 90;
			}
			error[p] = newAng[p] + GetCRServoPosition(p);
			servoSpeed[p] = ( Kp * error[p] ) + ( Ki * errorPrevSum[p] ) + ( Kd * (error[p] - errorPrev[p]) );
			servo[Assembly[p].driveServo] = 127 * ( -1 * servoSpeed[p] + 1);
			errorPrev[p] = error[p];
			errorPrevSum[p] = errorPrevSum[p] + errorPrev[p] * 0.005;
		}
		wait1Msec(100);
	}
}

#endif
