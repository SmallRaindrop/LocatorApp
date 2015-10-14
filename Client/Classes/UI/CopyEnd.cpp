#include "CopyEnd.h"
#include "GameScene/GameUILayer.h"
#include "TeamUI.h"
#include "GameScene/TaskMgr.h"
#include "DramaUi.h"

CCopyEnd::CCopyEnd()
	:GameUI(IDU_CopyEnd,JsonFile_CopyEnd)
{

}

CCopyEnd::~CCopyEnd()
{
	CC_SAFE_RELEASE_NULL(m_pGridsUI);
}

bool CCopyEnd::onInit()
{
	do 
	{
		Widget* pMain = Helper::seekWidgetByName(m_pWidget,"Image_23");
		Button* pClose = (Button*)Helper::seekWidgetByName(m_pWidget,"BtnClose");
		pClose->addTouchEventListener(this,toucheventselector(CCopyEnd::clickExit));

		m_pStaticstPanel = Helper::seekWidgetByName(m_pWidget,"PanelStatistics");	
		m_pRewardPanel = Helper::seekWidgetByName(m_pWidget,"PanelReward");


		CheckBox *pBoxStatistics = (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "CheckBox_Statistics"));
		CheckBox *pBoxReward = (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "CheckBox_Reward"));
		BREAK_IF(!(pBoxStatistics&&pBoxReward));

		for (int i=0; i<TeamSize; ++i)
		{
			m_name[i] = (Text*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("Name_%d",i)->getCString());
			m_harm[i] = (Text*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("harm_%d",i)->getCString());
			m_bear[i] = (Text*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("bear_%d",i)->getCString());
			m_kill[i] = (Text*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("kill_%d",i)->getCString());
			m_dead[i] = (Text*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("dead_%d",i)->getCString());
			m_relive[i] = (Text*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("relive_%d",i)->getCString());
		}

		m_time = (Text*)Helper::seekWidgetByName(m_pWidget,"Time");
		m_money = (Text*)Helper::seekWidgetByName(m_pWidget,"Money");
		m_exp = (Text*)Helper::seekWidgetByName(m_pWidget,"Exp");

		RadioButtonSet* pTabs = RadioButtonSet::create();
		pBoxStatistics->getParent()->addChild(pTabs);
		pTabs->AddButton(pBoxStatistics);
		pTabs->AddButton(pBoxReward);
		pTabs->SetSelectEvent(this, SEL_SelectIndexEvent(&CCopyEnd::clickTab));
		pTabs->ClickButton(0);

		m_pGridsUI = Helper::seekWidgetByName(m_pWidget, "GridsPanel");
		m_pItemList = (ListView*)Helper::seekWidgetByName(m_pWidget, "ListView_Items");
		m_pSlider = (Slider*)Helper::seekWidgetByName(m_pWidget,"Slider");
		BREAK_IF(!(m_pGridsUI&&m_pItemList&&m_pSlider));
		CC_SAFE_RETAIN(m_pGridsUI);
		m_pGridsUI->removeFromParentAndCleanup(true);

		return true;
	} while (0);
	return false;
}

void CCopyEnd::onOpen()
{

}

void CCopyEnd::onClose()
{
	Task* pTask = gCopyDataMgr->GetCopyDoingTask();
	if (pTask)
	{
		DramaUI::PlayDrama(pTask->GetQuitCopyDramaId());
		gCopyDataMgr->SetCopyDoingTask(nullptr);
	}
	gGridsManager->removeAllGrids(emGrids_CopyCheckout);
	m_pItemList->removeAllItems();
}

void CCopyEnd::clickTab(int index)
{
	m_pStaticstPanel->setEnabled(index == 0);
	m_pStaticstPanel->setVisible(index == 0);
	m_pRewardPanel->setEnabled(index == 1);
	m_pRewardPanel->setVisible(index == 1);
}

void CCopyEnd::clickExit(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

void CCopyEnd::updateCheckOut(pk::GS2C_CopyMapCheckOut* value)
{
	for (size_t i=0; i<TeamSize; ++i)
	{
		if (i<value->fightStats.size())
		{
			m_name[i]->setText(value->fightStats[i].playerName);
			m_harm[i]->setText(CCString::createWithFormat("%d%%",value->fightStats[i].damagePercent)->getCString());
			m_bear[i]->setText(CCString::createWithFormat("%d%%",value->fightStats[i].bearDamagePercent)->getCString());
			m_kill[i]->setText(CCString::createWithFormat("%d",value->fightStats[i].killCnt)->getCString());
			m_dead[i]->setText(CCString::createWithFormat("%d",value->fightStats[i].deadCnt)->getCString());
			m_relive[i]->setText(CCString::createWithFormat("%d",value->fightStats[i].reliveCnt)->getCString());
		} 
		else
		{
			m_name[i]->setText("");
			m_harm[i]->setText("");
			m_bear[i]->setText("");
			m_kill[i]->setText("");
			m_dead[i]->setText("");
			m_relive[i]	->setText("");
		}
	}

	m_time->setText(CCString::createWithFormat("%d",value->steps)->getCString());
	m_money->setText(CCString::createWithFormat("%d",value->coin)->getCString());
	m_exp->setText(CCString::createWithFormat("%d",value->exp)->getCString());

	if(value->itemInfos.empty())
	{
		m_pSlider->setEnabled(false);
		return;
	}

	m_pSlider->setEnabled(true);
	int nPages = getPageNum(value->itemInfos.size(),Page_Size_CopyCheckOut);
	for (int i=0; i<nPages; i++)
	{
		CGridArrayUI* pUI = CGridArrayUI::create(emGrids_CopyCheckout,i*Page_Size_CopyCheckOut,Page_Size_CopyCheckOut,m_pGridsUI->clone());
		if (pUI)
		{
			m_pItemList->pushBackCustomItem(pUI);
			gGridsManager->attachUI(pUI,emGrids_CopyCheckout,i);
		}
	}
	m_pSlider->setList(m_pItemList, Slider::ListType::LISTVIEW_TYPE);
	for (size_t i=0; i < value->itemInfos.size(); i++)
	{
		gGridsManager->insertGrid(emGrids_CopyCheckout, i, value->itemInfos[i].itemDataID, value->itemInfos[i].cnt);
	}
}