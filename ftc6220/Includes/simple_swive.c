#ifndef SWIVE_C
#define SWIVE_C

/* Code Review by Darrell
 - *Good use of library code.*
 - task name should be capitalized per style guide -> Drive.
 - *Great descriptive variable names.*
 - Instead of fetching the joystick values several times. It would be easier to read if they were first stored in scoped variables.
*/

#include "../../library/drive_modes/simple_swerve_4m.c"
#include "JoystickDriver.c"
#include "writing.c"

task drive()
{
	float joyDistance;

	while(true)
	{
		getJoystickSettings(joystick);

		joyDistance = sqrt( pow(joystick.joy1_x2, 2) + pow( joystick.joy1_x2, 2) );

		if (JoystickToRotRate(joystick.joy1_x1) == 0)
		{
			int driveDirection = CalculateDriveAngle(joystick.joy1_x2, joystick.joy1_y2);
			int driveMagnitude = JoystickToMagnitude(joyDistance);
			SimpleWriteToMotors(driveMagnitude * MAX_MOTOR_SPEED_CMPS);
			SimpleWriteToServos(driveDirection);

		}
		else
		{
			int driveMagnitude = JoystickToRotRate(joystick.joy1_x1);
			int driveDirection = 45;
			SimpleWriteToMotors(driveMagnitude * MAX_MOTOR_SPEED_CMPS);
			SetServosRotateMode();
		}
	}
}
#endif
