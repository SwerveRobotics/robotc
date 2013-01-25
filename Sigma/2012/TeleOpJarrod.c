#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irsensor,       sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorArm,      tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorRight,    tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorNone, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoRight,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servoWristRight,      tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servoLeft,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servoWristLeft,       tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int deadZone = 5;

//variables used for stall code
long timeStalling[3]; //amount of time the motors are stalling
int valueOfLastMove[3]; //the value of the encoders when the motor last moved
long timeStoppedMoving[3]; //the time the motors stopped

void InitializeStallCode()
{
	for(int i = 0; i <3; i++)
	{
		timeStalling[i] = 0;
		valueOfLastMove[i] = 0;
		timeStoppedMoving[i] = 0;
	}
}

int StallCode(int motorSentTo, int wantedPower)
{
	int motorIndex;//index value for the arrays
	switch(motorSentTo)//which motor power is being sent to
	{
		case motorLeft:
		motorIndex = 0;
		break;
		case motorRight:
		motorIndex = 1;
		break;
		case motorArm:
		default:
		motorIndex = 2;
		break;
	}
  int cur = nMotorEncoder[motorSentTo];//current encoder value of motor

if((wantedPower < -30 || wantedPower > 30)&&(cur == valueOfLastMove[motorIndex]))
{
	if(timeStalling[motorIndex] + 150 >= time1[T1])
	{
		if(timeStoppedMoving[motorIndex] == 0)
		{
			timeStoppedMoving[motorIndex] = time1[T1];
		}
		if(timeStoppedMoving[motorIndex] + 10 >= time1[T1])
		{
			return 0;
		}
		else
		{
		    valueOfLastMove[motorIndex] = cur;
			timeStoppedMoving[motorIndex] = 0;
			timeStalling[motorIndex] = time1[T1];
		}
	}
	return wantedPower;
}
timeStalling[motorIndex] = time1[T1];
return wantedPower;
}

void OpenHand()
{
    servo[servoLeft] = 200;
    servo[servoRight] = 50;
}

void CloseHand()
{
    servo[servoLeft] = 100;
    servo[servoRight] = 160;
}

void MoveArm(int power)
{
    motor[motorArm] = power;
}

task main ()
{
    waitForStart(); // wait until FCS lets us go
    ClearTimer(T1);
    InitializeStallCode();

    while(true) // infinite loop
    {
        //writeDebugStreamLine("%d", (joystick.joy1_y1 >> 4));
        getJoystickSettings(joystick);

        // medium mode
        if(joy1Btn(7) == 1) // if the lower left trigger is pressed on controller 1 ...
        {
            if(abs(joystick.joy1_y1) > deadZone) // and the left joystick value on controller 1 isn't in the deadzone ...
            {
                motor[motorLeft]  = StallCode(motorLeft, (joystick.joy1_y1) / 2); // set the left motor power to the left joystick value on controller 1 divided by 3
                //writeDebugStreamLine("left %d", nMotorEncoder[motorLeft]);
            }
            else
            {
                motor[motorLeft] = StallCode(motorLeft, 0); // if the left joystick value is in the deadzone set the left motor power to 0
            }

            if(abs(joystick.joy1_y2) > deadZone) // and the right joystick value on controller 1 isn't in the deadzone ...
            {
                motor[motorRight] = StallCode(motorRight, (joystick.joy1_y2) / 2); // set the right motor power to the right joystick value on controller 1 divided by 3
                //writeDebugStreamLine("right %d", nMotorEncoder[motorRight]);
            }
            else
            {
                motor[motorRight] = StallCode(motorRight, 0); // if the left joystick value is in the deadzone set the right motor power to 0
            }
        }
        // slow mode
        if(joy1Btn(8) == 1) // if the lower left trigger is pressed on controller 1 ...
        {
            if(abs(joystick.joy1_y1) > deadZone) // and the left joystick value on controller 1 isn't in the deadzone ...
            {
                motor[motorLeft]  = StallCode(motorLeft, (joystick.joy1_y1) / 4); // set the left motor power to the left joystick value on controller 1 divided by 3
                //writeDebugStreamLine("left %d", nMotorEncoder[motorLeft]);
            }
            else
            {
                motor[motorLeft] = StallCode(motorLeft, 0); // if the left joystick value is in the deadzone set the left motor power to 0
            }

            if(abs(joystick.joy1_y2) > deadZone) // and the right joystick value on controller 1 isn't in the deadzone ...
            {
                motor[motorRight] = StallCode(motorRight, (joystick.joy1_y2) / 4); // set the right motor power to the right joystick value on controller 1 divided by 3
                //writeDebugStreamLine("right %d", nMotorEncoder[motorRight]);
            }
            else
            {
                motor[motorRight] = StallCode(motorRight, 0); // if the left joystick value is in the deadzone set the right motor power to 0
            }
        }
        else // regular mode
        {
            if(abs(joystick.joy1_y1) > deadZone) // if the left joystick value isn't in the deadzone ...
	        {
	            motor[motorLeft]  = StallCode(motorLeft, joystick.joy1_y1); // set the left motor power to the left joystick value on controller 1
	        }
	        else
	        {
	            motor[motorLeft] = StallCode(motorLeft, 0); // if the left joystick value is in the deadzone set the left motor power to 0
	        }

	        if(abs(joystick.joy1_y2) > deadZone) // if the right joystick value isn't in the deadzone ...
	        {
	            motor[motorRight] = StallCode(motorRight, joystick.joy1_y2); // set the right motor power to the right joystick value on controller 1
	        }
	        else
	        {
	            motor[motorRight] = StallCode(motorRight, 0); // if the left joystick value is in the deadzone set the right motor power to 0
	        }
        }

        if(joy2Btn(1) == 1) // if button 1 on controller 2 is pressed
        {
            OpenHand();
        }
        else if(joy2Btn(3) == 1) // if button 3 on controller 2 is pressed
        {
            CloseHand();
        }

        if(joystick.joy2_TopHat == 0) // if up on the dpad on controller 2 is pressed
        {
            motor[motorArm] = 100;//StallCode(motorArm, 100);
        }
        else if(joystick.joy2_TopHat == 4) // if down on the dpad on controller 2 is pressed
        {
            motor[motorArm] = -100;//StallCode(motorArm, -100);
        }
        else
        {
            motor[motorArm] = 0;//StallCode(motorArm, 0); // set to 0 if nothing is pressed.
        }

        servo[servoWristLeft] = ((joystick.joy2_y1 + 128) * (180.0/255.0)) - 90;
        servo[servoWristRight] = ((127 - joystick.joy2_y1) * (180.0/255.0)) + 90;
    }
}
