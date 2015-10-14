#include "TimerProgressBar.h"
#include "UIImageView.h"
#include "UI/ResMgr/CtrlAllocator.h"
#include "GameScene/Hero.h"


TimerProgressBar::TimerProgressBar(void): m_bRunning(),m_fHoldTime(0.0f)
{
}


TimerProgressBar::~TimerProgressBar(void)
{
}

TimerProgressBar* TimerProgressBar::create()
{
    TimerProgressBar* widget = new TimerProgressBar();
    if (widget && widget->init())
    {
		widget->autorelease();
		widget->scheduleUpdate();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void TimerProgressBar::InitWithTarget(Node *pBase, Ref *pTarget, SEL_SCHEDULE pfnSelector, float fSeconds)
{
	m_fHoldTime = 0.0f;
	m_timer.initWithSelector(Director::getInstance()->getScheduler(), pfnSelector, pTarget, fSeconds, 0, 0.0f);
	m_pBase = pBase;
}

void TimerProgressBar::SetBGImg(const char* texture)
{
	ImageView *pImg = (ImageView*)gCtrlAllocator->LoadCtrl(texture);
	if (pImg)
	{
		removeChild(getChildByName("bg"), true);
		pImg->setName("bg");
		pImg->setPosition(Point(getSize().width / 2, getSize().height / 2));
		pImg->setLocalZOrder(-1);
		addChild(pImg);
	}
}

void TimerProgressBar::update(float dt)
{
	if (!m_bRunning)
		return;

	LoadingBar::update(dt);
	m_timer.update(dt);

	if (m_bRunning && m_timer.getInterval() > 0.0f)
	{
		setPercent((int)(m_timer.GetElapsed() * 100.f / m_timer.getInterval()));
	}

	if (m_pBase && gMap)
	{
		Point pos = m_pBase->convertToWorldSpace(Point::ZERO) - gDirector->getVisibleOrigin();
		//pos.y += m_pBase->getHangingPoint("V_TOP_NODE").y;
		pos.y += 150;

		setPosition(pos);
	}
	m_fHoldTime += dt;
	if (m_fHoldTime > 1.0f)
	{
		if ( gHero->IsMoving() || gHero->IsAttacking() || gHero->IsInjured() )
		{
			SetRunning(false);
		}
	}
}
