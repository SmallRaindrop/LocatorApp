#include "PetDataManager.h"
#include "GameDataManager.h"
#include "CommonDef.h"

PetData::PetData(int id,int dataId,int level,int exp,int strengLv,int isActive,
				   pk::FightProperty prop,vector<pk::EquipTianshu> tianShuLis,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index) 
	: m_id(id),m_dataId(dataId),m_level(level),m_exp(exp),m_strengLv(strengLv),m_isActive(isActive),m_content_lv(content_lv),m_tian_shu_use_index(tian_shu_use_index)
{
	m_prop = prop;
	m_tianShuList = tianShuLis;
	m_soltStrengList = soltStrengList;
	Reload(dataId);
}

PetData::~PetData()
{
}

void PetData::Reload(int dataId)
{
	m_pPetBaseData = PetBaseData.get(dataId);
	if ( !m_pPetBaseData )
	{
		LOGE(" PetBaseData dataId [%d] not found!",dataId);
		return ;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
PetDataManager::PetDataManager()
{
}

PetDataManager::~PetDataManager()
{
	Clear();
}

PetData* PetDataManager::Insert(int id,int dataId,int level,int exp,int strengLv,int isActive,
								pk::FightProperty prop,vector<pk::EquipTianshu> tianShuLis,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index)
{
	PetData* pPetData = new PetData(id,dataId,level,exp,strengLv,isActive,prop,tianShuLis,content_lv,soltStrengList,tian_shu_use_index);
	if ( pPetData )
	{
		Insert(pPetData);
		return pPetData;
	}
	else
	{
		LOGE("PetDataManager::Insert new PetData(%d) failed.",dataId);
	}

	return NULL;
}

void PetDataManager::Insert(PetData* pPetData)
{
	if ( pPetData )
	{
		m_PetDatas.push_back(pPetData);
	}
}

void PetDataManager::Clear()
{
	for (size_t i = 0; i < m_PetDatas.size(); ++i)
	{
		PetData* pPetData = m_PetDatas[i];
		CC_SAFE_DELETE(pPetData);
	}

	m_PetDatas.clear();
}

PetData* PetDataManager::GetByID(int id)
{
	for (size_t i = 0; i < m_PetDatas.size(); ++i)
	{
		PetData* pPetData = m_PetDatas[i];
		if ( pPetData && pPetData->GetPetID() == id )
		{
			return pPetData;
		}
	}

	return NULL;
}

PetData* PetDataManager::GetByDataID(int dataid)
{
	for (size_t i = 0; i < m_PetDatas.size(); ++i)
	{
		PetData* pPetData = m_PetDatas[i];
		if ( pPetData && pPetData->GetPetDataID() == dataid )
		{
			return pPetData;
		}
	}

	return NULL;
}
