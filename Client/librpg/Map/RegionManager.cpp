#include "RegionManager.h"

#ifndef GL_QUADS
#define GL_QUADS 0x0007
#endif // !GL_QUADS

CRegionManager::CRegionManager()
{

}

CRegionManager::~CRegionManager()
{
	for ( size_t i = 0;i<m_Npcs.size();++i )
	{
		CRegion* pRegion = m_Npcs[i];
		if ( pRegion )
		{
			delete pRegion;
		}
	}

	for ( size_t i = 0;i<m_Monsters.size();++i )
	{
		CRegion* pRegion = m_Monsters[i];
		if ( pRegion )
		{
			delete pRegion;
		}
	}

	for ( size_t i = 0;i<m_Doors.size();++i )
	{
		CRegion* pRegion = m_Doors[i];
		if ( pRegion )
		{
			delete pRegion;
		}
	}

	for ( size_t i = 0;i<m_Regions.size();++i )
	{
		CRegion* pRegion = m_Regions[i];
		if ( pRegion )
		{
			delete pRegion;
		}
	}

	m_Npcs.clear();
	m_Monsters.clear();
	m_Doors.clear();
	m_Regions.clear();
}

void CRegionManager::addRegion(CRegion* pRegion)
{
	if ( pRegion )
	{
		m_Regions.push_back(pRegion);
	}
}

void CRegionManager::addNpcRegion(CRegion* pRegion)
{
	if ( pRegion )
	{
		m_Npcs.push_back(pRegion);
	}
}

void CRegionManager::addMonsterRegion(CRegion* pRegion)
{
	if ( pRegion )
	{
		m_Monsters.push_back(pRegion);
	}
}

void CRegionManager::addDoorRegion(CRegion* pRegion)
{
	if ( pRegion )
	{
		m_Doors.push_back(pRegion);
	}
}

CRegion* CRegionManager::addRegion(int cx,int cy,int sx,int sy)
{
	CRegion* pRegion = new CRegion(cx,cy,sx,sy);
	if ( pRegion )
	{
		pRegion->addProperty("region_type",0);
		pRegion->addProperty("region_flag",0);
		addRegion(pRegion);
		return pRegion;
	}
	return NULL;
}


CRegion* CRegionManager::addNpcRegion(int cx,int cy,int sx,int sy)
{
	CRegion* pRegion = new CRegion(cx,cy,sx,sy);
	if ( pRegion )
	{
		pRegion->addProperty("region_type",1);
		pRegion->addProperty("npc_type_id",0);
		addNpcRegion(pRegion);
		return pRegion;
	}
	return NULL;
}

CRegion* CRegionManager::addMonsterRegion(int cx,int cy,int sx,int sy)
{
	CRegion* pRegion = new CRegion(cx,cy,sx,sy);
	if ( pRegion )
	{
		pRegion->addProperty("region_type",2);
		pRegion->addProperty("monster_type_id",0);
		pRegion->addProperty("count_min",0);
		pRegion->addProperty("count_max",0);
		pRegion->addProperty("refresh_mode",0);
		pRegion->addProperty("interval",0);
		pRegion->addProperty("z_active",0);
		pRegion->addProperty("z_find_path_type",0);
		pRegion->addProperty("z_follow_radius",0);
		pRegion->addProperty("z_patrol_radius",0);
		pRegion->addProperty("z_watch_radius",0);
		addMonsterRegion(pRegion);
		return pRegion;
	}
	return NULL;
}

CRegion* CRegionManager::addDoorRegion(int cx,int cy,int sx,int sy)
{
	CRegion* pRegion = new CRegion(cx,cy,sx,sy);
	if ( pRegion )
	{
		pRegion->addProperty("region_type",3);
		pRegion->addProperty("to_map_id",0);
		pRegion->addProperty("to_map_cx",0);
		pRegion->addProperty("to_map_cy",0);
		addDoorRegion(pRegion);
		return pRegion;
	}
	return NULL;
}

void CRegionManager::removeRegion(CRegion* pRegion)
{
	for (  RegionList::iterator itr = m_Npcs.begin();itr != m_Npcs.end(); )
	{
		CRegion* pRegionPtr = *itr;
		if ( pRegionPtr == pRegion )
		{
			delete pRegion;
			itr = m_Npcs.erase(itr);
			return ;
		}
		else
		{
			++itr;
		}
	}
	for (  RegionList::iterator itr = m_Monsters.begin();itr != m_Monsters.end(); )
	{
		CRegion* pRegionPtr = *itr;
		if ( pRegionPtr == pRegion )
		{
			delete pRegion;
			itr = m_Monsters.erase(itr);
			return ;
		}
		else
		{
			++itr;
		}
	}
	for (  RegionList::iterator itr = m_Doors.begin();itr != m_Doors.end(); )
	{
		CRegion* pRegionPtr = *itr;
		if ( pRegionPtr == pRegion )
		{
			delete pRegion;
			itr = m_Doors.erase(itr);
			return ;
		}
		else
		{
			++itr;
		}
	}
	for (  RegionList::iterator itr = m_Regions.begin();itr != m_Regions.end(); )
	{
		CRegion* pRegionPtr = *itr;
		if ( pRegionPtr == pRegion )
		{
			delete pRegion;
			itr = m_Regions.erase(itr);
			return ;
		}
		else
		{
			++itr;
		}
	}
}

CRegion* CRegionManager::getRegion(int cx,int cy)
{
	for (  RegionList::iterator itr = m_Npcs.begin();itr != m_Npcs.end();++itr )
	{
		CRegion* pRegion = *itr;
		if ( pRegion && pRegion->containsCell(cx,cy ) )
		{
			return pRegion;
		}
	}
	for (  RegionList::iterator itr = m_Monsters.begin();itr != m_Monsters.end();++itr )
	{
		CRegion* pRegion = *itr;
		if ( pRegion && pRegion->containsCell(cx,cy ) )
		{
			return pRegion;
		}
	}
	for (  RegionList::iterator itr = m_Doors.begin();itr != m_Doors.end();++itr )
	{
		CRegion* pRegion = *itr;
		if ( pRegion && pRegion->containsCell(cx,cy ) )
		{
			return pRegion;
		}
	}
	for (  RegionList::iterator itr = m_Regions.begin();itr != m_Regions.end();++itr )
	{
		CRegion* pRegion = *itr;
		if ( pRegion && pRegion->containsCell(cx,cy ) )
		{
			return pRegion;
		}
	}

	return NULL;
}

int	CRegionManager::getRegionList(int cx,int cy,RegionList& list)
{
	list.clear();
	for ( size_t i = 0;i<m_Regions.size();++i )
	{
		CRegion* pRegion = m_Regions[i];
		if ( pRegion && pRegion->containsCell(cx,cy ) )
		{
			list.push_back(pRegion);
		}
	}

	return list.size();
}

CRegion* CRegionManager::getRegionFlag(int cx,int cy,int flag)
{
	for ( size_t i = 0;i<m_Regions.size();++i )
	{
		CRegion* pRegion = m_Regions[i];
		if ( pRegion && pRegion->containsCell(cx,cy ) && pRegion->getProperty("region_flag") == flag )
		{
			return pRegion;
		}
	}

	return NULL;
}

CRegion* CRegionManager::getRegionNpc(int cx,int cy)
{
	for ( size_t i = 0;i<m_Npcs.size();++i )
	{
		CRegion* pRegion = m_Npcs[i];
		if ( pRegion && pRegion->containsCell(cx,cy ) )
		{
			return pRegion;
		}
	}

	return NULL;
}

CRegion* CRegionManager::getRegionMonster(int cx,int cy)
{
	for ( size_t i = 0;i<m_Monsters.size();++i )
	{
		CRegion* pRegion = m_Monsters[i];
		if ( pRegion && pRegion->containsCell(cx,cy ) )
		{
			return pRegion;
		}
	}

	return NULL;
}

CRegion* CRegionManager::getRegionDoor(int cx,int cy)
{
	for ( size_t i = 0;i<m_Doors.size();++i )
	{
		CRegion* pRegion = m_Doors[i];
		if ( pRegion && pRegion->containsCell(cx,cy ) )
		{
			return pRegion;
		}
	}

	return NULL;
}

bool CRegionManager::isRegionFlag(int cx,int cy,int flag)
{
	for ( size_t i = 0;i<m_Regions.size();++i )
	{
		CRegion* pRegion = m_Regions[i];
		if ( pRegion && pRegion->containsCell(cx,cy ) && pRegion->getProperty("region_flag") == flag )
		{
			return true;
		}
	}

	return false;
}

bool CRegionManager::isRegionDoor(int cx,int cy)
{
	for ( size_t i = 0;i<m_Doors.size();++i )
	{
		CRegion* pRegion = m_Doors[i];
		if ( pRegion && pRegion->containsCell(cx,cy ) )
		{
			return true;
		}
	}

	return false;
}

bool CRegionManager::addDynamicTransferDoorIfNotExist(int64 id,int16 x,int16 y,int8 cx,int8 cy)
{
	// check whether exist
	int32 door_id_low = (int32)id;
	int32 door_id_high = id >> 32;
	bool is_find = false;
	for ( size_t i = 0;i<m_Doors.size();++i )
	{
		CRegion* pRegion = m_Doors[i];
		if ( pRegion )
		{
			int low_tmp = pRegion->getProperty("door_id_low");
			int high_tmp = pRegion->getProperty("door_id_high");

			if(door_id_low == low_tmp && door_id_high == high_tmp)
			{
				is_find = true;
				break;
			}
		}
	}

	if(!is_find)
	{
		CRegion* pRegion = new CRegion( x, y, cx, cy);
		if(pRegion)
		{
			pRegion->addProperty("door_id_high",door_id_high);
			pRegion->addProperty("door_id_low",door_id_low);
			m_Doors.push_back(pRegion);
			//m_Doors[size] = pRegion;
		}
	}
	return is_find;
}