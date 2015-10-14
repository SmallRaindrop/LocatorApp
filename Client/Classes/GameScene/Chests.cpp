#include "Chests.h"
#include "TileMap.h"
#include "UI/GamePrompt.h"
#include "RoleTitle.h"
#include "Hero.h"
#include "../Net/pk_map.h"
#include "../Net/NetDispatcher.h"
#include "BeyondMap.h"
#include "../UI/CustomCtrl/TimerProgressBar.h"
#include "RoleTitleLayer.h"
#include "GameUILayer.h"
#include "UI/OpenLock.h"
#include "UI/OneStroke.h"


CChests::CChests() 
	:m_pCfgData(nullptr)
	,m_pChatText(nullptr)
	,m_openStatus(ChestsStatus_None)
	,m_fDestoryLeftTime()
{
	SetType(mapObjectType_Chests);
}

CChests::~CChests()
{

}

bool CChests::init()
{
	m_pData = new RoleFighterData;
	if ( !m_pData )
	{
		return false;
	}

	if ( !initRole() )
	{
		return false;
	}

	return true;
}

bool CChests::initRole()
{
	if ( !RoleFighter::initRole() )
	{
		return false;
	}
	
	return true;
}

void CChests::update( float delta )
{
	RoleFighter::update(delta);
	if(m_pChatText && m_pChatText->isVisible() )
	{
		//Point pos = getHangingPoint("V_TOP_NODE")+Point(0,100);
		//m_pChatText->setPosition(pos);
	}
	if(m_fDestoryLeftTime>0.0f)
	{
		m_fDestoryLeftTime-=delta;
	}
}

void CChests::onSelect(bool param)
{
	RoleFighter::onSelect(param);
}

void CChests::RefreshEquip()
{
	int armorID = GetPropertyInt(RoleProperty_Cloth);

	equipArmor(armorID);
	equipWeapon(0);
	equipWing(0);
}

void CChests::Dead(RoleFighter* pKiller)
{
	RoleFighter::Dead(pKiller);

	ActionInterval* pAction = DelayTime::create(5.5f);
	runAction(Sequence::create(pAction,CallFunc::create( CC_CALLBACK_0(CChests::Disappear,this)),NULL));
}

void CChests::DeadVirtual(RoleFighter* pKiller)
{
	Dead(pKiller);
}

void CChests::Disappear()
{
	LeaveMap();
}

void CChests::LeaveMap()
{
	MapObject::LeaveMap();

	COpenLock* pOpenLock = (COpenLock*)(gGameUILayer->getActiveUI(IDU_OpenLock));
	if(pOpenLock&&pOpenLock->GetItemBoxId()==GetId())
	{
		gGameUILayer->close(pOpenLock);
	}
	COneStroke* pOneStroke = (COneStroke*)(gGameUILayer->getActiveUI(IDU_OneStrokeUI));
	if(pOneStroke&&pOneStroke->GetItemBoxId()==GetId())
	{
		gGameUILayer->close(pOneStroke);
	}
}

void CChests::ShowMonsterChat(int strId,int displayMs)
{
	if(m_pChatText == NULL )
	{
		m_pChatText = ui::Text::create();
		if ( m_pChatText )
		{
			addChild(m_pChatText);
		}
	}
	if ( m_pChatText )
	{
		m_pChatText->setVisible(true);
		m_pChatText->setFontSize(Font_Size_Prompt);
		m_pChatText->setColor(Color3B::WHITE);
		m_pChatText->setText(GameString.get(strId)->value);
		ActionInterval* pAction = DelayTime::create(displayMs/1000.0f);
		runAction(Sequence::create(pAction,CallFunc::create( CC_CALLBACK_0(CChests::removeMonsterChat,this)),NULL));
	}
}

void CChests::removeMonsterChat()
{
	m_pChatText->stopAllActions();
	m_pChatText->setVisible(false);
}

void CChests::SetDataID(int dataid)
{
	m_pCfgData = ChestsData.get(dataid);
	if ( m_pCfgData )
	{
		changeDir(__Dir(rand() % 8));
		SetProperty(RoleProperty_Cloth,m_pCfgData->art_id);
	}

	if ( m_pRoleTitle )
	{
		m_pRoleTitle->GetName()->setVisible(false);
		m_pRoleTitle->GetHPBar()->setVisible(false);
		m_pRoleTitle->SetLock();
	}
}

void CChests::SetChestsStatus(ChestsStatus status)
{
	m_openStatus = status;
	if (m_pRoleTitle&&m_pRoleTitle->GetLock())
	{
		m_pRoleTitle->GetLock()->setEnabled(status != ChestsStatus_Opening);
	}
}

void CChests::SetDestroyLeftTime(float fLeftTime)
{ 
	m_fDestoryLeftTime = fLeftTime;
	COneStroke*	pOneStroke = (COneStroke*)gGameUILayer->getActiveUI(IDU_OneStrokeUI);
	if(pOneStroke&&pOneStroke->GetItemBoxId()==GetId())
	{
		pOneStroke->SetLeftTime(m_fDestoryLeftTime);
	}
	COpenLock*	pOpenLockKey = (COpenLock*)gGameUILayer->getActiveUI(IDU_OpenLock);
	if(pOpenLockKey&&pOpenLockKey->GetItemBoxId()==GetId())
	{
		pOpenLockKey->SetLeftTime(m_fDestoryLeftTime);
	}
}