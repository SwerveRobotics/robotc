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

	int lastX[10];
	int lastY[10];
	int lastZ[10];
	float product = 1;

	bool rotTrans = true;
	float slowModeFactor = 1.0;
	float radius = 35;
	while(true)
	{
		getJoystickSettings(joystick);

		joyX2 = joystick.joy1_x2;
		joyX1 = joystick.joy1_x1;
		joyY2 = joystick.joy1_y2;


		/// !!! begin experimental FIR !!! ///
		/*
		lastX[1] = abs(joyX2);
		lastY[1] = abs(joyY2);
		lastZ[1] = abs(joyX1);

		productX = 1;
		productY = 1;
		productZ = 1;
		for(int n = 2; n++; n < 11)
		{
			lastX[n] = lastX[n-1];
			lastY[n] = lastY[n-1];
			lastZ[n] = lastZ[n-1];

			//these values will aproach 2 if power is held at 100%
			productX = productX * (lastX[n] / n)
			productY = productY * (lastY[n] / n)
			productZ = productZ * (lastZ[n] / n)
		}
		*/
		/// !!!/ end experimental FIR !!! ///

		float X_Velocity = JoystickToCMPerSec(joyX2, joyX1);
		float Y_Velocity = JoystickToCMPerSec(joyY2, joyX1);
		float Z_Velocity = JoystickToRadsPerSec(joyX1);

		if (joystick.joy1_Buttons == 7)
		{
			slowModeFactor = 0.4;
		}
		else
		{
			slowModeFactor = 1.0;
		}

		if (rotTrans == true)
		{
			for (MotorEnum p; p < BACK_RIGHT; p++)
			{
				Drive[p].servoPosition = CalculateDriveAngle(X_Velocity, Y_Velocity, Z_Velocity, p);
				Drive[p].motorPower = CalculateDriveSpeed(X_Velocity, Y_Velocity, Z_Velocity, p) * slowModeFactor * reverseMotorFactor;
			}
			WriteToMotorsInd();
			WriteToServosInd();
		}
		if (joystick.joy1_Buttons == 5)
		{

			rotTrans = false;
			if (abs(joystick.joy1_y2) > 20)
			{
				radius = radius + joystick.joy1_y2 * 0.01;
			}
			RadialDrive(MAX_MOTOR_SPEED_CMPS * slowModeFactor, radius);
		}
		else if (joystick.joy1_Buttons == 6)
		{

			rotTrans = false;
			if (abs(joystick.joy1_y2) > 20)
			{
				radius = radius + joystick.joy1_y2 * 0.01;
			}
			RadialDrive(-1 * MAX_MOTOR_SPEED_CMPS * slowModeFactor, radius);
		}
		else
		{
			rotTrans = true;
			radius = 35;
		}

	}
}
#endif
