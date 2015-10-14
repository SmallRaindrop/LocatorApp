#include "PetItemManager.h"
#include "GameDataManager.h"
#include "CommonDef.h"

CPetItem::CPetItem(int id,int dataId,int level,int exp,int strengLv,int isActive,
				   pk::FightProperty prop,vector<pk::EquipTianshu> tianShuLis,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index) 
	: m_id(id),m_dataId(dataId),m_level(level),m_exp(exp),m_strengLv(strengLv),m_isActive(isActive),m_content_lv(content_lv),m_tian_shu_use_index(tian_shu_use_index)
{
	m_prop = prop;
	m_tianShuList = tianShuLis;
	m_soltStrengList = soltStrengList;
	Reload(dataId);
}

CPetItem::~CPetItem()
{
}

void CPetItem::Reload(int dataId)
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
PetItemManager::PetItemManager()
{
}

PetItemManager::~PetItemManager()
{
	Clear();
}

CPetItem* PetItemManager::Insert(int id,int dataId,int level,int exp,int strengLv,int isActive,
								pk::FightProperty prop,vector<pk::EquipTianshu> tianShuLis,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index)
{
	CPetItem* pPetData = new CPetItem(id,dataId,level,exp,strengLv,isActive,prop,tianShuLis,content_lv,soltStrengList,tian_shu_use_index);
	if ( pPetData )
	{
		Insert(pPetData);
		return pPetData;
	}
	else
	{
		LOGE("PetItemManager::Insert new PetData(%d) failed.",dataId);
	}

	return NULL;
}

void PetItemManager::Insert(CPetItem* pPetData)
{
	if ( pPetData )
	{
		m_PetItems.push_back(pPetData);
	}
}

void PetItemManager::Clear()
{
	for (size_t i = 0; i < m_PetItems.size(); ++i)
	{
		CPetItem* pPetData = m_PetItems[i];
		CC_SAFE_DELETE(pPetData);
	}

	m_PetItems.clear();
}

CPetItem* PetItemManager::GetByID(int id)
{
	for (size_t i = 0; i < m_PetItems.size(); ++i)
	{
		CPetItem* pPetData = m_PetItems[i];
		if ( pPetData && pPetData->GetPetID() == id )
		{
			return pPetData;
		}
	}

	return NULL;
}

CPetItem* PetItemManager::GetByDataID(int dataid)
{
	for (size_t i = 0; i < m_PetItems.size(); ++i)
	{
		CPetItem* pPetData = m_PetItems[i];
		if ( pPetData && pPetData->GetPetDataID() == dataid )
		{
			return pPetData;
		}
	}

	return NULL;
}
