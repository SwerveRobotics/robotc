#ifndef DRIVE_MODES_H
#define DRIVE_MODES_H

#ifdef PARALLEL_PAIRS // designed to replace TANK_2M, TANK_4M, and TANK_6M
	#include "../drive_modes/parallel_pairs.c"
#else
	#ifdef TANK_4M
		#include "../drive_modes/tank_4m.c"
	#endif
#endif

#endif
