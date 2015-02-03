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

typedef struct
{
	tTransform finalTransform;
	tVector finalVelocity;
	float finalRotationRate;
}tMovement;

typedef struct
{
	tVector velocity;
	float rotationRate;
}tDriveArgument;

tTransform Translate(tTransform A, tTransform B)
{
	tTransform C;
	for (AxisEnum axis = X; axis < W; axis++)
	{
		C.location[axis] = A.location[axis] + B.location[axis];
	}
	return C;
}

tVector FindRelation(tTransform A, tTransform B)
{
}

#endif
