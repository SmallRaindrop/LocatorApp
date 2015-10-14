#include "GameDef.h"
#include "pk_team.h"
#include "ui/TeamUI.h"
#include "ui/MessageBoxUI.h"
#include "Net/NetDispatcher.h"
#include "GameScene/MessageCenter.h"
#include "UI/GamePrompt.h"
#include "UI/TeamApplicationUI.h"
#include "GameScene/Hero.h"
#include "SysTipsMgr.h"
#include "UI/MainUIFight.h"
#include "UI/WaveEnd.h"
#include "DataPool.h"
#include "UI/FriendUI.h"
#include "UI/ChatMainUI.h"
#include "UI/UIWorldMap.h"

//更新UI
void	UpdateTeamInTeamUI()
{
	CTeamUI *pUI = (CTeamUI*)gGameUILayer->getActiveUI(IDU_Social);
	if(pUI) pUI->updateTeamList();
}
void	UpdateTeamInMainUI()
{
	if( MainUI::GetActiveMainUI() ) 
	{
		MainUI::GetActiveMainUI()->updateTeamHead();
	}
}
void	UpdateTeamInWorldMap()
{
	CUIWorldMap* pWorldMapUI = (CUIWorldMap*)gGameUILayer->getActiveUI(IDU_WORLDMAPUI);
	if(pWorldMapUI) pWorldMapUI->ShowTeamIcon();
}

namespace pk{

	bool OnGS2C_JoinTeam_Req(GS2C_JoinTeam_Req *value)
	{
		TeamInviterInfo info;
		info.id = value->inviterId;
		info.name = value->inviterName;
		info.lv = value->inviterLevel;
		info.career = value->inviterCareer;
		TeamApplicationUI::s_Inviters.push_back(info);
		gSysTipsMgr->RunTipsAction(systype_team);
		return true;
	}

	bool OnGS2C_TeamInvite_Msg(GS2C_TeamInvite_Msg *value)
	{
		TeamInviterInfo info;
		info.id = value->inviterId;
		info.name = value->inviterName;
		info.lv = value->inviterLevel;
		info.career = value->inviterCareer;
		TeamApplicationUI::s_Inviters.push_back(info);
		gSysTipsMgr->RunTipsAction(systype_team);
		return true;
	}
	bool OnGS2C_TeamInfo(GS2C_TeamInfo *value)
	{
		CTeamUI::s_teamInfo.teamId = value->teamId;
		CTeamUI::s_teamInfo.leadId = value->leadId;
		CTeamUI::s_teamInfo.isPermitNum = value->isPermitNum;
		CTeamUI::s_teamInfo.member_list.clear();
		for (unsigned int i=0; i<value->member_list.size(); ++i)
		{
			TeamMember member;
			member.id = value->member_list[i].id;
			member.career = value->member_list[i].career;
			member.hp = value->member_list[i].hp;
			member.isContinue = -1;	//未选择
			member.level = value->member_list[i].level;
			member.maxhp = value->member_list[i].maxhp;
			member.name = value->member_list[i].name;
			member.online = 0;	//在线
			member.sex = value->member_list[i].sex;
			CTeamUI::s_teamInfo.member_list.push_back(member);
			if(gHero->GetId() != member.id)
			{
				Friend_Info* player = gDataPool->getRelativePlayerInfo( member.id);
				if(!player)
				{
					pk::Friend_Info rePlayer = {member.id, member.name, member.level, 1, 0,1,1,1,1};
					gDataPool->getRelativeList().push_back(rePlayer);
				}
				else
				{
					gDataPool->deletePListDataByID(gDataPool->getRelativeList(), member.id);
					pk::Friend_Info rePlayer = {member.id, member.name, member.level, 1, 0,1,1,1,1};
					gDataPool->getRelativeList().push_back(rePlayer);
				}
				gDataPool->sortPlayerByOnline(gDataPool->getRelativeList());
				auto pFriendui = dynamic_cast<FriendUI_cl*>(gGameUILayer->getActiveUI(IDU_Friend));
				if(pFriendui)
				{
					pFriendui->freshRelativeList();
				}
			}

		}
		gMacthMachine->UpdateMatchStatus();

		ChatMainUI* pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
		if(pChatUI) pChatUI->AddFixChannel(ChannelType_Team);
		UpdateTeamInTeamUI();
		UpdateTeamInMainUI();
		UpdateTeamInWorldMap();
		return true;
	}
	bool OnGS2C_AddTeamMember(GS2C_AddTeamMember *value)
	{
		TeamMember member;
		member.id = value->member.id;
		member.career = value->member.career;
		member.hp = value->member.hp;
		member.isContinue = -1;	//未选择
		member.level = value->member.level;
		member.maxhp = value->member.maxhp;
		member.name = value->member.name;
		member.online = 0;	//在线
		member.sex = value->member.sex;
		CTeamUI::s_teamInfo.member_list.push_back(member);

		Friend_Info* player = gDataPool->getRelativePlayerInfo( member.id);
		if(!player)
		{
			pk::Friend_Info rePlayer = {member.id, member.name, member.level, 1, 0,1,1,1,1};
			gDataPool->getRelativeList().push_back(rePlayer);
		}
		else
		{
			gDataPool->deletePListDataByID(gDataPool->getRelativeList(), member.id);
			pk::Friend_Info rePlayer = {member.id, member.name, member.level, 1, 0,1,1,1,1};
			gDataPool->getRelativeList().push_back(rePlayer);
		}
		gDataPool->sortPlayerByOnline(gDataPool->getRelativeList());
		auto pFriendui = (FriendUI_cl*)(gGameUILayer->getUI(IDU_Friend));
		if(pFriendui)
		{
			pFriendui->freshRelativeList();
		}
		gMacthMachine->UpdateMatchStatus();

		UpdateTeamInTeamUI();
		UpdateTeamInMainUI();
		UpdateTeamInWorldMap();

		gCocosAudio->PlayEffect(76);
		return true;
	}

	bool OnGS2C_RemoveTeamMember(GS2C_RemoveTeamMember *value)
	{
		bool bLeaveTeam = false;
		if (((pk::GS2C_RemoveTeamMember*)value)->memberId == gHero->GetId())
		{
			bLeaveTeam = true;

			CTeamUI::s_teamInfo.leadId = 0;
			CTeamUI::s_teamInfo.teamId = 0;
			CTeamUI::s_teamInfo.isPermitNum = 0;
			CTeamUI::s_teamInfo.member_list.clear();
		}
		else
		{
			for (size_t j = 0; j < CTeamUI::s_teamInfo.member_list.size(); j++)
			{
				CTeamUI::s_teamInfo.leadId = value->leadId;
				if ( value->memberId == CTeamUI::s_teamInfo.member_list[j].id)
				{
					CTeamUI::s_teamInfo.member_list.erase(CTeamUI::s_teamInfo.member_list.begin() + j);
					break;
				}
			}
		}
		gMacthMachine->UpdateMatchStatus();
		
		if (bLeaveTeam)
		{
			gGameUILayer->close(IDU_Social);
			ChatMainUI* pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
			if(pChatUI) pChatUI->CloseFixChanel(ChannelType_Team);
		} 
		else
		{
			UpdateTeamInTeamUI();
		}
		UpdateTeamInMainUI();
		UpdateTeamInWorldMap();

		gCocosAudio->PlayEffect(77);
		return true;
	}
	bool OnGS2C_RemoveTeam(GS2C_RemoveTeam *value)
	{
		gPromptCenter->stopIconTeamFlick();
		CTeamUI::s_teamInfo.leadId = 0;
		CTeamUI::s_teamInfo.teamId = 0;
		CTeamUI::s_teamInfo.isPermitNum = 0;
		CTeamUI::s_teamInfo.member_list.clear();
		gMacthMachine->UpdateMatchStatus();

		//组队界面
		gGameUILayer->close(IDU_Social);
		ChatMainUI* pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
		if(pChatUI) pChatUI->CloseFixChanel(ChannelType_Team);

		UpdateTeamInMainUI();
		UpdateTeamInWorldMap();

		return true;
	}
	bool OnGS2C_ChangeTeamSet_Ret(GS2C_ChangeTeamSet_Ret *value)
	{
		return true;
	}
	bool OnGS2C_ChangePermitAllMemberCanInvite(GS2C_ChangePermitAllMemberCanInvite* value)
	{
		CTeamUI::s_teamInfo.isPermitNum = value->isPermitNum;

		//组队界面
		CTeamUI *pUI = (CTeamUI*)gGameUILayer->getActiveUI(IDU_Social);
		if(pUI) pUI->updateTeamAllowInfo();

		return true;
	}
	bool OnGS2C_GetOldTeamer_Ret(GS2C_GetOldTeamer_Ret* value)
	{
		CTeamUI::s_TeamRecent = *value;
		CTeamUI *pUI = (CTeamUI*)gGameUILayer->getActiveUI(IDU_Social);
		if(pUI) pUI->updateRecentList();
		return true;
	}

	bool OnGS2C_TeamMemberState(GS2C_TeamMemberState* value)
	{
		for (unsigned i=0; i<CTeamUI::s_teamInfo.member_list.size(); ++i)
		{
			if (value->playerId == CTeamUI::s_teamInfo.member_list[i].id)
			{
				CTeamUI::s_teamInfo.member_list[i].online = value->online;
				CTeamUI::s_teamInfo.member_list[i].hp = value->hp;
				CTeamUI::s_teamInfo.member_list[i].maxhp = value->maxHp;
				break;
			}
		}

		//刷新队员在线状态
		CTeamUI *pUI = (CTeamUI*)gGameUILayer->getActiveUI(IDU_Social);
		if(pUI) pUI->updateTeamOnlineState();

		//刷新队员血量
		UpdateTeamInMainUI();

		return true;
	}
}

