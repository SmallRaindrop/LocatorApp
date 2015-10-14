#include "TeamUI.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/Hero.h"
#include "CustomCtrl/MenuForPlayer.h"
#include "Net/NetDispatcher.h"
#include "SysTipsMgr.h"
#include "DataPool.h"

TeamInfo CTeamUI::s_teamInfo;
pk::GS2C_GetOldTeamer_Ret CTeamUI::s_TeamRecent;

CTeamUI::CTeamUI()
	:GameUI(IDU_Social,JsonFile_Social)
{
	m_nCurGroup = -1;
	m_pSelSign = NULL;
}

CTeamUI::~CTeamUI()
{
	m_nCurGroup = -1;
	s_teamInfo.member_list.clear();
	s_teamInfo.leadId = s_teamInfo.teamId = 0;
	s_TeamRecent.teamerList.clear();
}

bool CTeamUI::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());
		m_pMainBg = Helper::seekWidgetByName(m_pWidget, "Image_Inner");
		Button *pClose	   = (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Exit");

		BREAK_IF(!(pClose&&m_pMainBg));

		pClose->addTouchEventListener(this, SEL_TouchEvent(&CTeamUI::clickExit));

		m_pList = CScrollTable::create(false, "Box_Team");
		m_pList->setSize(Size(654,346));
		m_pList->setPosition(Point(10,20));
		m_pList->SetFontSize(20);
		m_pList->SetSelectEvent(this, SEL_SelListIndexEvent(&CTeamUI::clickItem));
		/*队伍：队长标志，等级，名字，职业*/
		m_pList->SetFormat(TCT_IMAGE, 50, 0.5, 0.5, TCT_STRING, 86, 0.5, 0.5,TCT_STRING, 320, 0.5, 0.5, TCT_STRING, 560, 0.5, 0.5,TCT_NONE);
		m_pMainBg->addChild(m_pList);

		CheckBox *pBoxTeam = (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "CheckBox_Team"));
		CheckBox *pBoxFriend = (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "CheckBox_Friend"));
		CheckBox *pBoxRecent = (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "CheckBox_Recent"));
		CheckBox *pBoxRegion = (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "CheckBox_Region"));
		BREAK_IF(!(pBoxTeam&&pBoxFriend&&pBoxRecent&&pBoxRegion));

		m_pTabs = RadioButtonSet::create();
		pBoxTeam->getParent()->addChild(m_pTabs);
		m_pTabs->AddButton(pBoxTeam);
		m_pTabs->AddButton(pBoxFriend);
		m_pTabs->AddButton(pBoxRegion);
		m_pTabs->AddButton(pBoxRecent);
		m_pTabs->SetSelectEvent(this, SEL_SelectIndexEvent(&CTeamUI::clickTab));

		m_teampanel = Helper::seekWidgetByName(m_pWidget,"TeamPanel");
		m_allowMemMsg = (CheckBox*)Helper::seekWidgetByName(m_pWidget,"AllowMemAdd");
		m_allowMemMsg->setSelectedState(false);	//default 不勾选
		m_allowMemMsg->addEventListenerCheckBox(this,checkboxselectedeventselector(CTeamUI::clickAllow));
		Button* pAllowMemAddBtn = (Button*)Helper::seekWidgetByName(m_pWidget,"AllowMemAddBtn");
		pAllowMemAddBtn->addTouchEventListener(this,toucheventselector(CTeamUI::clickAllowAdd));
		m_Operate = Helper::seekWidgetByName(m_pWidget,"operate");
		m_menuForPerson = CMenuForPerson::create("Team_Menu","Team_Menu_BG");
		m_menuForPerson->SetDynamicShow(false);
		m_menuForPerson->_setInterval(30.0f);
		m_menuForPerson->setPosition(Point(95,335));
		m_Operate->addChild(m_menuForPerson);

		m_pTabs->ClickButton(0);
		return true;
	} while (0);

	return false;
}

void CTeamUI::onOpen()
{
	if (m_nCurGroup>=0&&m_nCurGroup<4)
	{
		updateList(m_nCurGroup);
	}
}

void CTeamUI::clickTab(int index)
{
	m_nCurGroup = index;

	updateList(m_nCurGroup);
	m_teampanel->setEnabled(m_nCurGroup == 0);
}

void CTeamUI::updateList(int index)
{
	switch (index)
	{
	case 0:
		updateTeamList();
		break;
	case 1:
		updateFriendList();
		break;
	case 2:
		updateRegionList();
		break;
	case 3:
		{
			pk::C2GS_GetOldTeamer_Req cmd;
			cmd.Send(gNetSocket);
		}
		break;
	default:
		break;
	}
}

void CTeamUI::updateTeamList()
{
	TeamLayout();
	m_pList->Clear();
	m_pSelSign = NULL;
	for (unsigned int i=0; i<s_teamInfo.member_list.size(); ++i)
	{
		std::vector<Node*> itemNodes;
		itemNodes = m_pList->AddRow(s_teamInfo.member_list[i].id,(s_teamInfo.member_list[i].id==s_teamInfo.leadId)?"flag_team":"",
			CCString::createWithFormat("%d", s_teamInfo.member_list[i].level)->getCString(),WrapLongName(s_teamInfo.member_list[i].name).c_str(),
			GetCareerDes(s_teamInfo.member_list[i].career).c_str());

		//显示在线状态颜色
		Color3B color = IsOnline(s_teamInfo.member_list[i].id)?Color3B::WHITE:Color3B::GRAY;
		//是自己的话 显示绿色
		if(s_teamInfo.member_list[i].id == gHero->GetId()) color = Color3B::GREEN;

		((Text*)(itemNodes[1]))->setColor(color);
		((Text*)(itemNodes[2]))->setColor(color);
		((Text*)(itemNodes[3]))->setColor(color);
	}
	m_pList->ClickButton(0);
	m_allowMemMsg->setTouchEnabled(IsLeader());
	m_menuForPerson->setEnabled(!s_teamInfo.member_list.empty());
}

void CTeamUI::updateFriendList()
{
	OtherLayout();
	m_pList->Clear();
	m_pSelSign = NULL;
	FriendInfo_v& friendList = gDataPool->getFriendList();
	for (unsigned int i=0; i<friendList.size(); ++i)
	{
		if(!friendList[i].online) continue;

		std::vector<Node*> itemNodes;
		itemNodes = m_pList->AddRow(friendList[i].playerId,"",
			CCString::createWithFormat("%d", friendList[i].level)->getCString(),WrapLongName(friendList[i].name).c_str(),
			GetCareerDes(friendList[i].career).c_str());
	}
	m_pList->ClickButton(0);
	m_menuForPerson->setEnabled(m_pList->GetItemNum()!=0);
}

void CTeamUI::updateRegionList()
{
	OtherLayout();
	m_pList->Clear();
	m_pSelSign = NULL;
	m_pList->ClickButton(0);
	m_menuForPerson->setEnabled(false);
}

void CTeamUI::updateRecentList()
{
	OtherLayout();
	m_pList->Clear();
	m_pSelSign = NULL;
	for (unsigned int i=0; i<s_TeamRecent.teamerList.size(); ++i)
	{
		m_pList->AddRow(s_TeamRecent.teamerList[i].id,"",
			CCString::createWithFormat("%d", s_TeamRecent.teamerList[i].level)->getCString(),WrapLongName(s_TeamRecent.teamerList[i].name).c_str(),
			GetCareerDes(s_TeamRecent.teamerList[i].career).c_str());
	}

	m_pList->ClickButton(0);
	m_menuForPerson->setEnabled(!s_TeamRecent.teamerList.empty());
}

void CTeamUI::clickItem(int nIndex, long long nPlayerID)
{
	m_playerId = nPlayerID;
	Point pos = m_Operate->getPosition();
	switch (m_nCurGroup)
	{
	case 0:
		{
			if (IsLeader())
			{
				m_menuForPerson->AddMenu(nPlayerID,CMenuForPerson::PO_EQUI,CMenuForPerson::PO_FRIEND, CMenuForPerson::PO_TEAM_KICK,CMenuForPerson::PO_TEAM_LEAVE,0);
			} 
			else
			{
				m_menuForPerson->AddMenu(nPlayerID,CMenuForPerson::PO_EQUI,CMenuForPerson::PO_FRIEND,CMenuForPerson::PO_TEAM_LEAVE,0);
			}
		}
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		m_menuForPerson->AddMenu(nPlayerID,CMenuForPerson::PO_EQUI,CMenuForPerson::PO_TEAM,CMenuForPerson::PO_FRIEND,0);
		break;
	default:
		break;
	}
	updateSelState(nIndex);
}

void CTeamUI::updateSelState(int nIndex)
{
	Widget* pRow = m_pList->GetItem(nIndex);
	if(!pRow) return;
	Widget* pSel = pRow->getChildByName("Sel");
	if(!pSel) return;
	if(m_pSelSign) m_pSelSign->setVisible(false);
	pSel->setVisible(true);
	m_pSelSign = pSel;
}

void CTeamUI::clickExit(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

void CTeamUI::clickAllow(Ref* pSender, CheckBoxEventType type)
{
	//pk::C2GS_ChangePermitAllMemberCanInvite_Req cmd;
	//cmd.isPermitNum = (type == CHECKBOX_STATE_EVENT_SELECTED)?1:0;
	//cmd.Send(gNetSocket);
}

void CTeamUI::clickAllowAdd(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		if (IsLeader())
		{
			m_allowMemMsg->setSelectedState(!m_allowMemMsg->getSelectedState());
			pk::C2GS_ChangePermitAllMemberCanInvite_Req cmd;
			cmd.isPermitNum = m_allowMemMsg->getSelectedState()?1:0;
			cmd.Send(gNetSocket);
		}
	}
}

void CTeamUI::updateTeamAllowInfo()
{
	m_allowMemMsg->setSelectedState(s_teamInfo.isPermitNum == 1);
}

void CTeamUI::updateTeamOnlineState()
{
	Text* pText = NULL;
	for (unsigned int i=0; i<s_teamInfo.member_list.size(); ++i)
	{
		Widget* pRow = m_pList->GetItemByUserDate(s_teamInfo.member_list[i].id);
		if(!pRow) continue;
		Color3B color = s_teamInfo.member_list[i].online?Color3B::GRAY:Color3B::WHITE;
		Vector<Node*> itemNodes = pRow->getChildren();
		for (auto& text : itemNodes)
		{
			pText = (Text*)text;
			if(pText) pText->setColor(color);
		}
	}
}

void CTeamUI::TeamLayout()
{
	m_pMainBg->setSize(Size(874,454));
	m_Operate->setSize(Size(184,436));
	m_pList->setSize(Size(654,346));
	m_pMainBg->setPosition(Point(89+540,-9+285));
	m_Operate->setPosition(Point(417+540,-8+285));
}

void CTeamUI::OtherLayout()
{
	m_pMainBg->setSize(Size(874,484));
	m_Operate->setSize(Size(184,466));
	m_pList->setSize(Size(654,376));
	m_pMainBg->setPosition(Point(89+540,-24+285));
	m_Operate->setPosition(Point(417+540,-23+285));
}

