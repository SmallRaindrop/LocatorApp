#include "TuoYuanAction.h"

//
//TuoyuanBy
//

LRTuoyuanBy::LRTuoyuanBy()
	:m_startAngle(0.0f)
	,m_rotateDegree(0.0f)
{

}

LRTuoyuanBy::~LRTuoyuanBy()
{

}
LRTuoyuanBy* LRTuoyuanBy::create(float t, const lrTuoyuanConfig& c,Point pos,double rotateDegree)
{
	LRTuoyuanBy *pTuoyuanBy = new LRTuoyuanBy();
	pTuoyuanBy->initWithDuration(t, c);
	pTuoyuanBy->setRotationDegree(pos,rotateDegree);
	pTuoyuanBy->autorelease();

	return pTuoyuanBy;
}

LRTuoyuanBy* LRTuoyuanBy::create(float t, const lrTuoyuanConfig& c, double startAngle, double rotateDegree)
{
	LRTuoyuanBy *pTuoyuanBy = new LRTuoyuanBy();
	pTuoyuanBy->initWithDuration(t, c);
	pTuoyuanBy->setRotationDegree(startAngle,rotateDegree);
	pTuoyuanBy->autorelease();

	return pTuoyuanBy;
}

void LRTuoyuanBy::setRotationDegree(Point pos, double rotateDegree)
{
	setRotationDegree(Point(-1,0).getAngle(pos-m_sConfig.centerPosition),rotateDegree);
}

bool LRTuoyuanBy::initWithDuration(float t, const lrTuoyuanConfig& c)
{
	if (ActionInterval::initWithDuration(t))
	{
		m_sConfig = c;
		return true;
	}

	return false;
}

void LRTuoyuanBy::update(float time)
{
	if (_target)
	{
		Point s_startPosition =m_sConfig.centerPosition;
		float a = m_sConfig.aLength;
		float b = m_sConfig.bLength;
		float angle = m_startAngle + m_rotateDegree*time;
		if (angle>2*PI)
		{
			angle = angle - 2*PI;
		}
		float x = tuoyuanXat(a, angle);
		float y = tuoyuanYat(b, angle);
		_target->setPosition(s_startPosition+Point(x, y));
		//CCLOG("(%f,%f) startAgle:%fpi,angle:%fpi",_target->getPositionX(),_target->getPositionY(),m_startAngle/PI,angle/PI);
	}
}

LRTuoyuanBy* LRTuoyuanBy::reverse() const
{
	//no use
	auto a = new LRTuoyuanBy();
	a->initWithDuration(1.0f, m_sConfig );
	a->autorelease();
	return a;
}

LRTuoyuanBy* LRTuoyuanBy::clone() const
{
	//no use
	auto a = new LRTuoyuanBy();
	a->initWithDuration(1.0f, m_sConfig );
	a->autorelease();
	return a;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CircleBy::CircleBy() : _ra(0.0f),_rb(0.0f),_angle0(0.0f),_angle1(0.0f)
{

}

CircleBy::~CircleBy()
{

}

CircleBy* CircleBy::create(float t, float ra,float rb,const Point& center,float angle0,float angle1)
{
	CircleBy *pRet = new CircleBy();
	if ( pRet && pRet->initWithParams(t,ra,rb,center,angle0,angle1) )
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);

	return NULL;
}

bool CircleBy::initWithParams(float t,float ra,float rb,const Point& center,float angle0,float angle1)
{
	_ra = ra;
	_rb = rb;
	_center = center;
	_angle1 = angle1;
	_angle0 = angle0;
	
	return ActionInterval::initWithDuration(t);
}

CircleBy* CircleBy::reverse() const
{
	return create(getDuration(),_ra,_rb,_center,_angle1,_angle0);
}

CircleBy* CircleBy::clone() const 
{
	return create(getDuration(),_ra,_rb,_center,_angle0,_angle1);
}

void CircleBy::update(float time)
{
	if (_target)
	{
		float angle = _angle0 + time*(_angle1-_angle0);
		if (angle>2*PI)
		{
			angle = angle - 2*PI;
		}

		_target->setPosition(_center+Point(_ra*cos(angle), -_rb*sin(angle)));
	}
}