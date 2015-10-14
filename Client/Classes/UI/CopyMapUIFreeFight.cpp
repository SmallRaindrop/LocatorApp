#include "CopyMapUIFreeFight.h"
#include "Net/NetDispatcher.h"

CCopyMapFreeFight::CCopyMapFreeFight()
	:CCopyMapUI(IDU_CopyFreeFight,JsonFile_CopyFreeFight)
{

}

CCopyMapFreeFight::~CCopyMapFreeFight()
{

}

bool CCopyMapFreeFight::onInit()
{
	do 
	{
		m_pCountSeconds = (Text*)Helper::seekWidgetByName(m_pWidget,"Countdown");
		m_pCountSecondsTitle = (Text*)Helper::seekWidgetByName(m_pWidget,"CountdownTitle");
		Button* pBtnScore = (Button*)Helper::seekWidgetByName(m_pWidget,"BtnScore");
		BREAK_IF(!(m_pCountSeconds&&m_pCountSecondsTitle&&pBtnScore));
		m_pCountSeconds->setEnabled(false);
		pBtnScore->addTouchEventListener(this,toucheventselector(CCopyMapFreeFight::ClickBtnScore));
		return true;
	} while (0);
	return false;
}

void CCopyMapFreeFight::OnStartCountDown()
{
	m_pCountSecondsTitle->setText(STR_Copy_Title_CountFight);
}

void CCopyMapFreeFight::OnEndCountDown()
{
	m_pCountSecondsTitle->setText(STR_Copy_CountTitle);
}

void CCopyMapFreeFight::ClickBtnScore(Ref *pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		pk::C2GS_FreeFightCopyScoreBoard_Req cmd;
		cmd.Send(gNetSocket);
	}
}