#ifndef SWIVE_C
#define SWIVE_C

#include "../../library/drive_modes/swerve_4m.c"
#include "JoystickDriver.c"
#include "writing.c"

task drive()
{

	initializeDriveAssemblies();

	float joyX1;
	float joyX2;
	float joyY2;
	while(true)
	{
		getJoystickSettings(joystick);

		joyX2 = joystick.joy1_x2;
		joyX1 = joystick.joy1_x1;
		joyY2 = joystick.joy1_y2;

		float X_Velocity = JoystickToCMPerSec(joyX2, joyX1);
		float Y_Velocity = JoystickToCMPerSec(joyY2, joyX1);
		float Z_Velocity = JoystickToRadsPerSec(joyX1);

		for (MotorEnum p; p < BACK_RIGHT; p++)
		{
			Drive[p].servoPosition = CalculateDriveAngle(X_Velocity, Y_Velocity, Z_Velocity, p);
			Drive[p].motorPower = CalculateDriveSpeed(X_Velocity, Y_Velocity, Z_Velocity, p);
		}

	}
}
#endif
