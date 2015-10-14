#include "GodDeviceManager.h"
#include "GameDataManager.h"
#include "CommonDef.h"
#include "Hero.h"

GodDevice::GodDevice(int godCfgID,int isDress,int refineLevel,int enhanceLevel,int equipId,vector<pk::EquipTianshu> tianShuList,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index) 
	: m_refineLevel(refineLevel),m_enhanceLevel(enhanceLevel),m_equipId(equipId),m_tianShuList(tianShuList),m_content_lv(content_lv),m_soltStrengList(soltStrengList),m_tian_shu_use_index(tian_shu_use_index)
{
	Reload(godCfgID);
	SetIsDress(isDress);
}

GodDevice::~GodDevice()
{
}

void GodDevice::Reload(int godid)
{
	m_pItemData = ItemData.get(godid);
	if ( !m_pItemData )
	{
		LOGE("item table goddevice[%d] not found!",godid);
		return ;
	}

	m_pEquipData = EquipBaseData.get(godid);
	if ( !m_pEquipData )
	{
		LOGE("equipbase table goddevice[%d] not found!",godid);
		return ;
	}

	// 拆分技能列表
	StringSplitToInt(m_pEquipData->skillid,";",m_skillId_vec);

	// 拆分属性列表
	vector<string> temp_str_;
	int number_ = StringSplit(m_pEquipData->attribute,";",temp_str_);

	for (size_t i = 0;i<temp_str_.size();i++)
	{
		vector<int> temp_int_vec_;
		StringSplitToInt(temp_str_[i],",",temp_int_vec_);
		m_all_attr_vec[0].push_back(temp_int_vec_);
	}

	temp_str_.clear();
	number_ = StringSplit(m_pEquipData->attribute1,";",temp_str_);
	for (size_t i = 0;i<temp_str_.size();i++)
	{
		vector<int> temp_int_vec_;
		StringSplitToInt(temp_str_[i],",",temp_int_vec_);
		m_all_attr_vec[1].push_back(temp_int_vec_);
	}

	temp_str_.clear();
	number_ = StringSplit(m_pEquipData->attribute2,";",temp_str_);
	for (size_t i = 0;i<temp_str_.size();i++)
	{
		vector<int> temp_int_vec_;
		StringSplitToInt(temp_str_[i],",",temp_int_vec_);
		m_all_attr_vec[2].push_back(temp_int_vec_);
	}

	temp_str_.clear();
	number_ = StringSplit(m_pEquipData->attribute3,";",temp_str_);
	for (size_t i = 0;i<temp_str_.size();i++)
	{
		vector<int> temp_int_vec_;
		StringSplitToInt(temp_str_[i],",",temp_int_vec_);
		m_all_attr_vec[3].push_back(temp_int_vec_);
	}

	temp_str_.clear();
	number_ = StringSplit(m_pEquipData->attribute4,";",temp_str_);
	for (size_t i = 0;i<temp_str_.size();i++)
	{
		vector<int> temp_int_vec_;
		StringSplitToInt(temp_str_[i],",",temp_int_vec_);
		m_all_attr_vec[4].push_back(temp_int_vec_);
	}

	temp_str_.clear();
	number_ = StringSplit(m_pEquipData->attribute5,";",temp_str_);
	for (size_t i = 0;i<temp_str_.size();i++)
	{
		vector<int> temp_int_vec_;
		StringSplitToInt(temp_str_[i],",",temp_int_vec_);
		m_all_attr_vec[5].push_back(temp_int_vec_);
	}
}

int GodDevice::getArtId(int dataid,int level)
{
	// 如果进阶等级小于5级，取ItemCfg 的art_id字段。
	if ( level >=  GOD_MAX_LEVEL )
	{
		EquipBaseCfg* pGodData = EquipBaseData.get(dataid);
		if ( !pGodData )
		{
			LOGE(" GodDevice::GetGodArtId equipdata[%d] not found.",dataid);
			return 0;
		}
		return pGodData->art_id;
	}
	else
	{
		ItemCfg* pData = ItemData.get(dataid);
		if ( !pData )
		{
			LOGE(" GodDevice::GetGodArtId item[%d] data not found.",dataid);
			return 0;
		}
		return pData->artid;
	}
}

void GodDevice::SetIsDress(int isDress)
{ 
	m_isDress = isDress; 
	if ( isDress )
	{
		gHero->SetCloth(GetGodArtId());
	}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
GodDeviceManager::GodDeviceManager()
{
}

GodDeviceManager::~GodDeviceManager()
{
	Clear();
}

GodDevice* GodDeviceManager::Insert(int godCfgID,int isDress,int refineLevel,int enhanceLevel,int equipId,vector<pk::EquipTianshu> tianShuList,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index)
{
	GodDevice* pGod = new GodDevice(godCfgID,isDress,refineLevel,enhanceLevel,equipId,tianShuList,content_lv,soltStrengList,tian_shu_use_index);
	if ( pGod )
	{
		Insert(pGod);
		return pGod;
	}
	else
	{
		LOGE("RoleBuffManager::Insert new RoleBuff(%lld) failed.",godCfgID);
	}

	return NULL;
}

void GodDeviceManager::Insert(GodDevice* pGod)
{
	if ( pGod )
	{
		m_GodDevices.push_back(pGod);
	}
}

void GodDeviceManager::Clear()
{
	for (size_t i = 0; i < m_GodDevices.size(); ++i)
	{
		GodDevice* pGod = m_GodDevices[i];
		CC_SAFE_DELETE(pGod);
	}

	m_GodDevices.clear();
}

GodDevice* GodDeviceManager::Get(int godCfgID)
{
	for (size_t i = 0; i < m_GodDevices.size(); ++i)
	{
		GodDevice* pGod = m_GodDevices[i];
		if ( pGod && pGod->GetGodDataId() == godCfgID )
		{
			return pGod;
		}
	}

	return NULL;
}

int GodDeviceManager::GetIsDressGod()
{
	for (size_t i = 0; i < m_GodDevices.size(); ++i)
	{
		GodDevice* pGod = m_GodDevices[i];
		if ( pGod && pGod->m_isDress == 1 )
		{
			return pGod->GetGodDataId();
		}
	}

	return NULL;
}

GodDevice* GodDeviceManager::GetIsDressGodPtr()
{
	for (size_t i = 0; i < m_GodDevices.size(); ++i)
	{
		GodDevice* pGod = m_GodDevices[i];
		if ( pGod && pGod->m_isDress == 1 )
		{
			return pGod;
		}
	}

	return NULL;
}

int GodDeviceManager::GetIsDressGodIndex()
{
	for (size_t i = 0; i < m_GodDevices.size(); ++i)
	{
		GodDevice* pGod = m_GodDevices[i];
		if ( pGod && pGod->m_isDress == 1 )
		{
			return i;
		}
	}

	return NULL;
}
