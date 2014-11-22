#ifndef SWIVE_C
#define SWIVE_C

#include "../../library/drive_modes/simple_swerve_4m.c"
#include "JoystickDriver.c"

task drive()
{
	MOTOR_GEAR_RATIO = 1.0;

	SERVO_GEAR_RATIO = 1.0;

	float joyDistance;

	while(true)
	{
		getJoystickSettings(joystick);

		joyDistance = sqrt( pow(joystick.joy1_x2, 2) + pow( joystick.joy1_x2, 2) );

		if (JoystickToRotRate(joystick.joy1_x1) == 0)
		{
		int driveDirection = CalculateDriveAngle(joystick.joy1_x2, joystick.joy1_y2);
		int driveMagnitude = JoystickToMagnitude(joyDistance);
		SimpleWriteToDevicesMode1(driveMagnitude, driveDirection);
		}
		else
		{
			int driveMagnitude = JoystickToRotRate(joystick.joy1_x1);
			int driveDirection = 45;
			SimpleWriteToDevicesMode2(driveMagnitude, driveDirection);
		}
	}
}
#endif
