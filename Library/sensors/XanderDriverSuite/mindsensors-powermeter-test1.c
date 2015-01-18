#pragma config(Sensor, S1,     MSPOWER,             sensorI2CCustomFastSkipStates)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: mindsensors-powermeter-test1.c 133 2013-03-10 15:15:38Z xander $
 */

/**
 * mindsensors-powermeter.h provides an API for the Mindsensors Power Meter Sensor. This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 16 December 2009
 * version 0.1
 */

#include "drivers/mindsensors-powermeter.h"

int voltage = 0;
int current = 0;
bool scaleChanged = false;
int vscale = 0;
int cscale = 0;

typedef enum {
  showvoltage,
  showcurrent
} tDisplayUnit;

tDisplayUnit displayUnit;

/**
 * Wait until no button is pressed. Also known as debouncing.
 */
void debounce() {
  while(nNxtButtonPressed != kNoButton) {
     wait1Msec(1);
  }
}

void doDrawPoint(int top, int x_pos, int y_pos) {
	nxtEraseRect(x_pos, 63, x_pos+5, 0);
	if (displayUnit == showcurrent)
	  nxtDisplayCenteredTextLine(7, "Max: %d mA", top);
	else if (displayUnit == showvoltage)
	  nxtDisplayCenteredTextLine(7, "Max: %d mV", top);
	nxtDisplayStringAt(0, 12, "0");
	nxtDrawLine(10, 10, 10, 60);
	nxtDrawLine(10, 10, 15, 10);
	nxtDrawLine(10, 35, 15, 35);
	nxtDrawLine(10, 60, 15, 60);

	nxtSetPixel(x_pos, y_pos);
}

int scaleToTop() {
  // scales (amps)
  // 0: 0 -   50 mA
  // 1: 0 -  100 mA
  // 2: 0 -  500 mA
  // 3: 0 - 1000 mA
  // 4: 0 - 3000 mA

  // scales (volts)
  // 0: 0 -   100 mV
  // 1: 0 -   500 mV
  // 2: 0 -  1000 mV
  // 3: 0 -  5000 mV
  // 4: 0 - 13500 mV
  if (displayUnit == showcurrent) {
	  switch (cscale) {
	    case 0: return 50; break;
	    case 1: return 100; break;
	    case 2: return 500; break;
	    case 3: return 1000; break;
	    case 4: return 3000; break;
	  }
	} else if (displayUnit == showvoltage) {
	  switch (vscale) {
	    case 0: return 100; break;
	    case 1: return 500; break;
	    case 2: return 1000; break;
	    case 3: return 5000; break;
	    case 4: return 13500; break;
	  }
  }
  return 0;
}

task displayCardio () {
  int top = 0;
  int y_val = 0;
  eraseDisplay();
  while (true) {
    for (int i = 10; i < 99; i++) {
      top = scaleToTop();
      if (displayUnit == showcurrent) {
        y_val = (((long)current * 50) / top) + 10;
        if (current > top) {
          cscale++;
          scaleChanged = true;
        }
      } else if (displayUnit == showvoltage) {
        y_val = (((long)voltage * 50) / top) + 10;
        if (voltage > top) {
          vscale++;
          scaleChanged = true;
        }
      }
      if (scaleChanged) {
        eraseDisplay();
        scaleChanged = false;
        i = 100;
      } else {
	      doDrawPoint(top, i, y_val);
	      wait1Msec(20);
	    }
    }
  }
}

task main {
  nNxtButtonTask = -2;
  nNxtExitClicks = 3;

  nxtDisplayCenteredTextLine(0, "Mindstorms");
  nxtDisplayCenteredBigTextLine(1, "POWER");
  nxtDisplayCenteredTextLine(3, "Scope");
  nxtDisplayCenteredTextLine(5, "Connect MSPM to");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);

  StartTask(displayCardio);
  while (true) {
    // Using the function below is a much efficient way of fetching both
    // voltage and current info.  You could also fetch them separately.
    if (!MSPMreadVoltageCurrent(MSPOWER, voltage, current)) {
      StopTask(displayCardio);
      wait1Msec(100);
      PlaySound(soundException);
      eraseDisplay();
      nxtDisplayCenteredBigTextLine(2, "ERROR!");
      nxtDisplayCenteredTextLine(4, "Couldn't read");
      nxtDisplayCenteredTextLine(4, "from sensor");
      wait1Msec(2000);
      StopAllTasks();
    }



    switch(nNxtButtonPressed) {
      case kEnterButton:
        displayUnit = (displayUnit == showvoltage) ? showcurrent : showvoltage;
        scaleChanged = true;
        debounce();
        break;
      case kRightButton:
        if (displayUnit == showcurrent) {
	        if (cscale == 4) cscale = 0;
	        else cscale++;
	      } else if (displayUnit == showvoltage) {
					if (vscale == 4) vscale = 0;
					else vscale++;
				}
				scaleChanged = true;
        debounce();
        break;
      case kLeftButton:
        if (displayUnit == showcurrent) {
	        if (cscale == 0) cscale = 4;
	        else cscale--;
	      } else if (displayUnit == showvoltage) {
					if (vscale == 0) vscale = 4;
					else vscale--;
				}
        scaleChanged = true;
        debounce();
        break;
    }
    wait1Msec(1);
  }
}

/*
 * $Id: mindsensors-powermeter-test1.c 133 2013-03-10 15:15:38Z xander $
 */
