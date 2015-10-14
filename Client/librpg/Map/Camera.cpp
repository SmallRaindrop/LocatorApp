#include "Camera.h"


CCamera::CCamera()
{
	restore();
}

CCamera::~CCamera()
{
}


void CCamera::restore()
{
	kmVec3Fill(&_center, 0, 0, 0);
	kmVec3Fill(&_eye, 0, 0, FLT_EPSILON);
	kmVec3Fill(&_up, 0, 1, 0);
	updateTransform();
}

void CCamera::setEye(const kmVec3& eye)
{
	_eye = eye;
	updateTransform();
}

void CCamera::setEye(float x, float y)
{
	kmVec3Fill(&_eye, x, y, _eye.z);
	updateTransform();
}

void CCamera::setEye(float x, float y, float z)
{
	kmVec3Fill(&_eye, x, y, z);
	updateTransform();
}

void CCamera::setCenter(const kmVec3& center)
{
	_center = center;
	updateTransform();
}

void CCamera::setCenter(float x, float y, float z)
{
	kmVec3Fill(&_center, x, y, z);
	updateTransform();
}

void CCamera::setUp(const kmVec3& up)
{
	_up = up;
	updateTransform();
}

void CCamera::setUp(float x, float y, float z)
{
	kmVec3Fill(&_up, x, y, z);
	updateTransform();
}

void CCamera::updateTransform()
{
	kmMat4 lookupMatrix;
	kmMat4LookAt(&lookupMatrix, &_eye, &_center, &_up);

	kmMat4Identity(&_transform);
	kmMat4Multiply(&_transform, &_transform, &lookupMatrix);
}
