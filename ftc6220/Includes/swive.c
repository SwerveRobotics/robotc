#ifndef SWIVE_C
#define SWIVE_C

#include "../../library/drive_modes/swerve_4m.c"
#include "JoystickDriver.c"

// MOVE SWERVE CONSTANTS HERE //


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

		int X_Velocity = JoystickToMetersPerSec(joyX2, joyX1);
		int Y_Velocity = JoystickToMetersPerSec(joyY2, joyX1);
		int Z_Velocity = JoystickToRadsPerSec(joyX1);


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
