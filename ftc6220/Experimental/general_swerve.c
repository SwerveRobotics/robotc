#ifndef SIMPLESWERVE_4M_C
#define SIMPLESWERVE_4M_C

#include "../controllers/controller_defines.h"

// these variables will be used to write to the motors and servos
tMotor FRONT_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;

TServoIndex FRONT_LEFT_SERVO;
TServoIndex BACK_LEFT_SERVO;
TServoIndex FRONT_RIGHT_SERVO;
TServoIndex BACK_RIGHT_SERVO;


const float LARGEST_CENTER_RADIUS = 0.2286;

const float MAX_MOTOR_GEAR_RATIO = 1.0;

const float MAX_MOTOR_SPEED_MPS = 0.8193;//theoretical max based on 154rpm motor and 4in diameter wheel // gear ratio?
const float MOTOR_POWER_PER_MPS = 120.7671; //theoretical motor power nessesary to move at 1 m/s

//min and max values the servo can be sent to     //shouldnt these be given?
const int MAX_SERVO_VAL = 255;
const int MIN_SERVO_VAL = 0;

const float MAX_SERVO_ANGLE = PI/2.0;
const float MIN_SERVO_ANGLE = -PI/2.0;

const float SERVO_ANGLE_TO_VAL = ((MAX_SERVO_VAL - MIN_SERVO_VAL) / (MAX_SERVO_ANGLE - MIN_SERVO_ANGLE));

int joystickRange = MAX_ANALOG - ANALOG_DEAD_ZONE; //allowed input range along any axis from the joystick.

//MotorEnum datatype used to refer to each of the four drive modules
typedef enumWord
{
	FRONT_RIGHT,
	FRONT_LEFT,
	BACK_LEFT,
	BACK_RIGHT,
}
	MotorEnum;

//swerve module structure for storing all values specific to any given drive assembly
typedef struct
{

	int servoPosition;     	//in servo position units (0 - 255)
	int motorPower;         //in motor power units (0 - 100)

	float offsetAngle;      //assuming that 90deg is forward. In radians.
	float radiusFromCenter; //distance from the driving center of the robot:

	float motorGearRatio;   //between motor and wheel
	float servoGearRatio;   //between servo and turntable
	float wheelRadius;

	int speedXY;
	int Zangle;
}
DriveAssemblyState;

DriveAssemblyState Drive[4];


//-------------------------------------------------------------------------------------------------//
// !!! IMPORTANT - The following three functions MUST be called, else the drive will not work. !!! //maybe
//-------------------------------------------------------------------------------------------------//

//register the motors
void RegisterDriveMotors(tMotor frontLeftM, tMotor backLeftM, tMotor frontRightM, tMotor backRightM)
{
	FRONT_LEFT_MOTOR = frontLeftM;
	BACK_LEFT_MOTOR = backLeftM;
	FRONT_RIGHT_MOTOR = frontRightM;
	BACK_RIGHT_MOTOR = backRightM;
}

//register the servos
void RegisterDriveServos(TServoIndex frontLeftS, TServoIndex backLeftS, TServoIndex frontRightS, TServoIndex backRightS)
{
	FRONT_LEFT_SERVO = frontLeftS;
	BACK_LEFT_SERVO = backLeftS;
	FRONT_RIGHT_SERVO = frontRightS;
	BACK_RIGHT_SERVO = backRightS;
}

//initializes the drive assembly by setting all the values in the drive assembly structures
void initializeDriveAssemblies()
{
	//  FRONT_RIGHT Swerve Drive Module   //
	Drive[FRONT_RIGHT].offsetAngle      = PI / 4.0;
	Drive[FRONT_RIGHT].radiusFromCenter = 0.2286;
	Drive[FRONT_RIGHT].motorGearRatio   = 1.0;
	Drive[FRONT_RIGHT].servoGearRatio   = 1.0;
	Drive[FRONT_RIGHT].wheelRadius      = 0.0508;

	//  FRONT_LEFT Swerve Drive Module   //
	Drive[FRONT_LEFT].offsetAngle      = 3.0 * PI / 4.0;
	Drive[FRONT_LEFT].radiusFromCenter = 0.2286;
	Drive[FRONT_LEFT].motorGearRatio   = 1.0;
	Drive[FRONT_LEFT].servoGearRatio   = 1.0;
	Drive[FRONT_LEFT].wheelRadius      = 0.0508;

	//  BACK_RIGHT Swerve Drive Module   //
	Drive[BACK_LEFT].offsetAngle      = 5.0 * PI / 4.0;
	Drive[BACK_LEFT].radiusFromCenter = 0.2286;
	Drive[BACK_LEFT].motorGearRatio   = 1.0;
	Drive[BACK_LEFT].servoGearRatio   = 1.0;
	Drive[BACK_LEFT].wheelRadius      = 0.0508;

	//  BACK_RIGHT Swerve Drive Module   //
	Drive[BACK_RIGHT].offsetAngle      = 7.0 * PI / 4.0;
	Drive[BACK_RIGHT].radiusFromCenter = 0.2286;
	Drive[BACK_RIGHT].motorGearRatio   = 1.0;
	Drive[BACK_RIGHT].servoGearRatio   = 1.0;
	Drive[BACK_RIGHT].wheelRadius      = 0.0508;
}



//--------------------------------------//
//   !!! End of required funtions !!!   //
//--------------------------------------//






//Attenuate the joystick used for rotation based on the maximum angular speed possible
//and find the "desired" angular velocity.
float JoystickToRadiansPerSecond(int joystickZPosition)
{
	float maxRadiansPerSecond= (MAX_MOTOR_SPEED_MPS * MAX_MOTOR_GEAR_RATIO) / LARGEST_CENTER_RADIUS;
	//maximum rotational speed possible.

	float attenuationSlope =  maxRadiansPerSecond / joystickRange;
	//mapping maximum rotational speed to the allowed joystick input range, aka. finding the slope.

	float attenuationIntercept = sgn(joystickZPosition) * attenuationSlope * ANALOG_DEAD_ZONE;	//check for /0
	//finding the range taken up by the dead zone, aka. finding the intercept.

	float angularVelocity = (attenuationSlope * joystickZPosition) + attenuationIntercept;
	//slope-intercept form of attenuation.

	return angularVelocity;	//this is the "desired" angular velocity based on the joystick input above.
}

//Attenuate the joystick inputs being used for planar motion based on the maximum linear speed possible in any direction at this instant.
//Which is in turn scaled off of the current angular speed. This means that the angular velocity limits the linear velocity.
int JoystickToMetersPerSecond(int joystickXorYPosition, int joystickZPosition)
{

	float fastestMotorSpeedInRotationalComponent = JoystickToRadiansPerSecond(joystickZPosition) * LARGEST_CENTER_RADIUS; //find the largest component of motor velocity used to rotate the robot (limiting factor)
	float maximumLinearSpeed = sqrt( pow(MAX_MOTOR_SPEED_MPS, 2) - pow(fastestMotorSpeedInRotationalComponent, 2)); //calculate the maximum linear speed "left over" from the current rotational motion.
	float attenuationSlope = maximumLinearSpeed / joystickRange;	//map the maximum linear speed to the joystick range, aka. finding the slope.
	float attenuationIntercept = sgn(joystickXorYPosition) * attenuationSlope * ANALOG_DEAD_ZONE;	//finding the range taken by the dead zone, aka. finding the intercept.
	float linearVelocityInXorY = attenuationSlope * joystickXorYPosition + attenuationIntercept;	//slope-intercept for of attenuation.
	return linearVelocityInXorY; // this is the "desired" linear velocity along whichever axis this was applied to.
}

//calculate the direction a drive assembly should be pointed in:
//velocityX is the horizontal (Side-to-side) component of the desired robot motion in m/s.
//velocityY is the vertical (Front-to-back) component in m/s.
//velocityZ is the angular (Round and round) component in rad/s.
//This reference frame is relative to the robot in all instances, meaning the angular argument drives it kind of like a car.
float CalculateDriveAngle(float velocityX, float velocityY, float velocityZ, MotorEnum driveIdentifier)
{
	//used the arctangent function to find the angular component of the velocity vector for the chosen motor
	float driveXComponent = velocityX + (velocityZ * Drive[driveIdentifier].radiusFromCenter * cos(Drive[driveIdentifier].offsetAngle)); //find the component of the drive assembly velocity that is in X.
	float driveYComponent = velocityY - (velocityZ * Drive[driveIdentifier].radiusFromCenter * sin(Drive[driveIdentifier].offsetAngle)); //find the component of the drive assembly velocity that is in Y.
	float driveAngle = atan(driveXComponent / driveYComponent); //use atan function to find the angle the drive assembly in question should be pointed at.
	return driveAngle;
}

//Calculate the speed that a drive assembly should be traveling at:
//velocityX is the horizontal (Side-to-side) component of the desired robot motion in m/s
//velocityY is the vertical (Front-to-back) component in m/s
//velocityZ is the angular (Round and round) component in rad/s
//This reference frame is relative to the robot in all instances, meaning the angular argument drives it kind of like a car.
float CalculateDriveSpeed(float velocityX,float velocityY,float velocityZ, MotorEnum driveIdentifier)
{
	float driveXComponent = velocityX + (velocityZ * Drive[driveIdentifier].radiusFromCenter * cos(Drive[driveIdentifier].offsetAngle)); //find the component of the drive assembly velocity that is in X.
	float driveYComponent = velocityY - (velocityZ * Drive[driveIdentifier].radiusFromCenter * sin(Drive[driveIdentifier].offsetAngle)); //find the component of the drive assembly velocity that is in Y.
	float driveSpeed = sqrt(pow(driveXComponent, 2) + pow(driveYComponent, 2)); //find the speed the drive assembly in question should be moving at.
	return driveSpeed;
}

//Convert from SI units to MotorPower and Servo Position units, then set the motorPower and servoPosition arguments of the motor in question accordingly.
void SetDriveVelocity(float driveSpeed, float driveAngle, MotorEnum driveIdentifier)
{
	Drive[driveIdentifier].motorPower = MOTOR_POWER_PER_MPS * Drive[driveIdentifier].motorGearRatio * driveSpeed;
	Drive[driveIdentifier].servoPosition = SERVO_ANGLE_TO_VAL * Drive[driveIdentifier].servoGearRatio * driveAngle;
}

void WriteToDevices(){

	motor[FRONT_RIGHT_MOTOR] =  drive[FRONT_RIGHT].motorPower;
	motor[FRONT_LEFT_MOTOR]  =  drive[FRONT_LEFT].motorPower;
	motor[BACK_LEFT_MOTOR]   =  drive[BACK_LEFT].motorPower;
	motor[BACK_RIGHT_MOTOR]  =  drive[BACK_RIGHT].motorPower;

	servo[FRONT_RIGHT_SERVO] =  drive[FRONT_RIGHT].servoPosition;
	servo[FRONT_LEFT_SERVO]  =  drive[FRONT_RIGHT].servoPosition;
	servo[BACK_LEFT_SERVO]   =  drive[BACK_LEFT].servoPosition;
	servo[BACK_RIGHT_SERVO]  =  drive[BACK_RIGHT].servoPosition;
}

/*
The actual driver controlled portion of the program looks something like this then:

	RegisterDriveMotors(FLM, BLM, FRM, BRM);

	RegisterDriveServos(FLS, BLS, FRS, BRS);

	// SetPhysicalConfiguration() // defaults are fine

	InitializeDriveAssemblies();

	while(true)
	{

		getJoyStickSettings(joystick.joy1_x1);
		getJoystickSettings(joystick.joy1_y1);
		getJoystickSettings(joystick.joy2_x1);

			for (MotorEnum index; index < 4; index++)
		{
			SetDriveVelocity(
			(CalculateDriveSpeed(JoystickToMetersPerSecond(joystick.joy1_x, 1joystick.joy2_x1), JoystickToMetersPerSecond(joystick.joy1_y1, joystick.joy2_x1), JoystickToRadiansPerSecond(joystick.joy2_x1), index),
			 CalculateDriveAngle(JoystickToMetersPerSecond(joystick.joy1_x, 1joystick.joy2_x1), JoystickToMetersPerSecond(joystick.joy1_y1, joystick.joy2_x1), JoystickToRadiansPerSecond(joystick.joy2_x1), index),
			 index)
		}
	}

And autonomous is basically a sequence of moves input by the same function, but replacing the joystick calculations with values. Some additional tools for autonomous need to be written.

*/

#endif
