///////////// CODE REVIEW BY DRYW ///////////////////
// Should have #ifndef wrapping
// Comments need to be added for clarity#include "drivers/common.h"

#include "I2C.h"

void Servos_SetPosition(tSensors Port, int DaisyChainLevel, int ServoNumber, int Position)
{
	I2C_WritePMW(Port, DaisyChainLevel, 0);
	I2C_MoveServo(Port, DaisyChainLevel, ServoNumber, Position);
}
