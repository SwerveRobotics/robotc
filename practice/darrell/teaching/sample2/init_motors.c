#ifndef INIT_MOTORS_C
#define INIT_MOTORS_C

tMotor LEFT_FRONT;
tMotor LEFT_REAR;
tMotor RIGHT_FRONT;
tMotor RIGHT_REAR;

void InitMotors(tMotor leftFront, tMotor leftRear, tMotor rightFront, tMotor rightRear)
{
	LEFT_FRONT = leftFront;
	LEFT_REAR = leftRear;
	RIGHT_FRONT = rightFront;
	RIGHT_REAR = rightRear;
}

#endif
