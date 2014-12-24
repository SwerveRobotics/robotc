#ifndef DRIVE_MODES_H
#define DRIVE_MODES_H

#ifdef TANK_2M
#include "../drive_modes/tank_2m.c"
#else
#ifdef TANK_4M
#include "../drive_modes/tank_4m.c"
#else
#ifdef TANK_6M
#include "../drive_modes/tank_6m.c"
#endif
#endif
#endif

#endif
