#include "Relive.h"
#include "../GameScene/Hero.h"
#include "../Net/NetDispatcher.h"

#define Max_Relive_Choices			(3)
#define Town_Auto_Cd				(60)

CReliveUI::CReliveUI()
	:GameUI(IDU_REVIVEANDBACK,JSONFILE_RELIVE)
	,m_pTownDesc(NULL)
	,m_pTownBtn(NULL)
	,m_pNearDesc(NULL)
	,m_pNearBtn(NULL)
	,m_pSamePlaceDesc(NULL)
	,m_pSamePlaceBtn(NULL)
	,m_nTownRuleId(0)
	,m_nNearRuleId(0)
	,m_nSamePlaceRuleId(0)
	,m_pTownMask(NULL)
	,m_pNearMask(NULL)
	,m_pSamePlaceMask(NULL)
	,m_nTownCd(0)
	,m_nNearCd(0)
	,m_nSamePlaceCd(0)
	,m_nTownAutoCd(0)
{

}

CReliveUI::~CReliveUI()
{

}

bool CReliveUI::onInit()
{
	m_pWidget->setScale(0.5f);
	Widget* pRelivePanel = m_pWidget->getChildByName("RelivePanel");
	if (!pRelivePanel)
	{
		return false;
	}

	Widget* pTownPanel = pRelivePanel->getChildByName("TownPanel");
	Widget* pNearPanel = pRelivePanel->getChildByName("NearPanel");
	Widget* pSamePlacePanel = pRelivePanel->getChildByName("SamePlacePanel");
	if (!pTownPanel || !pNearPanel || !pSamePlacePanel)
	{
		return false;
	}

	m_pTownDesc = dynamic_cast<Text*>(pTownPanel->getChildByName("TownDesc"));
	m_pTownBtn = dynamic_cast<Button*>(pTownPanel->getChildByName("TownBtn"));
	m_pNearDesc = dynamic_cast<Text*>(pNearPanel->getChildByName("NearDesc"));
	m_pNearBtn = dynamic_cast<Button*>(pNearPanel->getChildByName("NearBtn"));
	m_pSamePlaceDesc = dynamic_cast<Text*>(pSamePlacePanel->getChildByName("SamePlaceDesc"));
	m_pSamePlaceBtn = dynamic_cast<Button*>(pSamePlacePanel->getChildByName("SamePlaceBtn"));
	if (!m_pTownDesc || !m_pTownBtn || !m_pNearDesc || !m_pNearBtn || !m_pSamePlaceDesc || !m_pSamePlaceBtn)
	{
		return false;
	}
	m_pTownBtn->addTouchEventListener(this,toucheventselector(CReliveUI::clickTownBtn));
	m_pNearBtn->addTouchEventListener(this,toucheventselector(CReliveUI::clickNearBtn));
	m_pSamePlaceBtn->addTouchEventListener(this,toucheventselector(CReliveUI::clickSamePlaceBtn));

	m_pTownMask = pTownPanel->getChildByName("TownMaskPanel");
	m_pNearMask = pNearPanel->getChildByName("NearMaskPanel");
	m_pSamePlaceMask = pSamePlacePanel->getChildByName("SamePlaceMaskPanel");
	if (!m_pTownMask || !m_pNearMask || !m_pSamePlaceMask)
	{
		return false;
	}

	return true;
}

void CReliveUI::onOpen()
{
	initialState();

	vector<int> rules = gMap->getReliveRules();

	for (size_t i=0; i<rules.size()&&i<Max_Relive_Choices; ++i)
	{
		RecoverLifeRuleCfg* pRuleCfg = RecoverLifeRuleData.get(rules[i]);
		if(!pRuleCfg) continue;
		showReliveChoice(pRuleCfg);
	}
}

void CReliveUI::onClose()
{

}

void CReliveUI::initialState()
{
	m_pTownDesc->setText("");
	m_pNearDesc->setText("");
	m_pSamePlaceDesc->setText("");
	m_pTownBtn->setBright(false);
	m_pTownBtn->setTouchEnabled(false);
	m_pNearBtn->setBright(false);
	m_pNearBtn->setTouchEnabled(false);
	m_pSamePlaceBtn->setBright(false);
	m_pSamePlaceBtn->setTouchEnabled(false);
	m_pTownMask->setEnabled(false);
	m_pNearMask->setEnabled(false);
	m_pSamePlaceMask->setEnabled(false);
	m_nTownCd = 0;
	m_nNearCd = 0;
	m_nSamePlaceCd = 0;
}

void CReliveUI::showReliveChoice(RecoverLifeRuleCfg* pRuleCfg)
{
	Text* pDesc = NULL;
	Button* pBtn = NULL;
	Widget* pMask = NULL;

	switch (pRuleCfg->type)
	{
	case 1:
		m_nTownRuleId = pRuleCfg->id;
		pDesc = m_pTownDesc;
		pBtn = m_pTownBtn;
		pMask = m_pTownMask;
		m_nTownCd = pRuleCfg->delay_seconds+1;
		break;
	case 2:
		m_nNearRuleId = pRuleCfg->id;
		pDesc = m_pNearDesc;
		pBtn = m_pNearBtn;
		pMask = m_pNearMask;
		m_nNearCd = pRuleCfg->delay_seconds+1;
		break;
	case 3:
		m_nSamePlaceRuleId = pRuleCfg->id;
		pDesc = m_pSamePlaceDesc;
		pBtn = m_pSamePlaceBtn;
		pMask = m_pSamePlaceMask;
		m_nSamePlaceCd = pRuleCfg->delay_seconds+1;
		break;
	}

	string StrCostPrefix = STR_Relive_CostDesc;
	string StrCostNum = CCString::createWithFormat("%d",pRuleCfg->consume_cnt_or_id)->getCString();
	string StrCostSuffix = "";
	switch (pRuleCfg->consume_type)
	{
	case 0:
		StrCostPrefix = "";
		StrCostNum = STR_Relive_Free.c_str();
		StrCostSuffix = "";
		break;
	case 1:
		StrCostSuffix = STR_Relive_Money;
		break;
	case 2:
		StrCostSuffix = STR_Relive_BindMoney;
		break;
	case 3:
		StrCostSuffix = STR_Relive_Gold;
		break;
	case 5:
		{
			ItemCfg* pCfg = ItemData.get(pRuleCfg->consume_cnt_or_id);
			if (pCfg)
			{
				StrCostNum = pCfg->name.c_str();
			}
		}
		break;
	}

	char str[256] = {0};
	sprintf(str,"%s%s%s",StrCostPrefix.c_str(),StrCostNum.c_str(),StrCostSuffix.c_str());
	pDesc->setText(str);

	if (pRuleCfg->delay_seconds == 0)
	{
		pBtn->setBright(true);
		pBtn->setTouchEnabled(true);
	}
	else
	{
		pMask->setEnabled(true);
		if (pRuleCfg->type == 1)
		{
			this->schedule(schedule_selector(CReliveUI::townTicker),1.0f,m_nTownCd-1,0.0f);
		}
		else if(pRuleCfg->type == 2)
		{
			this->schedule(schedule_selector(CReliveUI::nearTicker),1.0f,m_nNearCd-1,0.0f);
		}
		else
		{
			this->schedule(schedule_selector(CReliveUI::samePlaceTicker),1.0f,m_nSamePlaceCd-1,0.0f);
		}
	}
	m_nTownAutoCd = Town_Auto_Cd+1;
	this->schedule(schedule_selector(CReliveUI::townAutoTicker),1.0f,m_nTownAutoCd-1,0.0f);
}

void CReliveUI::townAutoTicker(float dt)
{
	m_nTownAutoCd--;
	if (m_nTownAutoCd <= 0)
	{
		clickTownBtn(NULL,TOUCH_EVENT_ENDED);
	}
	else
	{
		char str[16] = {0};
		sprintf(str,"%d",m_nTownAutoCd);
		m_pTownDesc->setText(str);
	}
}

void CReliveUI::townTicker(float dt)
{
	m_pTownMask->removeAllChildrenWithCleanup(true);
	m_nTownCd--;
	if (m_nTownCd<=0)
	{
		m_pTownMask->setEnabled(false);
		m_pTownBtn->setBright(true);
		m_pTownBtn->setTouchEnabled(true);
	}
	else
	{
		char str[16] = {0};
		sprintf(str,"%d",m_nTownCd);
		Label* pFont = Label::createWithBMFont("assets/common/font/Relive.fnt",str);
		pFont->setScale(2.0f);
		pFont->setPosition(Point(276,450));
		m_pTownMask->addChild(pFont);
	}
}

void CReliveUI::nearTicker(float dt)
{
	m_pNearMask->removeAllChildrenWithCleanup(true);
	m_nNearCd--;
	if (m_nNearCd<=0)
	{
		m_pNearMask->setEnabled(false);
		m_pNearBtn->setBright(true);
		m_pNearBtn->setTouchEnabled(true);
	}
	else
	{
		char str[16] = {0};
		sprintf(str,"%d",m_nTownCd);
		Label* pFont = Label::createWithBMFont("assets/common/font/Relive.fnt",str);
		pFont->setScale(2.0f);
		pFont->setPosition(Point(276,450));
		m_pNearMask->addChild(pFont);
	}
}

void CReliveUI::samePlaceTicker(float dt)
{
	m_pSamePlaceMask->removeAllChildrenWithCleanup(true);
	m_nSamePlaceCd--;
	if (m_nSamePlaceCd<=0)
	{
		m_pSamePlaceMask->setEnabled(false);
		m_pSamePlaceBtn->setBright(true);
		m_pSamePlaceBtn->setTouchEnabled(true);
	}
	else
	{
		char str[16] = {0};
		sprintf(str,"%d",m_nSamePlaceCd);
		Label* pFont = Label::createWithBMFont("assets/common/font/Relive.fnt",str);
		pFont->setScale(2.0f);
		pFont->setPosition(Point(276,450));
		m_pSamePlaceMask->addChild(pFont);
		//m_pSamePlaceMask->runAction(CCSequence::create(CCDelayTime::create(1.0f),CallFuncN::create(CC_CALLBACK_0(CReliveUI::samePlaceTicker,this)),NULL));
	}
}

void CReliveUI::unscheduleAllTicker()
{
	this->unschedule(schedule_selector(CReliveUI::townTicker));
	this->unschedule(schedule_selector(CReliveUI::nearTicker));
	this->unschedule(schedule_selector(CReliveUI::samePlaceTicker));
	this->unschedule(schedule_selector(CReliveUI::townAutoTicker));
}

void CReliveUI::clickTownBtn(Ref *pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		pk::C2GS_RecoverLife_Req cmd;
		cmd.recoverRuleId = m_nTownRuleId;
		cmd.Send(gNetSocket);
	}
}

void CReliveUI::clickNearBtn(Ref *pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		pk::C2GS_RecoverLife_Req cmd;
		cmd.recoverRuleId = m_nNearRuleId;
		cmd.Send(gNetSocket);
	}
}

void CReliveUI::clickSamePlaceBtn(Ref *pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		pk::C2GS_RecoverLife_Req cmd;
		cmd.recoverRuleId = m_nSamePlaceRuleId;
		cmd.Send(gNetSocket);
	}
}