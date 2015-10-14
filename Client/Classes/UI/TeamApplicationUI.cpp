#include "TeamApplicationUI.h"
#include "Net/pk_chat.h"
#include "Net/NetDispatcher.h"
#include "UIHelper.h"
#include "GameScene/Hero.h"
#include "GameScene/db.h"
#include "GameScene/GameDataManager.h"
#include "GameScene/GameUILayer.h"
#include "CustomCtrl/RadioButtonSet.h"
#include "CustomCtrl/MenuForPlayer.h"
#include "CustomCtrl/ScrollTable.h"
#include "ResMgr/CtrlAllocator.h"
#include "GamePrompt.h"
#include "SysTipsMgr.h"

vector<TeamInviterInfo> TeamApplicationUI::s_Inviters;


TeamApplicationUI:: TeamApplicationUI() : 
	GameUI(IDU_TEAMAPPLICATION,JSONFILE_TEAMAPPLICATION)
{
	m_playerIdx = -1;
	m_pSelSign = NULL;
}

TeamApplicationUI:: ~TeamApplicationUI()
{
	s_Inviters.clear();
}

bool TeamApplicationUI:: onInit()
{
	if (!GameUI::onInit())
	{
		return false;
	}
    
	Widget *pListParent = Helper::seekWidgetByName(m_pWidget,"Image_55");
	Button *pClose	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Exit");
	Button *pRefuseAll	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_RefuseAll");
	Button *pAgree	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Agree");
	Button *pRefuse	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Refuse");
	pClose->addTouchEventListener(this, SEL_TouchEvent(&TeamApplicationUI::clickExit));
	pRefuseAll->addTouchEventListener(this, SEL_TouchEvent(&TeamApplicationUI::clickRefuseAll));
	pAgree->addTouchEventListener(this, SEL_TouchEvent(&TeamApplicationUI::clickAgree));
	pRefuse->addTouchEventListener(this, SEL_TouchEvent(&TeamApplicationUI::clickRefuse));

	m_pCandidatesList = CScrollTable::create(false, "Box_Team");
    m_pCandidatesList->setSize(Size(654, 230));
	m_pCandidatesList->SetFontSize(20);
	m_pCandidatesList->SetFormat(TCT_STRING, 86, 0.5, 0.5,TCT_STRING, 320, 0.5, 0.5, TCT_STRING, 560, 0.5, 0.5,TCT_NONE);
	m_pCandidatesList->SetSelectEvent(this, SEL_SelListIndexEvent(&TeamApplicationUI::clickItem));


	pListParent->addChild(m_pCandidatesList);

	return true;
}

void TeamApplicationUI::onOpen()
{
	gSysTipsMgr->StopTipsAction(systype_team);
	Reload();
}

void TeamApplicationUI::onClose()
{
	m_pCandidatesList->Clear();
	m_playerIdx = -1;
}

void TeamApplicationUI::Reload()
{
	m_pCandidatesList->Clear();
	m_pSelSign=NULL;
	for (size_t i = 0; i < s_Inviters.size(); i++)
	{
		m_pCandidatesList->AddRow(i, CCString::createWithFormat("%d",s_Inviters[i].lv)->getCString(),WrapLongName(s_Inviters[i].name).c_str(),GetCareerDes(s_Inviters[i].career).c_str());
	}
	if(!s_Inviters.empty())
	{
		clickItem(0,0);
	}
}

void TeamApplicationUI::clickItem(int nIndex, long long userdata)
{
	m_playerIdx = nIndex;
	updateSelState(nIndex);
}

void TeamApplicationUI::clickExit(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		gGameUILayer->close(this);
	}
}

void TeamApplicationUI::updateSelState(int nIndex)
{
	Widget* pRow = m_pCandidatesList->GetItem(nIndex);
	if(!pRow) return;
	Widget* pSel = pRow->getChildByName("Sel");
	if(!pSel) return;
	if(m_pSelSign) m_pSelSign->setVisible(false);
	pSel->setVisible(true);
	m_pSelSign = pSel;
}

void TeamApplicationUI::clickRefuseAll(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		for (size_t i = 0; i < s_Inviters.size(); i++)
		{
			pk::C2GS_AcceptOrRefuseTeamInvite cmd = {s_Inviters[i].id, 0};
			cmd.Send(gNetSocket);
		}

		s_Inviters.clear();

		m_pCandidatesList->Clear();
		gPromptCenter->setIconTeamMsgNum(GetCandidateNum());
	}
}


void TeamApplicationUI::clickAgree(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if(m_playerIdx == -1) return;
		pk::C2GS_AcceptOrRefuseTeamInvite cmd;
		cmd.inviterId = s_Inviters[m_playerIdx].id;
		cmd.isAccept = 1;
		cmd.Send(gNetSocket);

		s_Inviters.erase(s_Inviters.begin() + m_playerIdx);
		Reload();
		gPromptCenter->setIconTeamMsgNum(GetCandidateNum());
	}
}

void TeamApplicationUI::clickRefuse(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if(m_playerIdx == -1) return;
		pk::C2GS_AcceptOrRefuseTeamInvite cmd;
		cmd.inviterId = s_Inviters[m_playerIdx].id;
		cmd.isAccept = 0;
		cmd.Send(gNetSocket);

		s_Inviters.erase(s_Inviters.begin() + m_playerIdx);
		Reload();
		gPromptCenter->setIconTeamMsgNum(GetCandidateNum());
	}
}
