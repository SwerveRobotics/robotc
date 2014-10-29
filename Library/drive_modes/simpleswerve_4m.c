#ifndef SIMPLESWERVE_4M_C
#define SIMPLESWERVE_4M_C

#include "../controllers/controller_defines.h"

typedef enumWord{FRONT_RIGHT,FRONT_LEFT,BACK_LEFT,BACK_RIGHT}POS;

typedef struct //define swerve drive module data type
{
	int position;
	int power;
	int offsetAngle;
	float radius;
}SWIVE;

SWIVE Swive[4];
//These describe the geometry of the robot.
//Both are 4 item arrays storing independent values for the four different drive assemblies which can be placed anywhere.
//basically these hold the placement vectors of the drive assemblies from the robot center (or center of driving)

//The RADIUS is the distance from the motor assemblies to the robot center (or center of driving) in meters. This array holds four different values for four different drive assemblies (general case is good).
//e.g RADIUS would have some values close to [0.2286, 0.2286, 0.2286, 0.2286] for most robots, but you could have differing values if you want.
float RADIUS[4] = {0.2286, 0.2286, 0.2286, 0.2286};
//The offsetangle is the angle of the placement of the drive assemblies from the "front" in radians. This array holds four different values for four different drive assemblies (general case is good).
//e.g, OFFSETANGLE would have values [PI/4, 3*PI/4, 5*PI/4, 7*PI/4] for most robots, but you could have differing values if you want
float OFFSET_ANGLE[4] = {PI/4, 3 * PI/4, 5 * PI/4, 7 * PI/4};
// for use in some of the joystick scaling, we need the largest radius value.
#define LARGEST_RADIUS (0.2286) //change this to find the largest number in RADIUS

void initializeSwiveGeometry()//sets drive geometry the swive struct
{
	for (POS p; p < 4; p++)
	{
		Swive[p].radius = RADIUS[p];
		Swive[p].offsetAngle = OFFSET_ANGLE[p];
	}

}

//The motorgearratio is the gear ratio between the motor and the wheel
int MOTOR_GEAR_RATIO = 1;
//The servogearratio is the gear ratio between the servo and the turntable
int SERVO_GEAR_RATIO = 1;
//maximum value the servo can be sent to
int MAX_SERVO_VAL = 255;
//minimum value the servo can be sent to
int MIN_SERVO_VAL = 0;
//maximum angle the servo can go to
int MAX_SERVO_ANGLE = PI/2;
//minimum angle the servo can go to
int MIN_SERVO_ANGLE = -PI/2;
///wheel radius (in meters in this set up)
int WHEEL_RADIUS = 0.0508 ;


const int MAX_MOTOR_SPEED_MPS = 0.8193; // it might make sense to make a library file for a bunch of constants like this, and unit conversions, this is with a 4in diameter wheel btw

const int MOTOR_POWER_PER_MPS = 120.7671; //we really should just make a bunch of these

//sets parameters that are specific to different hardware configurations.
void SetDrivePhysicalConfiguration(int radius,int offsetAngle, int motorGearRatio, int servoGearRatio, int maxServoValue, int minServoValue, int maxServoAngle, int minServoAngle, int wheelRadius)
{
	RADIUS = radius;
	OFFSET_ANGLE = offsetAngle;
	MOTOR_GEAR_RATIO = motorGearRatio;
	SERVO_GEAR_RATIO = servoGearRatio;
	MAX_SERVO_VAL = maxServoAngle;
	MIN_SERVO_VAL = minServoAngle;
	MAX_SERVO_ANGLE = maxServoAngle;
	MIN_SERVO_ANGLE = minServoAngle;
	WHEEL_RADIUS = wheelRadius;
}

//Attenuate the joystick input being used for angular velocity based on the maximum radius and the maximum motor speed, then convert to radians per second
int JoystickToRadiansPerSecond(int joystickZPosition)
{
	int angularSpeed = ((MAX_MOTOR_SPEED_MPS * MOTOR_GEAR_RATIO / LARGEST_RADIUS) / (MAX_ANALOG - ANALOG_DEAD_ZONE)) * joystickZPosition + sgn(joystickZPosition) * ((MAX_MOTOR_SPEED_MPS * MOTOR_GEAR_RATIO / LARGEST_RADIUS) / (MAX_ANALOG - ANALOG_DEAD_ZONE)) * ANALOG_DEAD_ZONE;
	return angularSpeed;
}

//Attenuate the joystick inputs being used for planar motion based on the maximum linear speed possible at an instant
//(which is in turn scaled off of the current angular speed)
int JoystickToMetersPerSecond(int joystickXorYPosition, int joystickZPosition)
{
	int maximumLinearSpeed = sqrt( pow(MAX_MOTOR_SPEED_MPS, 2) - pow(JoystickToRadiansPerSecond(joystickZPosition) * LARGEST_RADIUS, 2));
	int metersPerSecond = ((maximumLinearSpeed/(MAX_ANALOG - ANALOG_DEAD_ZONE)) * joystickXorYPosition + sgn(joystickXorYPosition) * (maximumLinearSpeed/(MAX_ANALOG - ANALOG_DEAD_ZONE)))* ANALOG_DEAD_ZONE;
	return metersPerSecond;
}

//Calculate the angular component of the motor velocity vector based on the inputs for the desired motion of the center of the robot:
//velocityX is the horizontal (Side-to-side) component of the desired robot motion in m/s
//velocityY is the vertical (Front-to-back) component in m/s
//velocityZ is the angular (Round and round) component in rad/s
//This reference frame is relative to the robot in all instances.
//So, the angular argument turns it like a car, while the x and y arguments strafe it around the field
float CalculateMotorAngle(int velocityX, int velocityY, int velocityZ,int driveIdentifier)
{
	//used the arctangent function to find the angular component of the velocity vector for the chosen motor
	int motorAngle = atan((velocityX + velocityZ * RADIUS[driveIdentifier] * cos(OFFSET_ANGLE[driveIdentifier])) / (velocityY - velocityZ * RADIUS[driveIdentifier] * sin(OFFSET_ANGLE[driveIdentifier])));
	return motorAngle;
}

//Calculate the magnitude (speed) component of the motor velocity vector base on the inputs for the desited motion of the center of the robot:
//velocityX is the horizontal (Side-to-side) component of the desired robot motion in m/s
//velocityY is the vertical (Front-to-back) component in m/s
//velocityZ is the angular (Round and round) component in rad/s
//This reference frame is relative to the robot in all instances.
//So, the angular argument turns it like a car, while the x and y arguments strafe it around the field
int CalculateMotorSpeed(int velocityX,int velocityY,int velocityZ,int driveIdentifier)
{
	// uses the pythagorean theorem to find the magnitude of the velocity vector for the chosen motor
	int motorSpeed = sqrt(pow((velocityX + velocityZ * RADIUS[driveIdentifier] * cos(OFFSET_ANGLE[driveIdentifier])), 2) + pow((velocityY - velocityZ * RADIUS[driveIdentifier] * sin(OFFSET_ANGLE[driveIdentifier])), 2));
	return motorSpeed;
}

//Convert the calculated units to the units for our servos and motors, then send to the drive assemblies
//this will need to be rewritten with more thought as to the particulars of limited servo ranges...
void SetDriveVelocity(int speed, int angle,int driveIdentifier)
{
	//convert radians to servo positions
	//the way this is set up is the reason that the servos should be set to the center position facing forwards
	//it also assumes at least 360 deg motion for the angle in order to work, so this will probably need to be more advanced at some point.
	int position = ((MAX_SERVO_VAL - MIN_SERVO_VAL) / (MAX_SERVO_ANGLE - MIN_SERVO_ANGLE)) * SERVO_GEAR_RATIO * angle;
	//convert m/s to motor power
	int power = MOTOR_POWER_PER_MPS * speed * MOTOR_GEAR_RATIO ;
	//send the values to the corresponding motor and servo
	Swive[driveIdentifier].power = power;
	Swive[driveIdentifier].position = position;
}

#endif
