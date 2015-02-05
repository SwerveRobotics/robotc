#ifndef INCLUDES_H
#define INCLUDES_H

#include "../../drivers/hitechnic-sensormux.h"
#include "../drivers/lego-touch.h"
#include "../drivers/hitechnic-irseeker-v2.h"
// The sensor define has to be here for the next few files
const tMUXSensor touchSensor = msensor_S3_1;
const tMUXSensor irSensor = msensor_S3_2;
#include "../../Library/sensors/ir_seeker.c"
#include "../../Library/drive/gyro_drive.c"
#include "functions.c"
#include "init_auto.c"
#include "center_objectives.c"
#include "JoystickDriver.c"

#endif
