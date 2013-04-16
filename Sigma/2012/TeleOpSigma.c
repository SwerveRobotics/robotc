#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     touchSensor,    sensorTouch)
#pragma config(Sensor, S3,     IRSensor,       sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorArm,      tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    fingerLeft,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    fingerRight,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servoWrist,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servoIR,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "C:\ftc\drivers\2.3\drivers\HTIRS2-driver.h" //only used in autonomous

int deadZone = 10;
//int motorSentTo;

//variables used for stall code
long timeStalling[] = {0, 0, 0}; //amount of time the motors are stalling
long valueOfLastMove[] = {0, 0, 0}; //the value of the encoders when the motor last moved
long timeStoppedMoving[] = {0, 0, 0}; //the time the motors stopped

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
        motorIndex = 2;
    default:
        break;
    }
    long cur = nMotorEncoder[motorSentTo]; //current encoder value of motor

    if((wantedPower < -15 || wantedPower > 15)&&(cur == valueOfLastMove[motorIndex]))
    {
        if(timeStalling[motorIndex] + 150 >= time1[T1])
        {
            if(timeStoppedMoving[motorIndex] == 0)
            {
                timeStoppedMoving[motorIndex] = time1[T1];
            }
            if(timeStoppedMoving[motorIndex] + 10 >= time1[T1])
            {
                writeDebugStreamLine("stall %d", motorIndex);
                PlayTone(724, 5);
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
    servo[fingerLeft] = 200;
    servo[fingerRight] = 50;
}

void CloseHand()
{
    servo[fingerLeft] = 100;
    servo[fingerRight] = 160;
}

task main()
{
    waitForStart(); // wait until FCS lets us go

    ClearTimer(T1);

    //nMotorEncoder[motorLeft] = 0; //zero encoders
    //nMotorEncoder[motorRight] = 0;
    nMotorEncoder[motorArm] = 0;

    /*if(SensorValue(touchSensor) == 1)
    {
        nMotorEncoder[motorArm] = 0;
    }*/

    while(true) // infinite loop
    {
        getJoystickSettings(joystick);

        // slow mode
        if(joy1Btn(8) == 1) // if the lower left trigger is pressed on controller 1 ...
        {
            if(abs(joystick.joy1_y1) > deadZone) // and the left joystick value on controller 1 isn't in the deadzone ...
            {
                motor[motorLeft]  = StallCode(motorLeft, (joystick.joy1_y1) / 3); // set the left motor power to the left joystick value on controller 1 divided by 3
                //writeDebugStreamLine("left %d", nMotorEncoder[motorLeft]);
            }
            else
            {
                motor[motorLeft] = StallCode(motorLeft, 0); // if the left joystick value is in the deadzone set the left motor power to 0
            }

            if(abs(joystick.joy1_y2) > deadZone) // and the right joystick value on controller 1 isn't in the deadzone ...
            {
                motor[motorRight] = StallCode(motorRight, (joystick.joy1_y2) / 3); // set the right motor power to the right joystick value on controller 1 divided by 3
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

        if(joy2Btn(8) == 1) // if lower right trigger on controller 2 is pressed
        {
            OpenHand();
        }
        else if(joy2Btn(6) == 1) // if upper right trigger on controller 2 is pressed
        {
            CloseHand();
        }

        if (joy2Btn(5) == 1)
        {
            while(nMotorEncoder[motorArm] < (1440 * 0.25))
            {
                motor[motorArm] = 75;
            }
        }

        if (joy2Btn(7) == 1)
        {
            // use dpad on second controller to control arm
            if(joystick.joy2_TopHat == 0) // if up on the dpad on controller 2 is pressed
            {
                motor[motorArm] = StallCode(motorArm, 35);
            }
            else if(joystick.joy2_TopHat == 4) // if down on the dpad on controller 2 is pressed
            {
                if(SensorValue(touchSensor) == 1)
                {
                    motor[motorArm] = StallCode(motorArm, 0);// if touch sensor is pressed and the arm is trying to go down, don't let the arm move
                }
                else if(nMotorEncoder[motorArm] < 100)
                {
                    motor[motorArm] = StallCode(motorArm, -20);// arm goes down slowly
                }
                else
                {
                    motor[motorArm] = StallCode(motorArm, -35);// arm goes down
                }
            }
            // use joystick to control arm
            else if(joystick.joy2_y1 > 50) // if left joystick is up
            {
                motor[motorArm] = StallCode(motorArm, 35); // arm goes up
            }
            else if(joystick.joy2_y1 < -50) // if left joystick is down
            {
                if(SensorValue(touchSensor) == 1)
                {
                    motor[motorArm] = StallCode(motorArm, 0); // if touch sensor is pressed and the arm is trying to go down, don't let the arm move
                }
                else if(nMotorEncoder[motorArm] < 100)
                {
                    motor[motorArm] = StallCode(motorArm, -20); // arm goes down slowly
                }
                else
                {
                    motor[motorArm] = StallCode(motorArm, -35);// arm goes down
                }
            }
            else // left joystick is in the middle
            {
                motor[motorArm] = 0; // arm doesn't move
            }
        }
        else
        {
            // use dpad on second controller to control arm
            if(joystick.joy2_TopHat == 0) // if up on the dpad on controller 2 is pressed
            {
                motor[motorArm] = StallCode(motorArm, 100);
            }
            else if(joystick.joy2_TopHat == 4) // if down on the dpad on controller 2 is pressed
            {
                if(SensorValue(touchSensor) == 1)
                {
                    motor[motorArm] = StallCode(motorArm, 0);// if touch sensor is pressed and the arm is trying to go down, don't let the arm move
                }
                else if(nMotorEncoder[motorArm] < 100)
                {
                    motor[motorArm] = StallCode(motorArm, -20);// arm goes down slowly
                }
                else
                {
                    motor[motorArm] = StallCode(motorArm, -100);// arm goes down
                }
            }
            // use joystick to control arm
            else if(joystick.joy2_y1 > 50) // if left joystick is up
            {
                motor[motorArm] = StallCode(motorArm, 100); // arm goes up
            }
            else if(joystick.joy2_y1 < -50) // if left joystick is down
            {
                if(SensorValue(touchSensor) == 1)
                {
                    motor[motorArm] = StallCode(motorArm, 0); // if touch sensor is pressed and the arm is trying to go down, don't let the arm move
                }
                else if(nMotorEncoder[motorArm] < 100)
                {
                    motor[motorArm] = StallCode(motorArm, -20); // arm goes down slowly
                }
                else
                {
                    motor[motorArm] = StallCode(motorArm, -100);// arm goes down
                }
            }
            else // left joystick is in the middle
            {
                motor[motorArm] = 0; // arm doesn't move
            }
        }
        int pos = joystick.joy2_y2;
        /* (pos < 0)
        {
        pos = 0;
        }*/
        // use right joystick on second controller to control wrist
        servo[servoWrist] = 255 - (pos * (256 / 128)) - 20;
        //writeDebugStreamLine("%d", 255 - (pos * (256 / 128)));
    }
}
