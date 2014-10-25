#ifndef SIMPLESWERVE_4M_C
#define SIMPLESWERVE_4M_C

#include "../controllers/controller_defines.h"

//These describe the geometry of the robot.
//The radius is the distance from the motor assemblies to the robot center (or center of driving) in meters
//The offsetangle is the angle of the placement of the drive assemblies from the "front" in radians
//Both are 4 item arrays storing independent values for the four different drive assemblies which can be placed anywhere.
//basically these hold the placement vectors of the drive assemblies from the robot center (or center of driving)
//e.g, OFFSETANGLE would have values [PI/4, 3*PI/4, 5*PI/4, 7*PI/4] for most robots, but you could have differing values if you want
//e.g RADIUS would have some values close to [0.2286, 0.2286, 0.2286, 0.2286] for most robots, but you could have differing values if you want.
//The motorgearratio is the gear ratio between the motor and the wheel
//The servogearratio is the gear ratio between the servo and the turntable

int RADIUS[4];
int OFFSETANGLE[4];
int MOTORGEARRATIO;
int SERVOGEARRATIO;
int largestradius = 0.2286; //change this to find the largest number in RADIUS

void SetGeometry(int radius,int offsetAngle, int motorGearRatio, int servoGearRatio)
{
	RADIUS = radius;
	OFFSETANGLE = offsetAngle;
	MOTORGEARRATIO = motorGearRatio;
	SERVOGEARRATIO = servoGearRatio;
}

//attenuate the joystick input to angular speed and return the angular speed in m/s
int JoystickToRadiansPerSecond(int joystickZPosition)
{
	int angularSpeed = ((0.82804 * MOTORGEARRATIO / RADIUS[largestradius]) / (MAX_ANALOG - ANALOG_DEAD_ZONE)) * joystickZPosition + sgn(joystickZPosition) * ((0.82804 * MOTORGEARRATIO / RADIUS[largestradius]) / (MAX_ANALOG - ANALOG_DEAD_ZONE)) * ANALOG_DEAD_ZONE;
	return angularSpeed;
}

//this function attenuates the joystick inputs off of the current maximum linear speed, which is based on the current angular speed
//(which is in turn attenuated off of the maximum placement radius and motor speed)
int JoystickToMetersPerSecond(int joystickXorYPosition, int joystickZPosition)
{
	// where .82804 has units of meters per second (and corresponds to 100 motor power, the maximum motor power)
	int maximumLinearSpeed = 0; //This math still needs to be done
	int metersPerSecond = ((maximumLinearSpeed/(MAX_ANALOG - ANALOG_DEAD_ZONE)) * joystickXorYPosition + sgn(joystickXorYPosition) * (maximumLinearSpeed/(MAX_ANALOG - ANALOG_DEAD_ZONE)))* ANALOG_DEAD_ZONE;
	return metersPerSecond;
}

//velocityX is the horizontal (Side-to-side) component of the desired robot motion in m/s
//velocityY is the vertical (Front-to-back) component in m/s
//velocityZ is the angular (Round and round) component in rad/s
//This reference frame is relative to the robot in all instances
int CalculateMotorAngle(int velocityX, int velocityY, int velocityZ, driveIdentifier)
{
	// calculate the angle from the front that the motor should be pointing
	int motorAngle = atan((velocityX + velocityZ * RADIUS[driveIdentifier] * cos(OFFSETANGLE[driveIdentifier])) / (velocityY - velocityZ * RADIUS[driveIdentifier] * sin(OFFSETANGLE[driveIdentifier])));
	return motorAngle;
}

//velocityX is the horizontal (Side-to-side) component of the desired robot motion
//velocityY is the vertical (Front-to-back) component
//velocityZ is the angular (Round and round) component
//This reference frame is relative to the robot in all instances
int CalculateMotorSpeed(int velocityX,int velocityY,int velocityZ, driveIdentifier)
{
	// calculate the speed that the motor should be driving at
	int motorSpeed = sqrt(pow((velocityX + velocityZ * RADIUS[driveIdentifier] * cos(OFFSETANGLE[driveIdentifier])), 2) + pow((velocityY - velocityZ * RADIUS[driveIdentifier] * sin(OFFSETANGLE[driveIdentifier])), 2));
	return motorSpeed;
}

//Convert the calculated units to the units for our servos and motors, then send to the drive assemblies
//this will need to be rewritten to accomodate different gear ratios on both the servo and the motor, plus to just pass it one identifier for drive assemblies
void DriveVelocity(int speed, int angle, driveIdentifier)
{
	//convert radians to servo positions, where 255 / PI has units of positions per radian
	int position = (255 / PI) * SERVOGEARRATIO * (angle-OFFSETANGLE[driveIdentifier]);
	//convert m/s to motor power where 120.7671 has units of power per m/s
	int power = 120.7671 * speed * MOTORGEARRATIO ;
	//send the values to the corresponding motor and servo
	motor[driveIdentifier] = power;
	servo[driveIdentifier] = position;
}


#endif
