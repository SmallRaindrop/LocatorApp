#include "Skill.h"
#include "GameDataManager.h"
#include "CommonDef.h"

CSkill::CSkill() : m_pData(NULL),m_nCDTime(0),m_nTickIndex(0),m_nTickTime(0),m_cdType(CdType_None)
{

}

CSkill::CSkill(int skillid) : m_pData(NULL),m_nCDTime(0),m_nTickIndex(0),m_nTickTime(0)
{
	Reload(skillid);
}

CSkill::~CSkill()
{

}

void CSkill::Reload(int skillid)
{
	m_pData = SkillData.get(skillid);
	if ( !m_pData )
	{
		LOGE("skill [%d] not found!",skillid);
		return ;
	}

	m_nTickTime = m_pData->comboreset;

	// 拆分连击技能
	StringSplitToInt(m_pData->comboskill,";",m_vTickSkills);

	m_nCDTime = 0;
}

SkillCfg* CSkill::GetTickSkill()
{
	if ( m_vTickSkills.empty() )
	{
		return GetData();
	}

	if ( m_nTickTime >= GetData()->comboreset )
	{
		m_nTickIndex = 0;
		m_nTickTime = 0;
		return GetData();
	}

	if ( m_nTickIndex >= (int)m_vTickSkills.size() )
	{
		m_nTickIndex = 0;
		m_nTickTime = 0;
		return GetData();
	}
	
	int skillid = m_vTickSkills[m_nTickIndex++];
	SkillCfg* ret = SkillData.get(skillid);
	if ( !ret )
	{
		LOGE("combon skill [%d] not found!",skillid);
	}

	m_nTickTime = 0;

	return ret;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

SkillManager::SkillManager()
{
}

SkillManager::~SkillManager()
{
}

CSkill* SkillManager::Insert(int skillid)
{
	return Insert(new CSkill(skillid));
}

CSkill* SkillManager::Insert(CSkill* pSkill)
{
	if ( pSkill )
	{
		m_Skills.push_back(pSkill);
	}

	return pSkill;
}

void SkillManager::Remove(int skillid)
{
	for (size_t i = 0; i < m_Skills.size(); ++i )
	{
		CSkill* pSkill = m_Skills[i];
		if ( pSkill && pSkill->GetDataID() == skillid )
		{
			m_Skills.erase(m_Skills.begin()+i);
			delete pSkill;
			return;
		}
	}
}

void SkillManager::Clear()
{
	for (size_t i = 0; i < m_Skills.size(); ++i )
	{
		CSkill* pSkill = m_Skills[i];
		if ( pSkill )
		{
			delete pSkill;
		}
	}

	m_Skills.clear();
	//m_careerSkills.clear();
	//m_guildSkills.clear();
}

CSkill* SkillManager::Get(int skillid)
{
	for (size_t i = 0; i < m_Skills.size(); ++i )
	{
		CSkill* pSkill = m_Skills[i];
		if ( pSkill && pSkill->GetDataID() == skillid )
		{
			return pSkill;
		}
	}

	return NULL;
}

CSkill* SkillManager::IndexBy(int idx)
{
	if ( idx >= 0 && idx < (int)m_Skills.size() )
	{
		return m_Skills[idx];
	}

	return NULL;
}

CSkill* SkillManager::Last()
{
	if ( m_Skills.size() > 0 )
	{
		return m_Skills[m_Skills.size()-1];
	}

	return NULL;
}

CSkill* SkillManager::LastActive()
{
	for ( size_t i = 0; i < m_Skills.size(); ++i )
	{
		CSkill* pSkill = m_Skills[i];
		if ( pSkill && 0 == pSkill->GetData()->passitive )
		{
			return pSkill;
		}
	}

	return NULL;
}

int	SkillManager::Count()
{
	return (int)m_Skills.size();
}

int SkillManager::CountActive()
{
	int num = 0;
	for ( size_t i = 0; i <m_Skills.size(); ++i )
	{
		CSkill* pSkill = m_Skills[i];
		if ( pSkill && 0 == pSkill->GetData()->passitive )
		{
			num++;
		}
	}
	return num;
}

bool SkillManager::IsStudyed(int skillid)
{
	return Get(skillid) != nullptr;
}

int SkillManager::GetSkillLevel(int skillid)
{
	CSkill* pSkill = Get(skillid);
	if ( pSkill )
	{
		return pSkill->GetLevel();
	}

	return 0;
}

void SkillManager::StartCd(int skillId )
{
	CSkill* pSkill = Get(skillId);
	if (pSkill)
	{
		pSkill->SetCDTime(pSkill->GetData()->cdtime);
		pSkill->SetCDType(CSkill::CdType_Skill);
		// 更新公共CD时间
		for (size_t i=0; i<m_Skills.size(); ++i)
		{
			if (m_Skills[i]->GetCDTime() <= pSkill->GetData()->globecooldown)
			{
				m_Skills[i]->SetCDTime(pSkill->GetData()->globecooldown);
				m_Skills[i]->SetCDType(CSkill::CdType_Globe);
			}
			else
			{
				m_Skills[i]->SetCDType(CSkill::CdType_Skill);
			}
		}
	}
}

void SkillManager::UpdateSkill(float dt)
{
	int deltaTime = dt*1000;
	for (size_t i=0; i<m_Skills.size(); ++i)
	{
		CSkill* pSkill = m_Skills[i];
		if ( pSkill )
		{
			pSkill->SetTickTime(deltaTime);

			float cdTime = pSkill->GetCDTime();
			if (cdTime>-100)
			{
				cdTime -= deltaTime;
				pSkill->SetCDTime(cdTime);
			}
		}
	}
}

//
//bool SkillManager::isLvEnough(SkillCfg* pSkillData)
//{
//	if (gHero->GetLevel() >= pSkillData->studylevel)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//bool SkillManager::isPointEnough(SkillCfg* pSkillData)
//{
//	//if (gHero->GetPropertyInt(RoleProperty_SkillPoint) >= pSkillData->skillpoint)
//	//{
//	//	return true;
//	//}
//	//else
//	//{
//	//	return false;
//	//}
//	return true;
//}
//
//bool SkillManager::isMoneyEnough(SkillCfg* pSkillData)
//{
//	if (gHero->GetMoneyBind() + gHero->GetMoney() >= pSkillData->bindmoney)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//bool SkillManager::canUpgrade(SkillCfg* pSkillData)
//{
//	if (isLvEnough(pSkillData) && isPointEnough(pSkillData) && isMoneyEnough(pSkillData) )
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//bool SkillManager::isLvEnoughStudy(SkillCfg* pSkillData)
//{
//	if (gHero->GetLevel() >= pSkillData->studylevel)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//bool SkillManager::isBookEnough(int ownCnt,SkillCfg* pSkillData)
//{
//	//if (ownCnt >= pSkillData->studybooknum)
//	if (ownCnt >= 1)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//bool SkillManager::canStudy(int ownCnt,SkillCfg* pSkillData)
//{
//	if (isLvEnoughStudy(pSkillData) && isBookEnough(ownCnt,pSkillData) )
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//bool SkillManager::isBoolEnoughNew(SkillCfg* pSkillData)
//{
//	if (gGridsManager->findItemByDataID(emGrids_BagZaWu,pSkillData->studybookid))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//void SkillManager::UpdateCareerAndGuildSkills()
//{
//	m_careerSkills.clear();
//	m_guildSkills.clear();
//	for (auto& skill : m_Skills)
//	{
//		if (skill->GetData()->career == -1)
//		{
//			m_guildSkills.push_back(skill);
//		}
//		else
//		{
//			m_careerSkills.push_back(skill);
//		}
//	}
//}

void SkillManager::GetSkillListByFlag(int val,SkillList& lists)
{
	for (auto& skill : m_Skills)
	{
		if (skill->GetData()->career == -1 && val == -1 )
		{
			lists.push_back(skill);
		}
		else if( skill->GetData()->career != -1 && val != -1 )
		{
			lists.push_back(skill);
		}
	}
}