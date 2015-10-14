#include "CdCtrol.h"
#include "Common/CommonDef.h"


CdCtrol::CdCtrol(const std::string& path)
	:m_pCdTime(NULL)
	,m_fCdTime(0)
	,m_Timer(NULL)
{
		m_cdFilePath = path;
		setAnchorPoint(Point(0.5,0.5));
		m_pCdTime = Text::create();
		m_pCdTime->setFontSize(32);
		m_pCdTime->setPosition(Point(_customSize.width/2, _customSize.height/2));
		m_pCdTime->setText("");
		addChild(m_pCdTime);

		Sprite* pCd = Sprite::create(m_cdFilePath);
		m_Timer = ProgressTimer::create(pCd);
		m_Timer->setType( ProgressTimer::Type::RADIAL );
		m_Timer->setReverseProgress(true);
		m_Timer->setPosition(Point(_customSize.width/2, _customSize.height/2));
		addChild(m_Timer);
}

CdCtrol::~CdCtrol()
{
	EndCd();
	m_pCdTime = NULL;
	m_Timer = NULL;
	m_fCdTime = 0.0f;
}

void CdCtrol::SetCd(int CdTime,int CdTimeTotal)
{
	EndCd();

	if(CdTimeTotal<=0) CdTimeTotal = CdTime;
	if(CdTimeTotal<=0) return;
	m_fCdTime = CdTime/1000.0f;
	if(m_fCdTime <= 0) return;

	m_Timer->setVisible(true);
	auto fromTo = ProgressFromTo::create(m_fCdTime, CdTime*100/CdTimeTotal,0);
	fromTo->setTag(Child_Cd_Tag);
	m_Timer->runAction( fromTo );
	setTouchEnabled(true);
	m_pCdTime->setEnabled(true);
	scheduleUpdate();
}

void CdCtrol::EndCd()
{
	setTouchEnabled(false);
	m_pCdTime->setEnabled(false);
	unscheduleUpdate();
	m_Timer->stopActionByTag(Child_Cd_Tag);
	m_Timer->setVisible(false);
}

void CdCtrol::setSize(const Size &size)
{
	Widget::setSize(size);
	Size sizeTotal = m_Timer->getSprite()->getContentSize();
	setScale(size.width/sizeTotal.width);
	m_Timer->setPosition(Point(size.width/2,size.height/2));
	m_pCdTime->setPosition(Point(size.width/2,size.height/2));
}

void CdCtrol::update(float dt)
{
	m_fCdTime-=dt;
	m_pCdTime->setText(CCString::createWithFormat("%.1f",m_fCdTime)->getCString());

	if(m_fCdTime <= 0)
	{
		EndCd();
	}
}