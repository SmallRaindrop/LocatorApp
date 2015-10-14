#include "GameUILayer.h"
#include "UI/MessageBoxUI.h"
#include "UI/ChatMainUI.h"
#include "UI/UIWorldMap.h"
#include "UI/TeamUI.h"
#include "UI/TeamApplicationUI.h"
#include "UI/NpcDialog.h"
#include "UI/TaskUI.h"
#include "UI/TaskDialog.h"
#include "UI/CustomCtrl/MenuForPlayer.h"
#include "UI/Relive.h"
#include "UI/MainUINormal.h"
#include "UI/MainUIFight.h"
#include "UI/FightPause.h"
#include "UI/HeroInfo.h"
#include "UI/TeamUI.h"
#include "UI/DramaUi.h"
#include "UI/WaveEnd.h"
#include "UI/CopyEnd.h"
#include "UI/FriendUI.h"
#include "UI/MailUI.h"
#include "UI/RoleAttriUI.h"
#include "UI/RolePackageUI.h"
#include "UI/MissionUI.h"
#include "UI/SkyBookUI.h"
#include "UI/GodDeviceUI.h"
#include "UI/copyMapUI.h"
#include "UI/StrengthenUI.h"
#include "UI/ManufactureUI.h"
#include "UI/OneStroke.h"
#include "UI/OpenLock.h"
#include "UI/ReviveUI.h"
#include "UI/ItemTipsUI.h"
#include "UI/HallTechUI.h"
#include "UI/HallTechTreeUI.h"
#include "UI/AddLegionUI.h"
#include "UI/LegionUI.h"
#include "UI/FreeFightScoreUI.h"
#include "UI/FreeFightCheckOut.h"
#include "UI/CopyMapUICommon.h"
#include "UI/CopyMapUIContendFor.h"
#include "UI/CopyMapUIDef.h"
#include "UI/CopyMapUIFreeFight.h"
#include "UI/CopyMapUISurvive.h"

#define REG_UI(IDU,NAME)	registerUI(IDU,new UICreator_T<NAME>)

CGameUILayer::CGameUILayer()
{
	initialize();
}

CGameUILayer::~CGameUILayer()
{
	removeFromParent();
	release();
}

bool CGameUILayer::initialize()
{
	REG_UI(IDU_MESSAGEBOX,CMessageBoxUI);
	REG_UI(IDU_CHATMAINUI,ChatMainUI);
	REG_UI(IDU_WORLDMAPUI,CUIWorldMap);
	REG_UI(IDU_TEAMAPPLICATION,TeamApplicationUI);
	REG_UI(IDU_NPCDIALOG,CNpcDialog);
	REG_UI(IDU_TASKUI,TaskUI);
	REG_UI(IDU_TASKDIALOG,TaskDialog);
	REG_UI(IDU_REVIVEANDBACK,CReliveUI);
	REG_UI(IDU_MainUINormal,CMainUINormal);
	REG_UI(IDU_MainUIFight,CMainUIFight);
	REG_UI(IDU_FightPause,CFightPause);
	REG_UI(IDU_HeroInfo,CHeroInfo);
	REG_UI(IDU_Social,CTeamUI);
	REG_UI(IDU_Drama, DramaUI);
	REG_UI(IDU_Friend, FriendUI_cl);
	REG_UI(IDU_RoleAttri, RoleAttriUI_cl);
	REG_UI(IDU_RolePackage, RolePackageUI_cl);
	REG_UI(IDU_WaveEnd, CWaveEnd);
	REG_UI(IDU_CopyEnd, CCopyEnd);
	REG_UI(IDU_MailUI, CMailUI);
	REG_UI(IDU_MissionlUI, CMissionUI);
	REG_UI(IDU_SkyBookUI, SkyBookUI_cl);
	REG_UI(IDU_GodDeviceUI, CGodDeviceUI);
	REG_UI(IDU_CopyUIDef, CCopyMapUIDef);
	REG_UI(IDU_SkyBookCalcUI, SkyBookCalcUI_cl);
	REG_UI(IDU_StrengthenUI, CStrengthenUI);
	REG_UI(IDU_ManufactureUI, ManufactureUI_cl);
	REG_UI(IDU_OneStrokeUI, COneStroke);
	REG_UI(IDU_OpenLock, COpenLock);
	REG_UI(IDU_ReviveUI, CReviveUI);
	REG_UI(IDU_ITEMTIPSUI, ItemTipsUI);
	REG_UI(IDU_HallTechUI, CHallTechUI);
	REG_UI(IDU_CopyFreeFight, CCopyMapFreeFight);	
	REG_UI(IDU_HallTechTreeUI, CHallTechTreeUI);
	REG_UI(IDU_LegionUI, LegionUI_cl);
	REG_UI(IDU_AddLegionUI, AddLegionUI_cl);
	REG_UI(IDU_FreeFightScore, CFreeFightScoreUI);	
	REG_UI(IDU_CopyCommon, CCopyMapCommon);	
	REG_UI(IDU_FreeFightCheckOut, CFreeFightCheckOut);
	REG_UI(IDU_CopyUISurvive, CCopyMapUISurvive);
	REG_UI(IDU_CopyUIContendFor, CCopyMapContendFor);	

	addChild(CMenu::create(), Menu_Zorder, Menu_Tag);
	addChild(CMenuForPerson::create(), Menu_Zorder, Menu4Player_Tag);
	addChild(CMenuForAchievement::create(), Menu_Zorder, Menu4Achievement_Tag);
	addChild(CMenuForMatchMode::create(), Menu_Zorder, Menu4MatchMode_Tag);

	return true;
}

void CGameUILayer::release()
{
	for ( UICreators::iterator itr = m_UICreators.begin();itr != m_UICreators.end(); itr++ )
	{
		CC_SAFE_DELETE(itr->second);
	}

	m_UICreators.clear();

	destroyUI();
}

void CGameUILayer::update(float delta)
{
	for ( UITable::iterator itr = m_UITable.begin();itr != m_UITable.end(); itr++ )
	{
		GameUI* pUI = itr->second;
		if ( isActive(pUI) )
		{
			pUI->update(delta);
		}
	}
}


void CGameUILayer::registerUI(int idu,UICreator* pUICreator)
{
	UICreators::iterator itr = m_UICreators.find(idu);
	if ( itr != m_UICreators.end() )
	{
		delete pUICreator;
		return ;
	}

	m_UICreators[idu] = pUICreator;
}

UICreator* CGameUILayer::getUICreator(int idu)
{
	UICreators::iterator itr = m_UICreators.find(idu);
	if ( itr != m_UICreators.end() )
	{
		return itr->second;
	}

	return NULL;
}

GameUI*	CGameUILayer::createUI(int idu)
{
	UICreator* pUICreator = getUICreator(idu);
	if ( pUICreator )
	{
		GameUI* pUI=pUICreator->createUI();
		return pUI;
	}

	return NULL;
}

GameUI* CGameUILayer::getUI(int idu,bool bNew)
{
	UITable::iterator itr = m_UITable.find(idu);
	if ( itr != m_UITable.end() )
	{
		return itr->second;
	}

	if ( !bNew )
	{
		return NULL;
	}

	GameUI* pUI = createUI(idu);
	if ( pUI )
	{
		m_UITable[idu] = pUI;
	}

	return pUI;
}

bool CGameUILayer::isActive(int idu)
{
	GameUI* pUI = getUI(idu);
	if ( pUI && isActive(pUI) )
	{
		return true;
	}

	return false;
}

bool CGameUILayer::isActive(GameUI* pUI)
{
	if ( pUI && (pUI->getState() == GUIS_OPEN || pUI->getState() == GUIS_SHOW ) )
	{
		return true;
	}

	return false;
}

GameUI*	CGameUILayer::getActiveUI(int idu)
{
	GameUI* pUI = getUI(idu,false);
	if ( pUI && isActive(pUI) )
	{
		return pUI;
	}

	return NULL;
}

void CGameUILayer::show(int idu)
{
	GameUI* pUI = getUI(idu);
	if ( pUI )
	{
		show(pUI);
	}
}

void CGameUILayer::show(GameUI* pUI)
{
	if ( pUI && !isActive(pUI) )
	{
		pUI->onShow();
		pUI->setState(GUIS_SHOW);
	}
}

GameUI* CGameUILayer::open(int idu)
{
	GameUI* pUI = getUI(idu);
	if ( pUI )
	{
		open(pUI);
		openTogetherUI(idu);
		return pUI;
	}
	return NULL;
}

void CGameUILayer::open(GameUI* pUI)
{
	if ( pUI && !isActive(pUI) )
	{
		pUI->onOpen();
		pUI->setState(GUIS_OPEN);
		addChild(pUI);
		gCocosAudio->PlayEffect(126);
	}
}

void CGameUILayer::openTogetherUI(int idu)
{
	map<int,int>::iterator itr = m_UITogetherTable.find(idu);
	if ( itr != m_UITogetherTable.end() )
	{
		if (!isActive(itr->second))
		{
			open(itr->second);
		}
	}
}

void CGameUILayer::close(int idu)
{
	GameUI* pUI = getActiveUI(idu);
	if ( pUI )
	{
		close(pUI);
		closeTogetherUI(idu);
	}
}

void CGameUILayer::close(GameUI* pUI)
{
	if ( pUI && isActive(pUI))
	{
		pUI->onClose();
		pUI->setState(GUIS_CLOSED);
		removeChild(pUI,true);
		gCocosAudio->PlayEffect(127);
	}
}

void CGameUILayer::closeTogetherUI(int idu)
{
	map<int,int>::iterator itr = m_UITogetherTable.find(idu);
	if ( itr != m_UITogetherTable.end() )
	{
		close(itr->second);
	}
}

void CGameUILayer::closeOtherUIs()
{
	for ( UITable::iterator itr = m_UITable.begin();itr != m_UITable.end(); itr++ )
	{
		GameUI* pUI = itr->second;
		if ( isActive(pUI) )
		{
			if( pUI->getIDU() == IDU_CHATMAINUI)
			{
				continue;
			}

			close(pUI);
		}
	}
}


void CGameUILayer::destroyUI(int idu)
{
	GameUI* pUI = getUI(idu,false);
	if ( pUI )
	{
		destroyUI(pUI);
	}
}

void CGameUILayer::destroyUI(GameUI* pUI)
{
	if ( pUI )
	{
		pUI->onDestroy();
		m_UITable.erase(pUI->getIDU());
		pUI->removeFromParentAndCleanup(true);
		pUI->release();
	}
}

void CGameUILayer::destroyUI()
{
	for ( UITable::iterator itr = m_UITable.begin();itr != m_UITable.end(); itr++ )
	{
		GameUI* pUI = itr->second;
		if ( pUI )
		{
			pUI->onDestroy();
			pUI->removeFromParentAndCleanup(true);
			pUI->release();
		}
	}

	m_UITable.clear();
	m_UITogetherTable.clear();
}