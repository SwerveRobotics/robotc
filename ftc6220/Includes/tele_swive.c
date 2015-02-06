#ifndef TELE_SWIVE_C
#define TELE_SWIVE_C

#include "JoystickDriver.c"
#include "controller.c"
#include "../../Library/drive_modes/simple_swerve_4m.c"
#include "../../Library/motors/motors.c"
#include "../../Library/motors/servos.c"
#include "pid.c"



task DriveTask()
{
	initializeDrive();

	float joyX;
	float joyY;
	float joyZ;
	float joyDirection;
	float joyTranslateMagnitude;

	while (true)
	{
				//update joystick values
		getJoystickSettings(joystick);
		joyX = joystick.joy1_x2;
		joyY = joystick.joy1_y2;
		joyZ = joystick.joy1_x1;
		joyDirection = radiansToDegrees( atan2( joyY, joyX ) );
		joyTranslateMagnitude = sqrt( pow(joyX, 2) + pow(joyY, 2) );


		//unfiltered motor power
		float drivePower;

		float drivePowerFiltered;
		//last filtered drive power
		float drivePowerFilteredPrev;

		//check whether the drive should be turning or translating
		if (abs(JoystickToMagnitude(joyZ)) > 0)
		{
			//set the drives to the optimal roatation positions and use rotation axis to control motor speed
			SetServosRotateMode();
			drivePower = 100 * JoystickToMagnitude(joyZ);
		}
		else if (abs(JoystickToMagnitude(joyTranslateMagnitude)) > 0)
		{
			//set the drives to aim in the direction of the translation axis and use it to control motor speed
			SetDriveServos(joyDirection);
			drivePower = 100 * joyTranslateMagnitude;
		}

		//PID loop for the drive servos
		for(int p = 0; p < 4; p++)
		{
			//update previous values
			angPrev[p]       = ang[p];
			newAngPrev[p]    = newAng[p];
			errorPrev[p]     = error[p];
			errorPrevSum[p] += error[p];

			//update current values
			ang[p] = Drive[p].servoPosition;
			error[p] = ang[p] + GetDrivePosition(p);//this SHOULD be a sum

			//optimize rotation target such that it is never > 90 degrees away
			if (error[p] > 90)
			{
				while(error[p] > 90)
				{
					n[p] += 180 * sgn(error[p]);
					Drive[p].reverseMotorPower *= -1;
					error[p] += n;
				}
			}

			//calculate the servo speed with PID
			Drive[p].servoSpeed = (Kp * error[p]) + (Ki * errorPrevSum[p]) + (Kd * ( error[p] - errorPrev[p] ) );
		}

		//motor speed LD filter
		if ( abs(drivePowerFilteredPrev - drivePower) < 10)
		{
			drivePowerFiltered = drivePower;
		}
		else
		{
			drivePowerFiltered -= sgn(drivePowerFilteredPrev - drivePower);
		}
		SetDriveMotors(drivePowerFiltered);
		drivePowerFilteredPrev = drivePowerFiltered;
		WriteToDrive();
		wait1Msec(100);
	}
}
#endif
