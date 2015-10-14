#include "RoleBuff.h"
#include "GameDataManager.h"

RoleBuff::RoleBuff(__int64 id,int buffid,int duration) : m_id(id),m_nDuration(duration)
{
	Reload(buffid);
}

RoleBuff::~RoleBuff()
{
	Clear();
}

void RoleBuff::Reload(int buffid)
{
	Clear();

	m_pData = BuffData.get(buffid);
	if ( !m_pData )
	{
		LOGE("buffid [%d] not found!",buffid);
		return;
	}

	if ( !m_pData->art.empty() )
	{
		Effect::GetEffectListByConfig(m_pData->art,m_effectList);
		for( size_t i = 0;i<m_effectList.size();++i )
		{
			CC_SAFE_RETAIN(m_effectList[i]);
		}
	}
}

void RoleBuff::Clear()
{
	for( size_t i = 0;i<m_effectList.size();++i )
	{
		CC_SAFE_RELEASE(m_effectList[i]);
	}
	m_effectList.clear();

	m_pData = NULL;
	m_id = 0;
	m_nDuration = 0;
}

RoleBuffManager::RoleBuffManager()
{
}

RoleBuffManager::~RoleBuffManager()
{
	Clear();
}

void RoleBuffManager::Insert(RoleBuff* pBuff)
{
	if ( pBuff )
	{
		m_Buffs.push_back(pBuff);
	}
}

void RoleBuffManager::Clear()
{
	for (size_t i = 0; i < m_Buffs.size(); ++i)
	{
		RoleBuff* pBuff = m_Buffs[i];
		CC_SAFE_DELETE(pBuff);
	}

	m_Buffs.clear();
}

void RoleBuffManager::Remove(int64 buffid)
{
	for (size_t i = 0; i < m_Buffs.size(); ++i)
	{
		RoleBuff* pBuff = m_Buffs[i];
		if ( pBuff && pBuff->GetBuffIdentity() == buffid )
		{
			CC_SAFE_DELETE(pBuff);
			m_Buffs.erase(m_Buffs.begin()+i);
			return;
		}
	}
}

RoleBuff* RoleBuffManager::Get(int64 buffid)
{
	for (size_t i = 0; i < m_Buffs.size(); ++i)
	{
		RoleBuff* pBuff = m_Buffs[i];
		if ( pBuff && pBuff->GetBuffIdentity() == buffid )
		{
			return pBuff;
		}
	}

	return NULL;
}