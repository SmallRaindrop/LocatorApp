#include "Pet.h"
#include "TileMap.h"
#include "UI/GamePrompt.h"
#include "RoleTitle.h"
#include "Hero.h"
#include "../Net/pk_map.h"
#include "../Net/NetDispatcher.h"
#include "RoleTitleLayer.h"

CPet::CPet() 
	:m_pCfgData(nullptr)
	,m_pChatText(nullptr)
{
	SetType(mapObjectType_Pet);
}

CPet::~CPet()
{

}

bool CPet::init()
{
	m_pData = new PetData;
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

bool CPet::initRole()
{
	if ( !RoleFighter::initRole() )
	{
		return false;
	}
	
	return true;
}

void CPet::SetProperty(RoleProperty idx,int val)
{
	RoleFighter::SetProperty(idx,val);
}

void CPet::SetProperty(RoleProperty idx,__int64 val)
{
	RoleFighter::SetProperty(idx,val);
}

void CPet::SetProperty(RoleProperty idx,const string& val)
{
	RoleFighter::SetProperty(idx,val);
}

void CPet::update( float delta )
{
	RoleFighter::update(delta);
	if(m_pChatText && m_pChatText->isVisible() )
	{
		//Point pos = getHangingPoint("V_TOP_NODE")+Point(0,100);
		//m_pChatText->setPosition(pos);
	}
}

void CPet::onSelect(bool param)
{
	RoleFighter::onSelect(param);
}

void CPet::RefreshEquip()
{
	int armorID = GetPropertyInt(RoleProperty_Cloth);

	equipArmor(armorID);
	equipWeapon(0);
	equipWing(0);
}

void CPet::Dead(RoleFighter* pKiller)
{
	RoleFighter::Dead(pKiller);

	//怪物死亡后，需不显示名字，仅短时间显示死亡动作即可
	if(m_pRoleTitle)
	{
		m_pRoleTitle->GetName()->setVisible(false);
		//m_pRoleTitle->GetHPBar()->setVisible(false);
	}

	ShowHitFly(pKiller->getPosition());

	ActionInterval* pAction = DelayTime::create(5.5f);
	runAction(Sequence::create(pAction,CallFunc::create( CC_CALLBACK_0(CPet::Disappear,this)),NULL));
}

void CPet::DeadVirtual(RoleFighter* pKiller)
{
	Dead(pKiller);
}

void CPet::Disappear()
{
	//// --------------怪物模拟五子棋--------------
	//if (m_pCfgData->id == Monster_Chess5_id1 || m_pCfgData->id == Monster_Chess5_id2 || m_pCfgData->id == Monster_Chess5_id3)
	//	//AttachEffect(1701002,"V_BOTTOM_NODE");

	//if (m_pCfgData->id == 9080 )
	//	//AttachEffect(1013001,"V_BOTTOM_NODE");

	MapObject::LeaveMap();
}

void CPet::ShowPetChat(int strId,int displayMs)
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
		runAction(Sequence::create(pAction,CallFunc::create( CC_CALLBACK_0(CPet::removePetChat,this)),NULL));
	}
}

void CPet::removePetChat()
{
	m_pChatText->stopAllActions();
	m_pChatText->setVisible(false);
}

void CPet::SetDataID(int dataid)
{
	m_pCfgData = PetBaseData.get(dataid);
	if ( m_pCfgData )
	{
		SetRoleName(m_pCfgData->name);
		SetLevel( this->GetLevel() );
		SetProperty(RoleProperty_Cloth,m_pCfgData->art_id);

		changeDir(__Dir(rand() % 8));
	}

	if ( m_pRoleTitle )
	{
		//m_pRoleTitle->SetRoleTitle(m_pCfgData->title);
		m_pRoleTitle->SetNameColor(Color3B::WHITE);
		m_pRoleTitle->SetHPBarPos(0,20);
		m_pRoleTitle->SetNamePos(0.0f,20.0f);
		m_pRoleTitle->SetTitlePos(0.0f,24.0f);
		m_pRoleTitle->GetName()->setVisible(false);
	}
}