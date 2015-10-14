#pragma once
#include "GameDef.h"

// 定义一个结构来包含确定椭圆的参数
typedef struct _lrTuoyuanConfig {
	Point centerPosition;
	float aLength;
	float bLength;
} lrTuoyuanConfig;

class LRTuoyuanBy : public ActionInterval
{
public:
	LRTuoyuanBy();
	virtual ~LRTuoyuanBy();
	bool initWithDuration(float t, const lrTuoyuanConfig& c);
	inline void setRotationDegree(double startAngle, double rotateDegree) { m_startAngle=startAngle; m_rotateDegree=rotateDegree; }
	void		setRotationDegree(Point pos, double rotateDegree);
	virtual void update(float time);
public:
	static LRTuoyuanBy *create(float t, const lrTuoyuanConfig& c, Point pos, double rotateDegree);
	static LRTuoyuanBy *create(float t, const lrTuoyuanConfig& c, double startAngle, double rotateDegree);

	inline float tuoyuanXat( float a, float angle ) { 	return -a*cos(angle); }
	inline float tuoyuanYat( float b, float angle ) { return b*sin(angle); }

	virtual LRTuoyuanBy* reverse() const override;
	virtual LRTuoyuanBy*clone() const override;

protected:
	lrTuoyuanConfig m_sConfig;
	Point m_startPosition;
	Point s_startPosition;
	float m_startAngle;
	float m_rotateDegree;
};

class CircleBy : public ActionInterval
{
public:
	CircleBy();
	virtual ~CircleBy();
	static CircleBy*	create(float t, float ra,float rb,const Point& center,float angle0,float angle1);
	
	virtual CircleBy*	reverse() const override;
	virtual CircleBy*	clone() const override;
	virtual void		update(float time);

protected:
	bool initWithParams(float t,float ra,float rb,const Point& center,float angle0,float angle1);

protected:
	Point _center;
	float _ra;
	float _rb;
	float _angle0;
	float _angle1;
};
