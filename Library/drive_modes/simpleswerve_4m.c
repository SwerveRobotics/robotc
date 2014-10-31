#ifndef SIMPLESWERVE_4M_C
#define SIMPLESWERVE_4M_C

#include "../controllers/controller_defines.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//This swerve drive needs to run seperate calculations for 4 different assemblies that could hypothetically have different propierties. So, lets set up some structure for this:
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// define the different motors for use.
tMotor FRONT_LEFT_MOTOR;
tMotor BACK_LEFT_MOTOR;
tMotor FRONT_RIGHT_MOTOR;
tMotor BACK_RIGHT_MOTOR;

//function to register the motors
void RegisterDriveMotors(tMotor frontLeftM, tMotor backLeftM, tMotor frontRightM, tMotor backRightM)
{
	FRONT_LEFT_MOTOR = frontLeftM;
	BACK_LEFT_MOTOR = backLeftM;
	FRONT_RIGHT_MOTOR = frontRightM;
	BACK_RIGHT_MOTOR = backRightM;
}

//define the different servos for use
TServoIndex FRONT_LEFT_SERVO;
TServoIndex BACK_LEFT_SERVO;
TServoIndex FRONT_RIGHT_SERVO;
TServoIndex BACK_RIGHT_SERVO;

//function to register the servos
void RegisterDriveServos(TServoIndex frontLeftS, TServoIndex backLeftS, TServoIndex frontRightS, TServoIndex backRightS)
{
	FRONT_LEFT_SERVO = frontLeftS;
	BACK_LEFT_SERVO = backLeftS;
	FRONT_RIGHT_SERVO = frontRightS;
	BACK_RIGHT_SERVO = backRightS;
}

//make an enum to easily reference the four different assemblies by their position on the robot.
typedef enumWord
{
	FRONT_RIGHT_ASSEMBLY,
	FRONT_LEFT_ASSEMBL,
	BACK_LEFT_ASSEMBLY,
	BACK_RIGHT_ASSEMBLY,
}
	MotorEnum;

//define swerve drive assembly state object to store all values specific to any given drive assembly. This would let you use weird hodgepodge hardware.
typedef struct
{
	// the servo position argument in servo position units:
	int servoPosition;
	// the motor power in motor power units:
	int motorPower;

	//clockwise offset angle from the front:
	float offsetAngle;
	//distance from the driving center of the robot:
	float radiusFromCenter;
	//gear ratio in speed between motor and wheel:
	float motorGearRatio;
	//gear ratio in speed between servo and turntable:
	float servoGearRatio;
	//radius of the wheel on this given drive assembly:
	float wheelRadius;
}
DriveAssemblyState;

//make an array of drive assemblies, now to be referenced by the enums above.
DriveAssemblyState Drive[4];


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Now that some of the structure is in place, lets define some default constants:
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// CENTER_RADIUS is the radius from the driving center of the robot.
float CENTER_RADIUS[4] = {0.2286, 0.2286, 0.2286, 0.2286};
// OFFSET_ANGLE is the clockwise angle of the drive assembly from the "front" direction.
float OFFSET_ANGLE[4] = {PI/4.0, 3 * PI/4.0, 5 * PI/4.0, 7 * PI/4.0};
// Basically, these two store the position vectors for the drive assemblies from the driving center.

//The MOTOR_GEAR_RATIO is the gear ratio between the motor and the wheel.
float MOTOR_GEAR_RATIO[4] = {1.0,1.0,1.0,1.0};
//The SERVO_GEAR_RATIO is the gear ratio between the servo and the turntable.
float SERVO_GEAR_RATIO[4] = {1.0,1.0,1.0,1.0};
//WHEEL_RADIUS in meters.
float WHEEL_RADIUS[4] = {0.0508,0.0508,0.0508,0.0508};

float LARGEST_CENTER_RADIUS = 0.2286; //change this to check and set to the largest number in CENTER_RADIUS

float MAX_MOTOR_GEAR_RATIO = 1;// change this to check and sst to thee largest number in MOTOR_GEAR_RATIO

//maximum motor speed in meters per second based on a 4inch diameter wheel and a 154rpm motor
const float MAX_MOTOR_SPEED_MPS = 0.8193;
//unit conversion between "motor power" units and meters per second, based on a 4in diameter wheel.
const float MOTOR_POWER_PER_MPS = 120.7671;

//maximum value the servo can be sent to
int MAX_SERVO_VAL = 255;
//minimum value the servo can be sent to
int MIN_SERVO_VAL = 0;
//maximum angle the servo can go to
float MAX_SERVO_ANGLE = PI/2.0;
//minimum angle the servo can go to
float MIN_SERVO_ANGLE = -PI/2.0;
//these are more based off of the type of servo used, so maybe a definition based on that would be easier.
//this is kept out of all the config stuff cuz it could be implemented more generally.

float SERVO_ANGLE_TO_VAL = ((MAX_SERVO_VAL - MIN_SERVO_VAL) / (MAX_SERVO_ANGLE - MIN_SERVO_ANGLE));

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Now that we have the prerequisites set up and defined, we can start defining some functions:
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//edits the constants defining the geometry, so you can set up different hardware configurations.
void SetPhysicalConfiguration(float radius, float offsetAngle, float motorGearRatio, float servoGearRatio, float wheelRadius)
{
	CENTER_RADIUS = radius;
	OFFSET_ANGLE = offsetAngle;
	MOTOR_GEAR_RATIO = motorGearRatio;
	SERVO_GEAR_RATIO = servoGearRatio;
	WHEEL_RADIUS = wheelRadius;
}

//initializes the drive assembly by setting all the values in the drive assembly structs
void initializeDriveAssemblies()
{
	for (MotorEnum index; index < 4; index++)
	{
		Drive[index].offsetAngle = OFFSET_ANGLE[index];
		Drive[index].radiusFromCenter = CENTER_RADIUS[index];
		Drive[index].motorGearRatio = MOTOR_GEAR_RATIO[index];
		Drive[index].servoGearRatio = SERVO_GEAR_RATIO[index];
		Drive[index].wheelRadius = WHEEL_RADIUS[index];
	}
}


//Attenuate the joystick used for rotation based on the maximum angular speed possible and find the "desired" angular velocity.
float JoystickToRadiansPerSecond(int joystickZPosition)
{
	int joystickRange = MAX_ANALOG - ANALOG_DEAD_ZONE; 	// allowed input range from the joystick.
	float maxRadiansPerSecond= (MAX_MOTOR_SPEED_MPS * MAX_MOTOR_GEAR_RATIO) / LARGEST_CENTER_RADIUS;	//maximum rotational speed possible.
	float attenuationSlope =  maxRadiansPerSecond / joystickRange;	//mapping maximum rotational speed to the allowed joystick input range, aka. finding the slope.
	float attenuationIntercept = sgn(joystickZPosition) * attenuationSlope * ANALOG_DEAD_ZONE;	//finding the range taken up by the dead zone, aka. finding the intercept.
	float angularVelocity = (attenuationSlope * joystickZPosition) + attenuationIntercept;	//slope-intercept form of attenuation.
	return angularVelocity;	//this is the "desired" angular velocity based on the joystick input above.
}

//Attenuate the joystick inputs being used for planar motion based on the maximum linear speed possible in any direction at this instant.
//Which is in turn scaled off of the current angular speed. This means that the angular velocity limits the linear velocity.
int JoystickToMetersPerSecond(int joystickXorYPosition, int joystickZPosition)
{
	int joystickRange = MAX_ANALOG - ANALOG_DEAD_ZONE; //allowed input range along any axis from the joystick.
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
float CalculateDriveAngle(float velocityX, float velocityY, float velocityZ,int driveIdentifier)
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
float CalculateDriveSpeed(float velocityX,float velocityY,float velocityZ,int driveIdentifier)
{
	float driveXComponent = velocityX + (velocityZ * Drive[driveIdentifier].radiusFromCenter * cos(Drive[driveIdentifier].offsetAngle)); //find the component of the drive assembly velocity that is in X.
	float driveYComponent = velocityY - (velocityZ * Drive[driveIdentifier].radiusFromCenter * sin(Drive[driveIdentifier].offsetAngle)); //find the component of the drive assembly velocity that is in Y.
	float driveSpeed = sqrt(pow(driveXComponent, 2) + pow(driveYComponent, 2)); //find the speed the drive assembly in question should be moving at.
	return driveSpeed;
}

//Convert from SI units to MotorPower and Servo Position units, then set the motorPower and servoPosition arguments of the motor in question accordingly.
void SetDriveVelocity(float driveSpeed, float driveAngle,int driveIdentifier)
{
	Drive[driveIdentifier].motorPower = MOTOR_POWER_PER_MPS * Drive[driveIdentifier].motorGearRatio * driveSpeed;
	Drive[driveIdentifier].servoPosition = SERVO_ANGLE_TO_VAL * Drive[driveIdentifier].servoGearRatio * driveAngle;
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
