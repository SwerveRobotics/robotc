#ifndef SWIVE_C
#define SWIVE_C

#include "../library/drive_modes/swerve_4m.c"
#include "JoystickDriver.c"

// MOVE SWERVE CONSTANTS HERE //


task drive()
{
	initializeDriveAssemblies();

	while(true)
	{
		getJoystickSettings(joystick);

		int X_Velocity = JoystickToMetersPerSec(joystick.joy1_x2, joystick.joy1_x1);
		int Y_Velocity = JoystickToMetersPerSec(joystick.joy1_y2, joystick.joy1_x1);
		int Z_Velocity = JoystickToRadsPerSec(joystick.joy1_x1);


		for (MotorEnum p; p < BACK_RIGHT; p++)
		{
			Drive[p].Zangle = CalculateDriveAngle(X_Velocity, Y_Velocity, Z_Velocity, p);
			Drive[p].speedXY = CalculateDriveSpeed(X_Velocity, Y_Velocity, Z_Velocity, p);
			SetDriveVelocity(Drive[p].speedXY, Drive[p].Zangle, p);//writing this has redundant properties. needs a redo
		}
		WriteToDevices();
	}
}
#endif
