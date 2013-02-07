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
#include "C:\ftc\drivers\2.3\drivers\HTIRS2-driver.h"

task main ()
{
    waitForStart(); //wait until FCS tells us to go

    // zero encoders
    nMotorEncoder[motorLeft] = 0;
    nMotorEncoder[motorRight] = 0;
    nMotorEncoder[motorArm] = 0;
    servo[servoWristLeft] = 0;
    servo[servoWristRight] = 180;
    servo[servoLeft] = 100;
    servo[servoRight] = 160;

    //create variables to store sensor outputs and set it to AC 1200Hz
    int dirAC = 1;
    tHTIRS2DSPMode mode = DSP_1200;

    dirAC = HTIRS2readACDir(irsensor);
    writeDebugStreamLine("dir=%d", dirAC);

    if(dirAC == 5)
    {
        while(nMotorEncoder[motorLeft] < (1440 * 59.25 /(4 * PI)))
        {
            motor[motorLeft] = 50;
            motor[motorRight] = 50;
        }

        nMotorEncoder[motorLeft] = 0;

        while(nMotorEncoder[motorLeft] < (1440 * 0.45))
        {
            motor[motorLeft] = 50;
            motor[motorRight] = -50;
        }

        nMotorEncoder[motorLeft] = 0;

        while(nMotorEncoder[motorLeft] < (1440 * 5 /(4 * PI)))
        {
            motor[motorLeft] = 75;
            motor[motorRight] = 75;
        }

        motor[motorLeft] = 0;
        motor[motorRight] = 0;

        while(nMotorEncoder[motorArm] < (1440 * 0.9))
        {
            motor[motorArm] = 100;
        }

        motor[motorArm] = 0;

        servo[servoWristLeft] = 75;
        servo[servoWristRight] = 105;
        wait1Msec(500);

        while(nMotorEncoder[motorArm] > 0)
        {
            motor[motorArm] = -100;
        }
        motor[motorArm] = 0;

        servo[servoLeft] = 200;
        servo[servoRight] = 50;
        wait1Msec(250);

        while(nMotorEncoder[motorLeft] > (1440 /(4 * PI)))
        {
            motor[motorLeft] = -50;
            motor[motorRight] = -50;
        }
        motor[motorLeft] = 0;
        motor[motorRight] = 0;
    }
    else if(dirAC == 6)
    {
        while(nMotorEncoder[motorLeft] < (1440 * 30 /(4 * PI)))
        {
            motor[motorLeft] = 50;
            motor[motorRight] = 50;
        }

        nMotorEncoder[motorLeft] = 0;

        while(nMotorEncoder[motorLeft] < (1440 * 0.53))
        {
            motor[motorLeft] = 50;
            motor[motorRight] = -50;
        }

        nMotorEncoder[motorLeft] = 0;

        while(nMotorEncoder[motorLeft] < (1440 * 26.5 /(4 * PI)))
        {
            motor[motorLeft] = 75;
            motor[motorRight] = 75;
        }

        motor[motorLeft] = 0;
        motor[motorRight] = 0;

        while(nMotorEncoder[motorArm] < (1440 * 0.9))
        {
            motor[motorArm] = 100;
        }

        motor[motorArm] = 0;

        servo[servoWristLeft] = 75;
        servo[servoWristRight] = 105;
        wait1Msec(500);

        while(nMotorEncoder[motorArm] > 0)
        {
            motor[motorArm] = -100;
        }
        motor[motorArm] = 0;

        servo[servoLeft] = 200;
        servo[servoRight] = 50;
        wait1Msec(250);

        while(nMotorEncoder[motorLeft] > (1440 * 20 /(4 * PI)))
        {
            motor[motorLeft] = -50;
            motor[motorRight] = -50;
        }
        motor[motorLeft] = 0;
        motor[motorRight] = 0;
    }
    else if(dirAC == 7)
    {
        while(nMotorEncoder[motorLeft] < (1440 * 1 /(4 * PI)))
        {
            motor[motorLeft] = 50;
            motor[motorRight] = 50;
        }

        nMotorEncoder[motorLeft] = 0;

        while(nMotorEncoder[motorLeft] < (1440 * 0.72))
        {
            motor[motorLeft] = 50;
            motor[motorRight] = -50;
        }

        nMotorEncoder[motorLeft] = 0;

        while(nMotorEncoder[motorLeft] < (1440 * 47 /(4 * PI)))
        {
            motor[motorLeft] = 75;
            motor[motorRight] = 75;
        }

        motor[motorLeft] = 0;
        motor[motorRight] = 0;

        while(nMotorEncoder[motorArm] < (1440 * 1))
        {
            motor[motorArm] = 100;
        }

        motor[motorArm] = 0;

        servo[servoWristLeft] = 75;
        servo[servoWristRight] = 105;
        wait1Msec(500);

        while(nMotorEncoder[motorArm] > 100)
        {
            motor[motorArm] = -100;
        }
        motor[motorArm] = 0;

        servo[servoLeft] = 200;
        servo[servoRight] = 50;
        wait1Msec(250);

        while(nMotorEncoder[motorLeft] > (1440 * 20 /(4 * PI)))
        {
            motor[motorLeft] = -50;
            motor[motorRight] = -50;
        }
        motor[motorLeft] = 0;
        motor[motorRight] = 0;
    }
}
