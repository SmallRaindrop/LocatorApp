#include "JoyStick.h"
#include "GameScene/Hero.h"

#define Moving_Radius 60.0f

JoyStick::JoyStick() : m_pBtn(NULL),m_pFrame(NULL),m_bValid(false),m_fCDTime(0.0f)
{
	initialize();
}

JoyStick::~JoyStick()
{
	
}

//
//int JoyStick::angleToDir(float angle)
//{
//	//float degree = CC_RADIANS_TO_DEGREES(angle);
//
//	if ( ( angle >= 0 && angle <= M_PI/8 + 0.001 /* add by 0.001,fixing the 'moon walk' */ ) 
//		|| ( angle < 0 && angle >= -M_PI/8 - 0.001 ))
//	{
//		return DIR_E;
//	}
//	else if( angle > M_PI/8 && angle <= M_PI/8*3 + 0.001 )
//	{
//		return DIR_NE;
//	}
//	else if( angle > M_PI/8*3 && angle <= M_PI/8*5 + 0.001 )
//	{
//		return DIR_N;
//	}
//	else if( angle > M_PI/8*5 && angle <= M_PI/8*7 + 0.001 )
//	{
//		return DIR_NW;
//	}
//	else if( ( angle > M_PI/8*7 && angle <= M_PI + 0.001 )
//		|| ( angle > -M_PI && angle <= -M_PI/8*7 + 0.001 ))
//	{
//		return DIR_W;
//	}
//	else if( angle > -M_PI/8*7 && angle <= -M_PI/8*5 + 0.001)
//	{
//		return DIR_SW;
//	}
//	else if( angle > -M_PI/8*5 && angle <= -M_PI/8*3 + 0.001  )
//	{
//		return DIR_S;
//	}
//	else if( angle > -M_PI/8*3 && angle <= -M_PI/8 + 0.001 )
//	{
//		return DIR_SE;
//	}
//
//	return DIR_SE;
//}

float JoyStick::getAngle()
{
	Point pos = m_pBtn->getPosition();
	return pos.getAngle();
}

int	JoyStick::getDir()
{
	return angleToDir(getAngle());
}

float JoyStick::getOffset()
{
	Point pos = m_pBtn->getPosition();
	return pos.getLength();
}

bool JoyStick::isValidMove()
{
	return getOffset() > 20.0f;
}

bool JoyStick::initialize()
{ 
	m_pFrame = ImageView::create("assets/ui/MainUIFight/img_yagan_kaiqidi.png");
	if ( !m_pFrame )
	{
		return false;
	}

	m_pBtn = Button::create("assets/ui/MainUIFight/img_yagan_gunzhu.png","assets/ui/MainUIFight/img_yagan_gunzhu.png","assets/ui/MainUIFight/img_yagan_gunzhu.png");
	if ( !m_pBtn )
	{
		return false;
	}
	m_pBtn->setTouchEnabled(false);
	addChild(m_pFrame);
	addChild(m_pBtn);

	reset();

	return true;
}

void JoyStick::reset()
{
	setPosition(Point(95,95));
	m_pFrame->setPosition(Point(0,0));
	m_pBtn->setPosition(Point(0,0));
	setValid(false);
	setEnabled(false);
}

void JoyStick::TouchMoved(Point pos)
{
	if(!isTouchEnabled())
	{
		return;
	}

	Point touchPoint = convertToNodeSpace(pos);

	kmVec2 dir = {fabs(touchPoint.x), fabs(touchPoint.y)};
	kmVec2Normalize(&dir, &dir);
	kmVec2 edge = {dir.x * Moving_Radius, dir.y * Moving_Radius};

	Point btnPos = Point(clampf(touchPoint.x, -edge.x,edge.x),
		clampf(touchPoint.y, -edge.y,edge.y));
	m_pBtn->setPosition(btnPos);

	if ( isValidMove() )
	{
		setValid(true);
	}
}


bool JoyStick::TouchBegan(Point pos)
{
	if(!isTouchEnabled())
	{
		return false;
	}

	setEnabled(true);
	m_pBtn->setPosition(convertToNodeSpace(pos));
	if ( isValidMove() )
	{
		setValid(true);
	}
	gHero->PursueCancel();
	return true;
}


void JoyStick::TouchEnded(Point pos)
{
	if(!isTouchEnabled())
	{
		return;
	}

	if ( gHero->IsMoving() )
	{
		gHero->Stop();
	}
	reset();
}


void JoyStick::TouchCancelled(Point ptTouch)
{
	if(!isTouchEnabled())
	{
		return;
	}

	if ( gHero->IsMoving() )
	{
		gHero->Stop();
	}
	reset();
}

void JoyStick::update(float dt)
{
	const float JOY_INTERVAL = 0.03f;
	m_fCDTime += dt;
	if ( m_fCDTime > JOY_INTERVAL )
	{
		m_fCDTime = 0.0f;

		if ( isValid() )
		{
			gHero->MoveBy(__Dir(getDir()));
		}
	}
}






















