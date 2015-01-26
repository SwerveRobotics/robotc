#ifndef INCLUDES_H
#define INCLUDES_H

/*Darrell Review
	file should probably reflect the type of includes since you will have two different types
	  autonomous
	  teleop

	autonomous has no need to include the joystick driver.
	If you want to use the same includes file, then you should move the JoystickDriver.c include to the individual files that need it
*/


#include "JoystickDriver.c"
#include "../../../library/drive_modes/parallel_pairs.c"
#include "../../../library/drive_modes/drive_modes.h"
#include "../../../library/controllers/tank_controller.c"
#include "../../../library/drive/gyro_drive.c"

#endif
