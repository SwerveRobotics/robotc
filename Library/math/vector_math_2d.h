#ifndef VECTOR_MATH_2D_H
#define VECTOR_MATH_2D_H

typedef enumWord
{
	X = 0,
	Y,
	W,
}AxisEnum;

typedef struct
{
	float location[2];
	float rotation;
}tTransform;

typedef struct
{
	float direction;
	float magnitude;
}tVector;

float FindAngle(tTransform A, tTransform B)
{
	float x = A.location[X] - B.location[X];
	float y = A.location[Y] - B.location[Y];
	float angle = radiansToDegrees( atan2(y, x) );
	return angle;
}

float FindDistance(tTransform A, tTransform B)
{
	float x = A.location[X] - B.location[X];
	float y = A.location[Y] - B.location[Y];
	float dist = sqrt( pow(x, 2) + pow(y, 2) );
	return dist;
}

void Transform(tTransform &A, tTransform B)
{
	A.location[X] += B.location[X];
	A.location[Y] += B.location[Y];
	A.rotation    += B.rotation;
}

#endif
