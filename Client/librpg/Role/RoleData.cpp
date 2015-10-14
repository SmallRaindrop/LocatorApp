#include "GameDef.h"
#include "RoleData.h"

// RoleData
RoleData::RoleData() : speed(0),stateFlag(0),career(0),sex(0),level(0),weapon(0),cloth(0),wing(0)
{

}

void RoleData::SetProperty(RoleProperty idx,__int64 val)
{

}

void RoleData::SetProperty(RoleProperty idx,int val)
{
	switch (idx)
	{
	case RoleProperty_speed:speed = val;return;
	case RoleProperty_StateFlag:stateFlag = val;return;
	case RoleProperty_Career:career = val;return;
	case RoleProperty_Sex:sex = val;return;
	case RoleProperty_Level:level = val;return;
	case RoleProperty_Weapon:weapon = val;return;
	case RoleProperty_Cloth:cloth = val;return;
	case RoleProperty_Wing:wing = val;return;
	case RoleProperty_RecoverCount:m_recoverCount = val;return;
	default:
		break;
	}
}

void RoleData::SetProperty(RoleProperty idx,const string& val)
{
	switch (idx)
	{
	case RoleProperty_Name:name = val;return;
	default:
		break;
	}
}

void RoleData::GetProperty(RoleProperty idx,__int64& val)
{

}

void RoleData::GetProperty(RoleProperty idx,int& val)
{
	switch (idx)
	{
	case RoleProperty_speed:val=speed;return;
	case RoleProperty_StateFlag:val=stateFlag;return;
	case RoleProperty_Career:val=career;return;
	case RoleProperty_Sex:val=sex;return;
	case RoleProperty_Level:val=level;return;
	case RoleProperty_Weapon:val=weapon;return;
	case RoleProperty_Cloth:val=cloth;return;
	case RoleProperty_Wing:val=wing;return;
	case RoleProperty_RecoverCount:m_recoverCount = val;return;
	default:
		break;
	}
}

void RoleData::GetProperty(RoleProperty idx,string& val)
{
	switch (idx)
	{
	case RoleProperty_Name:val = name;return;
	default:
		break;
	}
}

// RoleFighterData
RoleFighterData::RoleFighterData() : hp(0),mp(0),camp(0),fightValue(0)
{
	for (int i = 0;i<RoleProperty_Fight_Max;++i )
	{
		fight_array[i] = 0;
	}
}

RoleFighterData::~RoleFighterData()
{

}

void RoleFighterData::SetProperty(RoleProperty idx,__int64 val)
{
	switch (idx)
	{
	case RoleProperty_HP:hp = val;return;
	default:
		break;
	}

	if ( idx > RoleProperty_None && idx < RoleProperty_Fight_Max )
	{
		fight_array[idx] = val;
		return;
	}
	RoleData::SetProperty(idx,val);
}

void RoleFighterData::SetProperty(RoleProperty idx,int val)
{
	switch (idx)
	{
	case RoleProperty_MP:mp = val;return;
	case RoleProperty_Camp:camp = val;return;
	case RoleProperty_FightValue:fightValue = val;return;
	default:
		break;
	}

	if ( idx > RoleProperty_None && idx < RoleProperty_Fight_Max )
	{
		fight_array[idx] = val;
		return ;
	}
	RoleData::SetProperty(idx,val);
}

void RoleFighterData::SetProperty(RoleProperty idx,const string& val)
{
	RoleData::SetProperty(idx,val);
}

void RoleFighterData::GetProperty(RoleProperty idx,__int64& val)
{
	switch (idx)
	{
	case RoleProperty_HP:val = hp;return;
	default:
		break;
	}

	if ( idx > RoleProperty_None && idx < RoleProperty_Fight_Max )
	{
		val = fight_array[idx];
		return ;
	}
	RoleData::GetProperty(idx,val);
}

void RoleFighterData::GetProperty(RoleProperty idx,int& val)
{
	switch (idx)
	{
	case RoleProperty_MP:val = mp;return;
	case RoleProperty_Camp:val = camp;return;
	case RoleProperty_FightValue:val = fightValue;return;
	default:
		break;
	}

	if ( idx > RoleProperty_None && idx < RoleProperty_Fight_Max )
	{
		val = (int)fight_array[idx];
		return ;
	}
	RoleData::GetProperty(idx,val);
}

void RoleFighterData::GetProperty(RoleProperty idx,string& val)
{
	RoleData::GetProperty(idx,val);
}

// MonsterData
void MonsterData::SetProperty(RoleProperty idx,__int64 val)
{
	RoleFighterData::SetProperty(idx,val);
}

void MonsterData::SetProperty(RoleProperty idx,int val)
{
	RoleFighterData::SetProperty(idx,val);
}

void MonsterData::SetProperty(RoleProperty idx,const string& val)
{
	RoleFighterData::SetProperty(idx,val);
}

void MonsterData::GetProperty(RoleProperty idx,__int64& val)
{
	RoleFighterData::GetProperty(idx,val);
}

void MonsterData::GetProperty(RoleProperty idx,int& val)
{
	RoleFighterData::GetProperty(idx,val);
}

void MonsterData::GetProperty(RoleProperty idx,string& val)
{
	RoleFighterData::GetProperty(idx,val);
}

// PetData
void PetData::SetProperty(RoleProperty idx,__int64 val)
{
	RoleFighterData::SetProperty(idx,val);
}

void PetData::SetProperty(RoleProperty idx,int val)
{
	RoleFighterData::SetProperty(idx,val);
}

void PetData::SetProperty(RoleProperty idx,const string& val)
{
	RoleFighterData::SetProperty(idx,val);
}

void PetData::GetProperty(RoleProperty idx,__int64& val)
{
	RoleFighterData::GetProperty(idx,val);
}

void PetData::GetProperty(RoleProperty idx,int& val)
{
	RoleFighterData::GetProperty(idx,val);
}

void PetData::GetProperty(RoleProperty idx,string& val)
{
	RoleFighterData::GetProperty(idx,val);
}

// NPCData
void NpcData::SetProperty(RoleProperty idx,__int64 val)
{
	RoleData::SetProperty(idx,val);
}


void NpcData::SetProperty(RoleProperty idx,int val)
{
	RoleData::SetProperty(idx,val);
}

void NpcData::SetProperty(RoleProperty idx,const string& val)
{
	RoleData::SetProperty(idx,val);
}

void NpcData::GetProperty(RoleProperty idx,__int64& val)
{
	RoleData::GetProperty(idx,val);
}

void NpcData::GetProperty(RoleProperty idx,int& val)
{
	RoleData::GetProperty(idx,val);
}

void NpcData::GetProperty(RoleProperty idx,string& val)
{
	RoleData::GetProperty(idx,val);
}

// PlayerData
void PlayerData::SetProperty(RoleProperty idx,__int64 val)
{
	switch (idx)
	{
	case RoleProperty_GuildID: guildID = val; return;
	default:
		break;
	}
	RoleFighterData::SetProperty(idx,val);
}

void PlayerData::SetProperty(RoleProperty idx,int val)
{
	switch (idx)
	{
	case RoleProperty_VipLevel: vipLevel = val; return;
	case RoleProperty_Achievement: achievement = val; return;
	default:
		break;
	}
	RoleFighterData::SetProperty(idx,val);
}

void PlayerData::SetProperty(RoleProperty idx,const string& val)
{
	RoleFighterData::SetProperty(idx,val);
}

void PlayerData::GetProperty(RoleProperty idx,__int64& val)
{
	switch (idx)
	{
	case RoleProperty_GuildID: val = guildID; return;
	default:
		break;
	}
	RoleFighterData::GetProperty(idx,val);
}

void PlayerData::GetProperty(RoleProperty idx,int& val)
{
	switch (idx)
	{
	case RoleProperty_VipLevel: val = vipLevel; return;
	case RoleProperty_Achievement: val = achievement; return;
	default:
		break;
	}
	RoleFighterData::GetProperty(idx,val);
}

void PlayerData::GetProperty(RoleProperty idx,string& val)
{
	switch (idx)
	{
	case RoleProperty_VipLevel: val = vipLevel; return;
	default:
		break;
	}
	RoleFighterData::GetProperty(idx,val);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void HeroData::SetProperty(RoleProperty idx,__int64 val)
{
	switch (idx)
	{
	case RoleProperty_Exp: exp = val; return;
	case RoleProperty_Coin:  money=val; return;
	case RoleProperty_Coin_b:  money_b=val; return;
	default:
		break;
	}
	PlayerData::SetProperty(idx,val);
}

void HeroData::SetProperty(RoleProperty idx,int val)
{
	switch (idx)
	{
	case RoleProperty_Lucky:  lucky=val; return;
	case RoleProperty_Treasure:  gold=val; return;
	case RoleProperty_Treasure_b:  gold_b=val; return;
	case RoleProperty_Reputation:  reputation=val; return;
	case RoleProperty_ManufactureSize: manufactureSize = val; return;
	default:
		break;
	}
	PlayerData::SetProperty(idx,val);
}

void HeroData::SetProperty(RoleProperty idx,const string& val)
{
	PlayerData::SetProperty(idx,val);
}

void HeroData::GetProperty(RoleProperty idx,__int64& val)
{
	switch (idx)
	{
	case RoleProperty_Exp: val = exp; return;
	case RoleProperty_Coin:  val = money; return;
	case RoleProperty_Coin_b: val = money_b; return;
	default:
		break;
	}
	PlayerData::GetProperty(idx,val);
}

void HeroData::GetProperty(RoleProperty idx,int& val)
{
	switch (idx)
	{
	case RoleProperty_Lucky: val = lucky; return;
	case RoleProperty_Treasure:  val = gold; return;
	case RoleProperty_Treasure_b: val = gold_b; return;
	case RoleProperty_Reputation: val = reputation; return;
	case RoleProperty_ManufactureSize: val = manufactureSize; return;
	default:
		break;
	}
	PlayerData::GetProperty(idx,val);
}

void HeroData::GetProperty(RoleProperty idx,string& val)
{
	PlayerData::GetProperty(idx,val);
}