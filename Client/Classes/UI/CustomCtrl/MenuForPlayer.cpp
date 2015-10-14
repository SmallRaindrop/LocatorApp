#include "MenuForPlayer.h"
#include "Net/pk_chat.h"
#include "Net/pk_team.h"
#include "Net/pk_friend.h"
#include "Net/NetDispatcher.h"
#include "UI/TeamUI.h"
#include "UI/MessageBoxUI.h"
#include "GameScene/Hero.h"
#include "GameScene/GameTipsLayer.h"
#include "GameScene/MessageCenter.h"
#include "../../Net/pk_trade.h"
#include "UI/ChatMainUI.h"

//-----------------------------------------------CMenuForPerson----------------------------------------------------------
extern const char *arrFriendTypes[4];

const char *CMenuForPerson::PO_MSG				= "@msg@";		//发聊天消息
const char *CMenuForPerson::PO_TEAM				= "@team@";	//邀请组队
const char *CMenuForPerson::PO_MAIL				= "@mail@";	//发送邮件
const char *CMenuForPerson::PO_EQUI				= "@equi@";	//查看装备
const char *CMenuForPerson::PO_SEARCH			= "@search@";	
const char *CMenuForPerson::PO_FRIEND			= "@friend@";	//添加好友
const char *CMenuForPerson::PO_BLACKLIST		= "@blacklist@";
const char *CMenuForPerson::PO_ENEMY			= "@enemy@";
const char *CMenuForPerson::PO_DEL				= "@del@";		//删除好友
const char *CMenuForPerson::PO_TEAM_KICK		= "@teamkick@";	//队伍踢人
const char *CMenuForPerson::PO_TEAM_HANDOVER	= "@teamhandover@";
const char *CMenuForPerson::PO_TRADE			= "@trade@";
const char *CMenuForPerson::PO_TEAM_LEAVE		= "@teamLeave@";
const char *CMenuForPerson::PO_MASK			= "@mask@";
const char *CMenuForPerson::PO_NAME_COPY		= "@namecopy@";

int64 CMenuForPerson::s_nPlayerID;
string CMenuForPerson::s_nPlayerName;
bool CMenuForPerson::s_bPlayerOnline;
map<const char*, const char*> mpCustomItems;
#define DEF_DADIUS 210

CMenuForPerson::CMenuForPerson(void)
{
	mpCustomItems.insert(make_pair(PO_MSG, STR_Private_Msg));
	mpCustomItems.insert(make_pair(PO_TEAM, STR_Team_Invite));
	mpCustomItems.insert(make_pair(PO_MAIL, STR_MENU_SENDMAIL));
	mpCustomItems.insert(make_pair(PO_EQUI, STR_Check_Player));
	mpCustomItems.insert(make_pair(PO_SEARCH, STR_MENU_SEARCH));
	mpCustomItems.insert(make_pair(PO_FRIEND, STR_Add_Friend));
	mpCustomItems.insert(make_pair(PO_BLACKLIST, STR_MENU_ADDBLACKLIST));
	mpCustomItems.insert(make_pair(PO_ENEMY, STR_MENU_ADDENEMY));
	mpCustomItems.insert(make_pair(PO_DEL, STR_MENU_DELETE));
	mpCustomItems.insert(make_pair(PO_TEAM_KICK, STR_Team_Kickout));
	mpCustomItems.insert(make_pair(PO_TEAM_HANDOVER, STR_MENU_TEAMHANDOVER));
	mpCustomItems.insert(make_pair(PO_TRADE, STR_MENU_TRADE));
	mpCustomItems.insert(make_pair(PO_TEAM_LEAVE, STR_Team_Leave));
	mpCustomItems.insert(make_pair(PO_MASK, STR_Mask_Msg));
	mpCustomItems.insert(make_pair(PO_NAME_COPY, STR_CopyName));

	m_nCurFadeOutIndex = 0;
	m_nRadius = DEF_DADIUS;
}

void CMenuForPerson::AddItem(const char* strCaption, bool bDisabled)
{
	map<const char*, const char*>::iterator it = mpCustomItems.find(strCaption);
	if (it != mpCustomItems.end())
	{
		CMenu::AddItem(it->second, bDisabled);
		m_mpCustomItems.insert(make_pair(m_vtrButtons.back(), strCaption));
		return;
	}


	CMenu::AddItem(strCaption, bDisabled);
}

extern Point ptWindowLB2UILayer;
extern Point ptWindowRT2UILayer;

void CMenuForPerson::LayOut()
{
	// 重新布局菜单项
	float fDegreeStep = 2 * (float)M_PI / MAX(7, m_vtrButtons.size());
	float fDegreeStart= (float)M_PI / 2;
	for (size_t i = 0; i < m_vtrButtons.size(); i++)
	{
		Point pos(cos(fDegreeStart + i * fDegreeStep), sin(fDegreeStart + i * fDegreeStep));
		m_vtrButtons[i]->setAnchorPoint(Point(0.5f, 0.5f));
		m_vtrButtons[i]->setPosition(pos * m_nRadius);

		//m_vtrButtons[i]->getProtectedChildByTag(1)->setOpacity(0);
		m_vtrButtons[i]->setOpacity(0);
		m_vtrButtons[i]->stopAllActions();

	}

	if (m_vtrButtons.size() > 0)
	{
		int nMoveRight	= _position.x - m_nRadius - m_vtrButtons[0]->getSize().width / 2 - ptWindowLB2UILayer.x;
		int nMoveLeft	= _position.x + m_nRadius + m_vtrButtons[0]->getSize().width / 2 - ptWindowRT2UILayer.x;
		int nMoveDown	= _position.y - m_nRadius - m_vtrButtons[0]->getSize().height / 2 - ptWindowLB2UILayer.y;
		int nMoveUp		= _position.y + m_nRadius + m_vtrButtons[0]->getSize().height / 2 - ptWindowRT2UILayer.y;

		if (nMoveRight < 0)
		{
			setPositionX(_position.x - nMoveRight);
		}
		if (nMoveLeft > 0)
		{
			setPositionX(_position.x - nMoveLeft);
		}
		if (nMoveDown < 0)
		{
			setPositionY(_position.y - nMoveDown);
		}
		if (nMoveUp > 0)
		{
			setPositionY(_position.y - nMoveUp);
		}
	}

	m_pBG->setPosition(Point(0, 10));
	m_nCurFadeOutIndex = 0;
	OneItemFadeOut();
}

void CMenuForPerson::SetPlayer(int64 nPlayerID)
{
	s_nPlayerID = nPlayerID;
}

void CMenuForPerson::OneItemFadeOut()
{
	if ((int)m_vtrButtons.size() > m_nCurFadeOutIndex)
	{
		//m_vtrButtons[m_nCurFadeOutIndex]->getProtectedChildByTag(1)->runAction(FadeIn::create(0.05f));
		m_vtrButtons[m_nCurFadeOutIndex++]->runAction(Sequence::createWithTwoActions(FadeIn::create(0.05f),CallFunc::create( CC_CALLBACK_0(CMenuForPerson::OneItemFadeOut,this))));
	}
}

void CMenuForPerson::ClickButton(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (s_nPlayerID)
		{
			map<Ref*, const char*>::iterator it = m_mpCustomItems.find(pSender);
			if (it != m_mpCustomItems.end())
			{
				if (it->second == PO_MSG)
				{
					//显示一个私聊频道
					ChatMainUI* pUI = (ChatMainUI*)gGameUILayer->open(IDU_CHATMAINUI);
					if(pUI) pUI->ShowPrivateChannel(s_nPlayerID,s_nPlayerName);
				}
				else if (it->second == PO_TEAM)
				{
					
					if (CTeamUI::GetTeamMember(s_nPlayerID))
					{
						gMessageCenter->SystemMessage(107);
					}
					else if (CTeamUI::s_teamInfo.teamId!=0&&!CTeamUI::IsLeader()&&!CTeamUI::s_teamInfo.isPermitNum)
					{
						//禁止队员邀请
						gMessageCenter->SystemMessage(1050);
					}
					else
					{
						pk::C2GS_InviteTeam_Req cmd = {s_nPlayerID};
						cmd.Send(gNetSocket);
					}
				}
				else if (it->second == PO_EQUI)
				{
					pk::C2GS_LookOverPlayerEquip cmd = {s_nPlayerID};
					cmd.Send(gNetSocket);
				}
				else if (it->second == PO_MAIL)
				{

				}
				else if (it->second == PO_SEARCH)
				{
				}
				else if (it->second == PO_FRIEND)
				{
					pk::C2GS_Add_Friend cmd = {s_nPlayerID, 1};
					cmd.Send(gNetSocket);
				}
				else if (it->second == PO_BLACKLIST)
				{
					pk::C2GS_Add_Friend cmd = {s_nPlayerID, 3};
					cmd.Send(gNetSocket);
				}
				else if (it->second == PO_ENEMY)
				{
					pk::C2GS_Add_Friend cmd = {s_nPlayerID, 2};
					cmd.Send(gNetSocket);
				}
				else if (it->second == PO_DEL)
				{
				}
				else if (it->second == PO_TEAM_KICK)
				{
					std::function<void(bool bYes)> func = [](bool bYes)
					{
						if(bYes)
						{
							pk::C2GS_TeamKickOutPlayer cmd = {s_nPlayerID};
							cmd.Send(gNetSocket);
						}
					};
					CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO, GameString.get(161)->value.c_str(),func,STR_MESSAGEBOX_COMFIRM.c_str(), STR_MESSAGEBOX_CANCEL.c_str(),
										this,NULL,CMessageBoxUI::Scene_Game);
				}
				else if (it->second == PO_TRADE)
				{
					pk::C2GS_RequestTrade cmd;
					cmd.desPlayerId = s_nPlayerID;
					cmd.Send(gNetSocket);
				}
				else if (it->second == PO_TEAM_LEAVE)
				{
					std::function<void(bool bYes)> func = [](bool bYes)
					{
						if(bYes)
						{
							pk::C2GS_ExitTeam_Req cmd;
							cmd.teamId = CTeamUI::s_teamInfo.teamId;
							cmd.Send(gNetSocket);
						}
					};
					CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO, GameString.get(1105)->value.c_str(),func,STR_MESSAGEBOX_COMFIRM.c_str(), STR_MESSAGEBOX_CANCEL.c_str(),
						this,NULL,CMessageBoxUI::Scene_Game);
				}

				if (m_bDynamicShow)
				{
					pSender->retain();
					pSender->autorelease();	// 本次按钮事件执行完毕之前被点击按钮不能被删除，否则本函数返回后发现按钮事件已经被撤销，点击事件会继续下去
					Clear();
				}
			}
		}
	}

	CMenu::ClickButton(pSender, type);
}

void CMenuForPerson::Clear()
{
	CMenu::Clear();
	m_mpCustomItems.clear();
	//s_nPlayerID = 0;
}

void CMenuForPerson::AddMenu(int64 nPlayerID,const char* strItem1, ...)
{
	Clear();
	SetPlayer(nPlayerID);
	va_list va;
	va_start(va, strItem1);

	const char *pTmp = strItem1;
	do
	{
		AddItem(pTmp);
	}
	while (pTmp = va_arg(va, const char*));
}


CMenuForPerson* CMenuForPerson::create(string nItemBGID, string nBGID, int nInterval)
{
	CMenuForPerson* rw = new CMenuForPerson();
	if(rw && rw->init())
	{
		rw->_setBGID(nBGID);
		rw->SetItemBGID(nItemBGID);
		rw->_setInterval(nInterval);
		rw->setTouchEnabled(true);
		rw->Clear();
		rw->autorelease();
		return rw;
	}
	CC_SAFE_DELETE(rw);
	return NULL;
}

void CMenuForPerson::PopupMenu(Point pos, int nRadius, int64 nPlayerID, Ref* pListenner, SEL_SelectIndexEvent pHandler, const char* strItem1, ...)
{
	gCocosAudio->PlayEffect(18);
	va_list va;
	va_start(va, strItem1);


	gMenu4PInst->Clear();
	gMenu4PInst->SetDynamicShow(true);
	gMenu4PInst->SetPlayer(nPlayerID);
	gMenu4PInst->setPosition(pos);
	gMenu4PInst->m_nRadius = (nRadius == 0 ? DEF_DADIUS : nRadius);

	const char *pTmp = strItem1;
	do
	{
		gMenu4PInst->AddItem(pTmp);
	}
	while (pTmp = va_arg(va, const char*));


	gMenu4PInst->SetSelectEvent(pListenner, pHandler);
	//gMenu4PInst->LayOut();
}

//成就弹出菜单
CMenuForAchievement* CMenuForAchievement::create(string nItemBGID, string nBGID, int nInterval)
{
	CMenuForAchievement* rw = new CMenuForAchievement();
	if(rw && rw->init())
	{
		rw->_setBGID(nBGID);
		rw->SetItemBGID(nItemBGID);
		rw->_setInterval(nInterval);
		rw->setTouchEnabled(true);
		rw->Clear();
		rw->autorelease();
		return rw;
	}
	CC_SAFE_DELETE(rw);
	return NULL;
}

void CMenuForAchievement::PopupMenu(Point pos, Ref* pListenner, SEL_SelectIndexEvent pHandler, const char* strItem1, ...)
{
	va_list va;
	va_start(va, strItem1);


	gMenu4Achievement->Clear();
	gMenu4Achievement->setPosition(pos);

	const char *pTmp = strItem1;
	do
	{
		gMenu4Achievement->AddItem(pTmp);
	}
	while (pTmp = va_arg(va, const char*));

	gMenu4Achievement->SetSelectEvent(pListenner, pHandler);
}

//匹配模式弹出菜单
CMenuForMatchMode* CMenuForMatchMode::create(string nItemBGID, string nBGID, int nInterval)
{
	CMenuForMatchMode* rw = new CMenuForMatchMode();
	if(rw && rw->init())
	{
		rw->_setBGID(nBGID);
		rw->SetItemBGID(nItemBGID);
		rw->_setInterval(nInterval);
		rw->setTouchEnabled(true);
		rw->autorelease();
		rw->Clear();

		return rw;
	}
	CC_SAFE_DELETE(rw);
	return NULL;
}

void CMenuForMatchMode::PopupMenu(Point pos, Ref* pListenner, SEL_SelectIndexEvent pHandler, const char* strItem1, ...)
{
	va_list va;
	va_start(va, strItem1);


	gMenu4MatchMode->Clear();
	gMenu4MatchMode->setPosition(pos);

	const char *pTmp = strItem1;
	do
	{
		gMenu4MatchMode->AddItem(pTmp);
	}
	while (pTmp = va_arg(va, const char*));

	gMenu4MatchMode->SetSelectEvent(pListenner, pHandler);
}