#ifndef SWIVE_C
#define SWIVE_C

#include "../../library/drive_modes/simple_swerve_4m.c"
#include "pid.c"
#include "JoystickDriver.c"
#include "read_write.c"



task drive()
{
	//initialization
	bool driverRelativeMode = true;
	float joyDistance;
	int joyX;
	int joyY;
	int joyZ;
	StartTask(PID);
	while(true)
	{
		getJoystickSettings(joystick);

		joyDistance = sqrt( pow(joystick.joy1_x2, 2) + pow( joystick.joy1_y2, 2) );
		int joyX = joystick.joy1_x2;
		int joyY = joystick.joy1_y2;
		int joyZ = joystick.joy1_x1;

		if (JoystickToRotRate(joyZ) == 0)
		{
			float driveDirection;
			if (driverRelativeMode == true)
			{
				driveDirection = RADIAN_TO_DEGREE * atan2(joyY, joyX) - readGyro();
			}
			else
			{
				driveDirection = RADIAN_TO_DEGREE * atan2(joyY, joyX) - readGyro();
			}
			float driveMagnitude = JoystickToMagnitude(joyDistance);
			SimpleWriteToMotors(driveMagnitude * MAX_MOTOR_SPEED_CMPS);
			SetServos(driveDirection);

		}
		else
		{
			float driveMagnitude = JoystickToRotRate(joyZ);
			SimpleWriteToMotors(driveMagnitude * MAX_MOTOR_SPEED_CMPS);
			SetServosRotateMode();
		}
	}
}
#endif
