#ifndef SWERVE_4M_C
#define SWERVE_4M_C

#include "../controllers/controller_defines.h"
#include "../motors/motors.c"

const float CENTER_RADIUS = 22.86;//centimeters

// these variables will be used to write to the motors and servos
tMotor FRONT_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;


TServoIndex FRONT_LEFT_SERVO;
TServoIndex BACK_LEFT_SERVO;
TServoIndex FRONT_RIGHT_SERVO;
TServoIndex BACK_RIGHT_SERVO;

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
	float offsetAngle;        //in radians

	float servoPosition;     	//in degrees (0 - 360)
	float motorPower;         //in motor power units (0 - 100)

}
DriveAssemblyState;

DriveAssemblyState Drive[4];


//-------------------------------------------------------------------------------------------------//
// !!! IMPORTANT - The following three functions MUST be called, else the drive will not work. !!! //
//-------------------------------------------------------------------------------------------------//

//register the motors clockwise
void RegisterMotors(tMotor frontLeftM, tMotor backLeftM, tMotor frontRightM, tMotor backRightM)
{
	FRONT_LEFT_MOTOR = frontLeftM;
	BACK_LEFT_MOTOR = backLeftM;
	FRONT_RIGHT_MOTOR = frontRightM;
	BACK_RIGHT_MOTOR = backRightM;
}

//register the servos clockwise
void RegisterServos(TServoIndex frontLeftS, TServoIndex backLeftS, TServoIndex frontRightS, TServoIndex backRightS)
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
	Drive[FRONT_RIGHT].offsetAngle     = PI / 4.0;

	//  FRONT_LEFT Swerve Drive Module   //
	Drive[FRONT_LEFT].offsetAngle      = 3.0 * PI / 4.0;

	//  BACK_RIGHT Swerve Drive Module   //
	Drive[BACK_LEFT].offsetAngle       = 5.0 * PI / 4.0;

	//  BACK_RIGHT Swerve Drive Module   //
	Drive[BACK_RIGHT].offsetAngle      = 7.0 * PI / 4.0;

}



//--------------------------------------//
//   !!! End of required funtions !!!   //
//--------------------------------------//




//Attenuate the joystick used for rotation based on the maximum angular speed possible
//and find the "desired" angular velocity.
float JoystickToRadsPerSec(float joystickZ)
{
	float maxRadsPerSecond = (MAX_MOTOR_SPEED_CMPS * MOTOR_GEAR_RATIO) / CENTER_RADIUS;
	//maximum rotational speed possible.

	float attenuationSlope =  maxRadsPerSecond / joystickRange;
	//mapping maximum rotational speed to the allowed joystick input range, aka. finding the slope.

	float attenuationIntercept = -1 * ANALOG_DEAD_ZONE * sgn(joystickZ) * attenuationSlope;
	//finding the range taken up by the dead zone, aka. finding the intercept.

	if (abs(joystickZ) < ANALOG_DEAD_ZONE)
	{
		return 0;
	}
	else
	{
		return attenuationSlope * joystickZ + attenuationIntercept;
	}

}

//Attenuate the joystick inputs being used for planar motion based on the maximum linear speed possible in any
//direction at this instant.
//Which is in turn scaled off of the current angular speed. This means that the angular velocity limits the
//linear velocity.
float JoystickToCMPerSec(float joystickXorY, float joystickZ)
{
	float fastestMotorRotationRate = JoystickToRadsPerSec(joystickZ) * CENTER_RADIUS;
	//find the largest component of motor velocity used to rotate the robot (limiting factor)

	float maximumLinearSpeed = sqrt( pow(MAX_MOTOR_SPEED_CMPS, 2) - pow(fastestMotorRotationRate, 2) );
	//calculate the maximum linear speed "left over" from the current rotational motion.

	float attenuationSlope = maximumLinearSpeed / joystickRange;
	//map the maximum linear speed to the joystick range, aka. finding the slope.

	float attenuationIntercept = -1 * sgn(joystickXorY) * attenuationSlope * ANALOG_DEAD_ZONE;
	//finding the range taken by the dead zone, aka. finding the intercept.

	float linearVelocityInXorY = attenuationSlope * joystickXorY + attenuationIntercept;
	//slope-intercept for of attenuation.

	if (abs(joystickXorY) < ANALOG_DEAD_ZONE)
	{
		return 0;
	}
	else
	{
		return linearVelocityInXorY;
	}
	//return linearVelocityInXorY; // this is the "desired" linear velocity along whichever axis this was applied to.
}

//calculate the direction a drive assembly should be pointed in:
//velocityX is the horizontal (Side-to-side) component of the desired robot motion in m/s.
//velocityY is the vertical (Front-to-back) component in m/s.
//velocityZ is the angular (Round and round) component in rad/s.
//This reference frame is relative to the robot in all instances, meaning the angular argument
//drives it kind of like a car.
float CalculateDriveAngle(float velocityX, float velocityY, float velocityZ, MotorEnum driveIdentifier)
{
	//used the arctangent function to find the angular component of the velocity vector for the chosen motor
	float driveXComponent = velocityX + (velocityZ * CENTER_RADIUS * cos(Drive[driveIdentifier].offsetAngle));
	float driveYComponent = velocityY - (velocityZ * CENTER_RADIUS * sin(Drive[driveIdentifier].offsetAngle));
	int tangent = 57.3 * atan2(driveXComponent, driveYComponent); //drive angle
	if (tangent < 0)
	{
		return tangent + 360;
	}
	else
	{
		return tangent;
	}

}

//Calculate the speed that a drive assembly should be traveling at:
//velocityX is the horizontal (Side-to-side) component of the desired robot motion in m/s
//velocityY is the vertical (Front-to-back) component in m/s
//velocityZ is the angular (Round and round) component in rad/s
//This reference frame is relative to the robot in all instances, meaning the angular argument
//drives it kind of like a car.
float CalculateDriveSpeed(float velocityX,float velocityY,float velocityZ, MotorEnum driveIdentifier)
{
	float driveXComponent = velocityX + (velocityZ * CENTER_RADIUS * cos(57.3 * Drive[driveIdentifier].offsetAngle) / 6.28);
	float driveYComponent = velocityY - (velocityZ * CENTER_RADIUS * sin(57.3 * Drive[driveIdentifier].offsetAngle) / 6.28);
	float driveSpeed = sqrt(pow(driveXComponent, 2) + pow(driveYComponent, 2)); //drive speed
	return driveSpeed;
}

//Convert from SI units to MotorPower and Servo Position units, then set the motorPower and servoPosition
//arguments of the motor in question accordingly.

void WriteToDevices()
{
	mpsToMotor(  FRONT_RIGHT_MOTOR, Drive[FRONT_RIGHT].motorPower);
	mpsToMotor(  FRONT_LEFT_MOTOR,  Drive[FRONT_LEFT].motorPower);
	mpsToMotor(  BACK_LEFT_MOTOR,   Drive[BACK_LEFT].motorPower);
	mpsToMotor(  BACK_RIGHT_MOTOR,  Drive[BACK_RIGHT].motorPower);

	degToCRServo(FRONT_RIGHT_SERVO, Drive[FRONT_RIGHT].servoPosition);
	degToCRServo(FRONT_LEFT_SERVO,  Drive[FRONT_RIGHT].servoPosition);
	degToCRServo(BACK_LEFT_SERVO,   Drive[BACK_LEFT].servoPosition);
	degToCRServo(BACK_RIGHT_SERVO,  Drive[BACK_RIGHT].servoPosition);
}

#endif
