#include "CopyMapUISurvive.h"

CCopyMapUISurvive::CCopyMapUISurvive()
	:CCopyMapUI(IDU_CopyUISurvive,JsonFile_CopySurvive)
	,m_pAttentionFrame(nullptr)
	,m_pAttentionValue(nullptr)
	,m_pAttentionBar(nullptr)
	,m_pAttention(nullptr)
	,m_pSurviveSeconds(nullptr)
	,m_nSurviveSeconds(0)
{

}

CCopyMapUISurvive::~CCopyMapUISurvive()
{

}

bool CCopyMapUISurvive::onInit()
{
	do 
	{
		m_pCountSecondsTitle = (Text*)Helper::seekWidgetByName(m_pWidget,"CountdownTitle");
		m_pCountSeconds = (Text*)Helper::seekWidgetByName(m_pWidget,"Countdown");
		m_pSurviveSecondsTitle = (Text*)Helper::seekWidgetByName(m_pWidget,"SurviveSecondTitle");
		m_pSurviveSeconds = (Text*)Helper::seekWidgetByName(m_pWidget,"SurviveSeconds");
		m_pAttentionFrame = (Layout*)Helper::seekWidgetByName(m_pWidget,"AttentionBarFrame");
		m_pAttentionValue = (Text*)Helper::seekWidgetByName(m_pWidget,"AttentionValue");
		m_pAttentionBar = Helper::seekWidgetByName(m_pWidget,"AttentionBar");
		m_pAttention = Helper::seekWidgetByName(m_pWidget,"AttentionTitle");
		BREAK_IF(!(m_pCountSecondsTitle&&m_pCountSeconds&&m_pSurviveSecondsTitle&&m_pSurviveSeconds&&m_pAttentionFrame&&m_pAttentionValue&&m_pAttentionBar&&m_pAttention));
		m_pCountSecondsTitle->setText(STR_Copy_Title_CountFight);
		m_pSurviveSecondsTitle->setText(STR_Copy_Title_FightSec);
		m_pSurviveSeconds->setEnabled(false);
		m_pAttention->setEnabled(false);
		m_pCountSeconds->setEnabled(false);
		m_pAttentionFrame->setClippingEnabled(true);
		return true;
	} while (0);
	return false;
}

void CCopyMapUISurvive::onClose()
{
	CCopyMapUI::onClose();
	EndSurviveSeconds();
}

void CCopyMapUISurvive::UpdateCopyInitInfo(pk::GS2C_CopyInitInfo* value)
{
	CCopyMapUI::UpdateCopyInitInfo(value);
	std::function<void()> fun = [this]()
	{
		if (!isScheduled(schedule_selector(CCopyMapUISurvive::ScheduleCountSeconds)))
		{
			StartCountSeconds(2);
		}
	};
	//断线重连，如果已经激活，则开始计时
	runAction(Sequence::createWithTwoActions(CCDelayTime::create(2.0f),CCCallFunc::create(fun)));
}

void CCopyMapUISurvive::BeforeActive()
{
	m_pAttention->setEnabled(false);
}

void CCopyMapUISurvive::OnActive()
{
	m_pAttention->setEnabled(true);
	StartSurviveSeconds(0);
}

void CCopyMapUISurvive::StartSurviveSeconds(int nSeconds)
{
	if(!m_pSurviveSeconds || nSeconds<0) return;

	EndSurviveSeconds();

	m_nSurviveSeconds = nSeconds;
	m_pSurviveSeconds->setEnabled(true);
	m_pSurviveSeconds->setText(SecondsToTime(m_nSurviveSeconds,1));
	schedule(schedule_selector(CCopyMapUISurvive::ScheduleSurviveSeconds),1.0f,kRepeatForever,1.0f);
}

void CCopyMapUISurvive::EndSurviveSeconds()
{
	if(!m_pSurviveSeconds) return;

	m_pSurviveSeconds->setEnabled(false);
	unschedule(schedule_selector(CCopyMapUISurvive::ScheduleSurviveSeconds));
}

void CCopyMapUISurvive::ScheduleSurviveSeconds(float dt)
{
	//激活前倒计时,激活后战斗统计时间
	m_nSurviveSeconds++;
	m_pSurviveSeconds->setText(SecondsToTime(m_nSurviveSeconds,1));
}

void CCopyMapUISurvive::updateLivePoint(pk::GS2C_LivePoint* value)
{
	if (value->livePoint == -1)
	{
		m_pAttention->setEnabled(false);
	} 
	else
	{
		m_pAttention->setEnabled(true);
		m_pAttentionValue->setText(CCString::createWithFormat("%d%%",value->livePoint*100/10000)->getCString());
		m_pAttentionFrame->setSize(Size(m_pAttentionBar->getContentSize().width*(value->livePoint/10000.0f),m_pAttentionBar->getContentSize().height));
	}
}