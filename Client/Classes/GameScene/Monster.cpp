#include "Monster.h"
#include "TileMap.h"
#include "UI/GamePrompt.h"
#include "RoleTitle.h"
#include "Hero.h"
#include "../Net/pk_map.h"
#include "../Net/NetDispatcher.h"
#include "BeyondMap.h"
#include "../UI/CustomCtrl/TimerProgressBar.h"
#include "RoleTitleLayer.h"

CMonster::CMonster() 
	:m_pCfgData(nullptr)
	,m_pChatText(nullptr)
	,m_pCollectionProgressBar(nullptr)
{
	SetType(mapObjectType_Monster);
}

CMonster::~CMonster()
{
	if (m_pCollectionProgressBar)
		m_pCollectionProgressBar->removeFromParent();
}

bool CMonster::init()
{
	m_pData = new MonsterData;
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

bool CMonster::initRole()
{
	if ( !RoleFighter::initRole() )
	{
		return false;
	}
	
	return true;
}

void CMonster::SetProperty(RoleProperty idx,int val)
{
	RoleFighter::SetProperty(idx,val);
}

void CMonster::SetProperty(RoleProperty idx,__int64 val)
{
	RoleFighter::SetProperty(idx,val);
}

void CMonster::SetProperty(RoleProperty idx,const string& val)
{
	RoleFighter::SetProperty(idx,val);
}

void CMonster::update( float delta )
{
	RoleFighter::update(delta);
	if(m_pChatText && m_pChatText->isVisible() )
	{
		//Point pos = getHangingPoint("V_TOP_NODE")+Point(0,100);
		//m_pChatText->setPosition(pos);
	}
}

void CMonster::onSelect(bool param)
{
	RoleFighter::onSelect(param);
}

void CMonster::RefreshEquip()
{
	int armorID = GetPropertyInt(RoleProperty_Cloth);

	equipArmor(armorID);
	equipWeapon(0);
	equipWing(0);
}

void CMonster::Dead(RoleFighter* pKiller)
{
	RoleFighter::Dead(pKiller);

	//怪物死亡后，需不显示名字，仅短时间显示死亡动作即可
	if(m_pRoleTitle)
	{
		m_pRoleTitle->GetName()->setVisible(false);
		m_pRoleTitle->GetHPBar()->setVisible(false);
	}

	if ( pKiller )
	{
		ShowHitFly(pKiller->getPosition());
	}

	ActionInterval* pAction = DelayTime::create(5.5f);
	runAction(Sequence::create(pAction,CallFunc::create( CC_CALLBACK_0(CMonster::Disappear,this)),NULL));
}

void CMonster::DeadVirtual(RoleFighter* pKiller)
{
	Dead(pKiller);
}

void CMonster::Disappear()
{
	//// --------------怪物模拟五子棋--------------
	//if (m_pCfgData->id == Monster_Chess5_id1 || m_pCfgData->id == Monster_Chess5_id2 || m_pCfgData->id == Monster_Chess5_id3)
	//	//AttachEffect(1701002,"V_BOTTOM_NODE");

	//if (m_pCfgData->id == 9080 )
	//	//AttachEffect(1013001,"V_BOTTOM_NODE");

	MapObject::LeaveMap();
}

void CMonster::ShowMonsterChat(int strId,int displayMs)
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
		runAction(Sequence::create(pAction,CallFunc::create( CC_CALLBACK_0(CMonster::removeMonsterChat,this)),NULL));
	}
}

void CMonster::removeMonsterChat()
{
	m_pChatText->stopAllActions();
	m_pChatText->setVisible(false);
}

void CMonster::SetDataID(int dataid)
{
	m_pCfgData = MonsterBaseData.get(dataid);
	if ( m_pCfgData )
	{
		SetRoleName(m_pCfgData->name);
		SetLevel(m_pCfgData->level);
		// 设置外观
		SetProperty(RoleProperty_Cloth,m_pCfgData->art_id);
		SetBoundingInfo(m_pCfgData->body_size,m_pCfgData->body_size,m_pCfgData->height);
		if ( m_pCfgData->scale != 0 )
		{
			setScale((float)m_pCfgData->scale/100.f);
		}
		SetSkinEffect(m_pCfgData->skin);

		changeDir(__Dir(rand() % 8));
	}

	if ( m_pRoleTitle )
	{
		m_pRoleTitle->SetRoleTitle(m_pCfgData->title);
		m_pRoleTitle->SetNameColor(CampColor_Monster);
		m_pRoleTitle->SetHPBarPos(0,20);
		m_pRoleTitle->SetNamePos(0.0f,20.0f);
		m_pRoleTitle->SetTitlePos(0.0f,24.0f);
		m_pRoleTitle->GetName()->setVisible(false);
	}
}

void CMonster::CollectStart()
{
	if (m_pCollectionProgressBar == NULL)
	{
		m_pCollectionProgressBar = TimerProgressBar::create();
		if (m_pCollectionProgressBar == NULL)
			return;

		m_pCollectionProgressBar->loadTexture("assets/ui/mainui/collection_Bar.png");
		m_pCollectionProgressBar->SetBGImg("Image_CollectionBar_BG");
	}
	m_pCollectionProgressBar->InitWithTarget(this, this, (SEL_SCHEDULE)&CMonster::CollectTimeOut, 3.f);
	if (m_pCollectionProgressBar->getParent() == NULL)
	{
		m_pCollectionProgressBar->setScale(0.6f);
		gRoleTitleLayer->addChild(m_pCollectionProgressBar);
	}
	m_pCollectionProgressBar->SetRunning(true);
	gCocosAudio->PlayEffect(116);
}

void CMonster::CollectTimeOut(float fNoUse)
{
	m_pCollectionProgressBar->SetRunning(false);
	pk::C2GS_OpenDoor_Req cmd;
	cmd.id = GetId();
	cmd.Send(gNetSocket);
}
