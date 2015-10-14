/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：游戏内摄像机
 */

#ifndef __Camera_h_
#define __Camera_h_

#include "GameDef.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	/* sets the Eye value of the Camera */
	void setEye(const kmVec3 &eye);
	void setEye(float x,float y);
	void setEye(float x, float y, float z);
	/* sets the Center value of the Camera */
	void setCenter(const kmVec3 &center);
	void setCenter(float x, float y, float z);
	/* sets the Up value of the Camera */
	void setUp(const kmVec3 &up);
	void setUp(float x, float y, float z);

	/* returns the Eye value of the Camera */
	const kmVec3& getEye() const { return _eye; }
	/* returns the Center value of the Camera */
	const kmVec3& getCenter() const { return _center; }
	/* Returns the Up value of the Camera */
	const kmVec3& getUp() const { return _up; }
	/* Returns the transform value of the Camera */
	const kmMat4& getTransform() const { return _transform; }

protected:
	void restore();
	void updateTransform();

private:
	kmVec3 _center;
	kmVec3 _eye;
	kmVec3 _up;
	kmMat4 _transform;
};

#endif // !__Camera_h_
