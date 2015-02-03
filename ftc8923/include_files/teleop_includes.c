#ifndef INCLUDES_H
#define INCLUDES_H

#include "../drivers/hitechnic-sensormux.h"
#include "../drivers/lego-touch.h"
#include "../drivers/hitechnic-irseeker-v2.h"
// The sensor define has to be here for the next few files
const tMUXSensor touchSensor = msensor_S3_1;
const tMUXSensor irSensor = msensor_S3_2;
#include "../Library/controllers/tank_controller.c"
#include "include_files/functions.c"
#include "include_files/init_teleop.c"

#endif
