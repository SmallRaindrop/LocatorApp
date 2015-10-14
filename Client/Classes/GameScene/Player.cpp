#include "Player.h"
#include "TileMap.h"
#include "GameDataManager.h"
#include "Common/CommonDef.h"
#include "PKMode.h"
#include "RoleTitle.h"
#include "BeginnerGuide.h"
#include "Hero.h"

CPlayer::CPlayer()
{
	SetType(mapObjectType_Player);
}

CPlayer::~CPlayer()
{
	
}

bool CPlayer::init()
{
	m_pData = new PlayerData;
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

bool CPlayer::initRole()
{
	if ( !RoleFighter::initRole() )
	{
		return false;
	}
	
	SetCamp(RoleCamp_Player);

	return true;
}

void CPlayer::update(float dt)
{
	RoleFighter::update(dt);
}

void CPlayer::onSelect(bool param)
{
	RoleFighter::onSelect(param);
}

void CPlayer::SetProperty(RoleProperty idx,int val)
{
	switch (idx)
	{
	case RoleProperty_VipLevel:
		SetVipLevel(val);
		return;
	case RoleProperty_Cloth:
		{
			// 拆分ID和神器等级
			int dataid = val % 10000;
			int level = val / 10000;
			int artid = GodDevice::getArtId(dataid,level);
			SetCloth(artid);
		}
		return ;
	case RoleProperty_Weapon:
		{
			ItemCfg* pItemData = ItemData.get(val);
			if ( pItemData )
			{
				SetWeapon(pItemData->artid);
			}
			else
			{
				SetWeapon(0);
			}
		}
		return ;
	case RoleProperty_Wing:
		{
			ItemCfg* pItemData = ItemData.get(val);
			if ( pItemData )
			{
				SetWing(pItemData->artid);
			}
			else
			{
				SetWing(0);
			}
		}
		return ;
	default:
		break;
	}
	RoleFighter::SetProperty(idx,val);
}

void CPlayer::SetProperty(RoleProperty idx,__int64 val)
{
	switch (idx)
	{
	case RoleProperty_GuildID:
		SetVipLevel(val);
		break;
	default:
		break;
	}
	RoleFighter::SetProperty(idx,val);
}

void CPlayer::SetProperty(RoleProperty idx,const string& val)
{
	RoleFighter::SetProperty(idx,val);
}

void CPlayer::SetCloth(int val)
{
	RoleFighter::SetCloth(val);
	SetWeapon(0);
}

void CPlayer::SetWeapon(int val)
{
	val = 0;
	RoleFighter::SetWeapon(val);
}

void CPlayer::SetWing(int val)
{
	RoleFighter::SetWing(val);
}

void CPlayer::SetVipLevel(int val)
{
	GetData()->SetProperty(RoleProperty_VipLevel,val);
}

void CPlayer::SetGuildID(__int64 val)
{
	SetProperty(RoleProperty_GuildID,val);
}

void CPlayer::RefreshEquip()
{
	RoleFighter::RefreshEquip();
}

void CPlayer::RefreshRoleTitle()
{
	RoleFighter::RefreshRoleTitle();

	if ( m_pRoleTitle )
	{
		if ( GetHPMax() > 0 )
		{
			m_pRoleTitle->SetHPPercent(((float)GetHP()) / GetHPMax() * 100);
		}
		
		m_pRoleTitle->SetVip(GetVipLevel() > 0);
		m_pRoleTitle->SetTeamLeader(HasStateFlag(RoleStateFlag_TeamLeader));
		m_pRoleTitle->UpdateRoleNameCampColor();
		m_pRoleTitle->SetRoleTitle("");

		/*if (GetPropertyInt(RoleProperty_Camp))
		{
		m_pRoleTitle->SetNameColor(GetPropertyInt(RoleProperty_Camp) == gHero->GetPropertyInt(RoleProperty_Camp) ? Color3B::BLUE : Color3B::RED);
		}*/

		string strTitle;
		if ( GetPropertyInt(RoleProperty_Achievement) > 0 )
		{
			strTitle = AchievementData.get(GetPropertyInt(RoleProperty_Achievement))->name;
		}

		if (strTitle.length())
		{
			m_pRoleTitle->SetRoleTitle(strTitle);
			m_pRoleTitle->SetNamePos(0, 20);
			m_pRoleTitle->SetTitlePos(0, 24);
		}
		else
		{
			m_pRoleTitle->SetNamePos(0, 20);
		}
	}
}
