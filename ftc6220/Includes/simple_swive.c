#ifndef SWIVE_C
#define SWIVE_C

/* Code Review by Darrell
 - *Good use of library code.*
 - task name should be capitalized per style guide -> Drive.
 - *Great descriptive variable names.*
 - Instead of fetching the joystick values several times. It would be easier to read if they were first stored in scoped variables.
*/

#include "../../library/drive_modes/simple_swerve_4m.c"
#include "pid.c"
#include "JoystickDriver.c"
#include "read_write.c"



task DriveTask()
{
	//initialization
	driverRelativeMode = false;
	float joyDistance;
	int joyX;
	int joyY;
	int joyZ;
	StartTask(PID);
	while(true)
	{
		getJoystickSettings(joystick);

		joyDistance = sqrt( pow(joystick.joy1_x2, 2) + pow( joystick.joy1_y2, 2) );
		joyX = joystick.joy1_x2;
		joyY = joystick.joy1_y2;
		joyZ = joystick.joy1_x1;

		if (JoystickToRotRate(joyZ) == 0)
		{
			float driveDirection;
			if (driverRelativeMode == true)
			{
				driveDirection = RADIAN_TO_DEGREE * atan2(joyY, joyX) - readGyro();
			}
			else
			{
				driveDirection = RADIAN_TO_DEGREE * atan2(joyY, joyX);
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
