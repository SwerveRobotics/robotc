//
// JudgingDemo.c
//
#define ROBOT_NAME  ROBOT_NAME_FTC417_2011_V1

#include "..\lib\MainPrelude.h"
#include "config\RobotConfig.h"
#include "..\lib\MainPostlude.h"
#include "TeleOp.h"

task main()
	{
	if(InitializeMain(true, true))
		{
		StartReadingTouchSensor(touchForklift);
        SpeculativelyUpdateBlackboard();

        // Tines down
        UpDownTine(svoLeftTineUpDown,  TINE_LOC_DOWN);
        UpDownTine(svoRightTineUpDown, TINE_LOC_DOWN);
        UpDownTine(svoLeftTineUpDown,  TINE_LOC_NONE);
        UpDownTine(svoRightTineUpDown, TINE_LOC_NONE);
        wait1Msec(1000);

        // Tines up
        UpDownTine(svoLeftTineUpDown,  TINE_LOC_UP);
        UpDownTine(svoRightTineUpDown, TINE_LOC_UP);
        UpDownTine(svoLeftTineUpDown,  TINE_LOC_NONE);
        UpDownTine(svoRightTineUpDown, TINE_LOC_NONE);
        wait1Msec(1000);

        // Tines close
        OpenCloseTine(svoLeftTineOpenClose,  TINE_DIR_RIGHT);
        OpenCloseTine(svoRightTineOpenClose, TINE_DIR_LEFT);
        wait1Msec(2000);
        OpenCloseTine(svoLeftTineOpenClose,  TINE_DIR_NONE);
        OpenCloseTine(svoRightTineOpenClose, TINE_DIR_NONE);

        // Tines open
        OpenCloseTine(svoLeftTineOpenClose,  TINE_DIR_LEFT);
        OpenCloseTine(svoRightTineOpenClose, TINE_DIR_RIGHT);
        wait1Msec(1000);
        OpenCloseTine(svoLeftTineOpenClose,  TINE_DIR_NONE);
        OpenCloseTine(svoRightTineOpenClose, TINE_DIR_NONE);

        // Mast up
        ENCOD encMastTop = encMastBottom + 1440 * 5;
        ENCOD encCur;
        ReadEncoder(OUT encCur, motorForklift);
        while(encCur < encMastTop)
            {
            ReadEncoder(OUT encCur, motorForklift);
	        UpDownMast(motorForklift, MAST_DIR_UP, 100);
	        }
	    UpDownMast(motorForklift, MAST_DIR_NONE, 0);
return;
        // Mast down slowly
        while(!touchForklift.fvalue)
	        {
	        UpDownMast(motorForklift, MAST_DIR_DOWN, -100);
	        }
	    UpDownMast(motorForklift, MAST_DIR_NONE, 0);
		}
	}
