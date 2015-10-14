#include "CopyMapUICommon.h"

CCopyMapCommon::CCopyMapCommon()
	:CCopyMapUI(IDU_CopyCommon,JsonFile_CopyCommon)
{

}

CCopyMapCommon::~CCopyMapCommon()
{

}

bool CCopyMapCommon::onInit()
{
	do 
	{
		m_pGoalTitle = (Text*)Helper::seekWidgetByName(m_pWidget,"GoalTitle");
		m_pCurTitle = (Text*)Helper::seekWidgetByName(m_pWidget,"CurTitle");
		m_pCountSecondsTitle = (Text*)Helper::seekWidgetByName(m_pWidget,"CountdownTitle");
		m_pGoalNum = (Text*)Helper::seekWidgetByName(m_pWidget,"GoalNum");
		m_pCurNum = (Text*)Helper::seekWidgetByName(m_pWidget,"CurNum");
		m_pCountSeconds = (Text*)Helper::seekWidgetByName(m_pWidget,"Countdown");
		BREAK_IF(!(m_pGoalTitle&&m_pCurTitle&&m_pCountSecondsTitle&&m_pGoalNum&&m_pCurNum&&m_pCountSeconds));
		m_pCountSecondsTitle->setText(STR_Copy_CountTitle);
		return true;
	} while (0);
	return false;
}

void CCopyMapCommon::onOpen()
{
	switch (gMap->getPlayType())
	{
	case GameMapPlayType_Kill:
		{
			m_pGoalTitle->setText(STR_Copy_Title_GoalKill);
			m_pCurTitle->setText(STR_Copy_Title_CurKill);
			m_pCountSeconds->setVisible(false);
		}
		break;
	case GameMapPlayType_Catch:
		{
			m_pGoalTitle->setText(STR_Copy_Title_GoalCatch);
			m_pCurTitle->setText(STR_Copy_Title_CurCatch);
			m_pCountSeconds->setVisible(true);
		}
		break;
	case GameMapPlayType_Destroy:
		{
			m_pGoalTitle->setText(STR_Copy_Title_GoalDestroy);
			m_pCurTitle->setText(STR_Copy_Title_CurDestroy);
			m_pCountSeconds->setVisible(true);
		}
		break;
	case GameMapPlayType_XB:
		{
			m_pGoalTitle->setText(STR_Copy_Title_GoalChests);
			m_pCurTitle->setText(STR_Copy_Title_CurChests);
			m_pCountSeconds->setVisible(true);
		}
		break;
	case GameMapPlayType_Save:
		{
			m_pGoalTitle->setText(STR_Copy_Title_GoalSave);
			m_pCurTitle->setText(STR_Copy_Title_CurSave);
			m_pCountSeconds->setVisible(true);
		}
		break;
	default:
		break;
	}
	StartCountSeconds(m_nCountSeconds);
}