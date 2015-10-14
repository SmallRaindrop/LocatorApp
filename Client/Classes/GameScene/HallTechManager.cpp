#include "HallTechManager.h"
#include "GameDataManager.h"
#include "CommonDef.h"

HallTech::HallTech(int id,int lv,double nextLvTime) 
	: m_id(id),m_lv(lv),m_nextLvTime(nextLvTime)
{
	Reload(id);
}

HallTech::~HallTech()
{
}

void HallTech::Reload(int hallTechId)
{
	m_pHallTechData = HallTechData.get(hallTechId);
	if ( !m_pHallTechData )
	{
		LOGE(" HallTechData hallTechId [%d] not found!",hallTechId);
		return ;
	}
}

string HallTech::GetHallDes()
{
	if (m_pHallTechData->id == 1)
	{
		switch (m_lv)
		{
		case 1:
			return m_pHallTechData->description1;
			break;
		case 2:
			return m_pHallTechData->description2;
			break;
		case 3:
			return m_pHallTechData->description3;
			break;
		default:
			return "not found";
			break;
		}
	}else
	{
		switch (m_lv)
		{
		case 0:
			return m_pHallTechData->description1;
			break;
		case 1:
			return m_pHallTechData->description2;
			break;
		case 2:
			return m_pHallTechData->description3;
			break;
		default:
			return "not found";
			break;
		}
	}
}


int HallTech::GetUpgradeGold()
{
	vector<int> needGold_vec_;
	StringSplitToInt(m_pHallTechData->gold,";",needGold_vec_);
	if (m_lv>=GetHallMaxLevel()) // 当前等级已经达到最大等级
	{
		return 0;
	}
	return needGold_vec_[m_lv];
}


int HallTech::GetUpgradeItemCountByLevel(int level)
{
	vector<int> needItemCount_vec_;
	StringSplitToInt(m_pHallTechData->item_number,";",needItemCount_vec_);
	if (level>=GetHallMaxLevel()) // 当前等级已经达到最大等级
	{
		return 0;
	}
	return needItemCount_vec_[level];
}


int HallTech::GetUpgradeNeedTimeByLevel(int level)
{
	vector<int> needTime_vec_;
	StringSplitToInt(m_pHallTechData->time,";",needTime_vec_);
	if (level>=GetHallMaxLevel()) // 当前等级已经达到最大等级
	{
		return 0;
	}
	return needTime_vec_[level];
}

void HallTech::onTimer(float dt)
{
	m_nextLvTime = m_nextLvTime - dt;
	if (m_nextLvTime <= 0)
	{
		m_nextLvTime = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
HallTechManager::HallTechManager()
{
}

HallTechManager::~HallTechManager()
{
	Clear();
}

HallTech* HallTechManager::Insert(int id,int lv,double nextLvTime)
{
	HallTech* pHallTech = new HallTech(id,lv,nextLvTime);
	if ( pHallTech )
	{
		Insert(pHallTech);
		return pHallTech;
	}
	else
	{
		LOGE("HallTechManager::Insert new HallTech(%d) failed.",id);
	}

	return NULL;
}

void HallTechManager::Insert(HallTech* pHallTech)
{
	if ( pHallTech )
	{
		m_HallTechs.push_back(pHallTech);
	}
}

void HallTechManager::Clear()
{
	for (size_t i = 0; i < m_HallTechs.size(); ++i)
	{
		HallTech* pHallTech = m_HallTechs[i];
		CC_SAFE_DELETE(pHallTech);
	}

	m_HallTechs.clear();
}

HallTech* HallTechManager::Get(int id)
{
	for (size_t i = 0; i < m_HallTechs.size(); ++i)
	{
		HallTech* pHallTech = m_HallTechs[i];
		if ( pHallTech && pHallTech->GetHallTechID() == id )
		{
			return pHallTech;
		}
	}

	return NULL;
}

HallTech* HallTechManager::GetByCfgID(int cfg_id)
{
	for (size_t i = 0; i < m_HallTechs.size(); ++i)
	{
		HallTech* pHallTech = m_HallTechs[i];
		if ( pHallTech && pHallTech->GetHallTechData()->id == cfg_id )
		{
			return pHallTech;
		}
	}

	return NULL;
}

bool HallTechManager::GetIsUpgrade(int id)
{
	for (size_t i = 0; i < m_HallTechs.size(); ++i)
	{
		HallTech* pHallTech = m_HallTechs[i];
		if ( pHallTech && pHallTech->GetHallTechID() == id )
		{
			if(pHallTech->GetHallTechUpgradeTime()==0)
			{
				return false;
			}else
			{
				return true;
			}
		}
	}
	return false;
}

float HallTechManager::GetUpgradeTime(int id)
{
	for (size_t i = 0; i < m_HallTechs.size(); ++i)
	{
		HallTech* pHallTech = m_HallTechs[i];
		if ( pHallTech && pHallTech->GetHallTechID() == id )
		{
			return pHallTech->GetHallTechUpgradeTime();
		}
	}

	return 0;
}

float HallTechManager::GetUpgradeTimePercent(int id)
{
	for (size_t i = 0; i < m_HallTechs.size(); ++i)
	{
		HallTech* pHallTech = m_HallTechs[i];
		if ( pHallTech && pHallTech->GetHallTechID() == id )
		{
			vector<int> time_vec_; 
			StringSplitToInt(pHallTech->GetHallTechData()->time,";",time_vec_);
			double need_time_;
			if (pHallTech->m_lv >= (int)(time_vec_.size()))
			{
				return 0.0f; // 没有下一级
			}else
			{
				need_time_ = time_vec_[pHallTech->m_lv];
			}
			return (need_time_ - pHallTech->GetHallTechUpgradeTime())/need_time_*100;
		}
	}

	return 0.0f;
}

int HallTechManager::GetLevelByID(int id)
{
	for (size_t i = 0; i < m_HallTechs.size(); ++i)
	{
		HallTech* pHallTech = m_HallTechs[i];
		if ( pHallTech && pHallTech->GetHallTechID() == id )
		{
			return pHallTech->GetHallLevel();
		}
	}

	return 0;
}

int HallTechManager::GetLevelByCfgID(int cfg_id)
{
	for (size_t i = 0; i < m_HallTechs.size(); ++i)
	{
		HallTech* pHallTech = m_HallTechs[i];
		if ( pHallTech && pHallTech->GetHallTechData()->id == cfg_id )
		{
			return pHallTech->GetHallLevel();
		}
	}

	return 0;
}


void HallTechManager::Update(float dt)
{
	for (size_t i = 0;i<m_HallTechs.size();++i)
	{
		m_HallTechs[i]->onTimer(dt);
	}
}