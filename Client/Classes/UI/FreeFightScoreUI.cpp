#include "FreeFightScoreUI.h"
#include "GameScene/GameUILayer.h"

CFreeFightScoreUI::CFreeFightScoreUI()
	:GameUI(IDU_FreeFightScore,JsonFile_FreeFightScoreUI)
{
	m_pRedScore = nullptr;
	m_pBlueScore = nullptr;
	m_pSlider = nullptr;
	m_pListView = nullptr;
	m_pListItem = nullptr;
}

CFreeFightScoreUI::~CFreeFightScoreUI()
{

}

bool CFreeFightScoreUI::onInit()
{
	do 
	{
		Button* pClose = (Button*)Helper::seekWidgetByName(m_pWidget,"BtnClose");
		m_pBlueScore = (Text*)Helper::seekWidgetByName(m_pWidget,"ScoreBlue");
		m_pRedScore = (Text*)Helper::seekWidgetByName(m_pWidget,"ScoreRed");
		Widget* pLeftPanel = Helper::seekWidgetByName(m_pWidget,"LeftPanel");	
		Widget* pRightPanel = Helper::seekWidgetByName(m_pWidget,"RightPanel");	
		BREAK_IF(!(pClose&&m_pBlueScore&&m_pRedScore&&pLeftPanel&&pRightPanel));
		pClose->addTouchEventListener(this,toucheventselector(CFreeFightScoreUI::clickExit));
		m_pSlider = (Slider*)Helper::seekWidgetByName(m_pWidget,"Slider");	
		m_pListView = (ListView*)Helper::seekWidgetByName(m_pWidget,"ListView_List");
		m_pListItem = Helper::seekWidgetByName(m_pWidget,"ListItem");	
		BREAK_IF(!(m_pSlider&&m_pListView&&m_pListItem));
		m_pListItem->setEnabled(false);
		return true;
	} while (0);
	return false;
}

void CFreeFightScoreUI::clickExit(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->destroyUI(this);
	}
}

void CFreeFightScoreUI::UpdateScore(pk::GS2C_FreeFightCopyScoreBoard* value)
{
	m_pBlueScore->setText(CCString::createWithFormat("%d",value->blueCampScore)->getCString());
	m_pRedScore->setText(CCString::createWithFormat("%d",value->redCampScore)->getCString());
	m_pListView->removeAllItems();
	size_t nSize = MAX(value->blueVec.size(),value->redVec.size());
	for (size_t i=0; i<nSize; ++i)
	{
		Widget* pItem = m_pListItem->clone();
		pItem->setEnabled(true);
		Text* pNameLeft = (Text*)pItem->getChildByName("Name_Left");
		Text* pLevelLeft = (Text*)pItem->getChildByName("Level_Left");
		Text* pCountLeft = (Text*)pItem->getChildByName("Count_Left");
		Text* pNameRight = (Text*)pItem->getChildByName("Name_Right");
		Text* pLevelRight = (Text*)pItem->getChildByName("Level_Right");
		Text* pCountRight = (Text*)pItem->getChildByName("Count_Right");
		BREAK_IF(!(pNameLeft&&pLevelLeft&&pCountLeft&&pNameRight&&pLevelRight&&pCountRight));
		if (i<value->blueVec.size())
		{
			pNameLeft->setText(value->blueVec[i].name);
			pLevelLeft->setText(CCString::createWithFormat("%d",value->blueVec[i].level)->getCString());
			pCountLeft->setText(CCString::createWithFormat("%d/%d",value->blueVec[i].killCnt,value->blueVec[i].deadCnt)->getCString());
		} 
		else
		{
			pNameLeft->setText("");
			pLevelLeft->setText("");
			pCountLeft->setText("");
		}
		if (i<value->redVec.size())
		{
			pNameRight->setText(value->redVec[i].name);
			pLevelRight->setText(CCString::createWithFormat("%d",value->redVec[i].level)->getCString());
			pCountRight->setText(CCString::createWithFormat("%d/%d",value->redVec[i].killCnt,value->redVec[i].deadCnt)->getCString());
		} 
		else
		{
			pNameRight->setText("");
			pLevelRight->setText("");
			pCountRight->setText("");
		}
		m_pListView->pushBackCustomItem(pItem);
	}
	m_pSlider->setList(m_pListView, Slider::ListType::LISTVIEW_TYPE);
}