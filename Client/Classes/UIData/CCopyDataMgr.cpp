#include "CCopyDataMgr.h"
#include "UI/UIWorldMap.h"

CCopyDataMgr::CCopyDataMgr()
{
	Init();
}

CCopyDataMgr::~CCopyDataMgr()
{
	Clear();
}

void CCopyDataMgr::Init()
{
	m_copyMapUIOpened = nullptr;
	CGameCopysItr gameCopyItr(m_gameCopys,m_worldPlaces);
	WorldmapTableData.foreach(gameCopyItr);
}

void CCopyDataMgr::Clear()
{
	m_gameCopys.clear();
	m_worldPlaces.clear();
	m_copyMapUIOpened = nullptr;
}

bool CCopyDataMgr::IsWorldPlaceUnLock(int nWorldPlaceId)
{
	for (size_t i=0; i<m_worldPlaces.size(); ++i)
	{
		if (m_worldPlaces[i].worldMapId == nWorldPlaceId)
		{
			return m_worldPlaces[i].unLock;
		}
	}
	return false;
}


vector<GameCopy*> CCopyDataMgr::GetLocaleList(int nWorldMapId)
{
	vector<GameCopy*> localeList;
	for (unsigned int i=0; i<m_gameCopys.size(); ++i)
	{
		if (m_gameCopys[i].worldMapId == nWorldMapId && m_gameCopys[i].baseCopy)
		{
			localeList.push_back(&m_gameCopys[i]);
		}
	}
	return localeList;
}

vector<GameCopy*> CCopyDataMgr::GetMapList(int nLocaleId)
{
	vector<GameCopy*> mapList;
	for (unsigned int i=0; i<m_gameCopys.size(); ++i)
	{
		if (m_gameCopys[i].localeId == nLocaleId)
		{
			mapList.push_back(&m_gameCopys[i]);
		}
	}
	return mapList;
}

bool CCopyDataMgr::IsSpecialTaskExist(vector<GameCopy*>& gameCopys,GameMapTaskType type)
{
	for (size_t i=0; i<gameCopys.size(); ++i)
	{
		if (type == gameCopys[i]->TaskType)
		{
			return true;
		}
	}
	return false;
}

vector<GameCopy*> CCopyDataMgr::GetMapListAndBaseGameCopy(int nLocaleId,GameCopy* &pBaseGameCopy)
{
	vector<GameCopy*> mapList;
	for (unsigned int i=0; i<m_gameCopys.size(); ++i)
	{
		if (m_gameCopys[i].localeId == nLocaleId)
		{
			if(m_gameCopys[i].baseCopy)
			{
				pBaseGameCopy = &m_gameCopys[i];
			}
			mapList.push_back(&m_gameCopys[i]);
		}
	}
	return mapList;
}

void CCopyDataMgr::AddTaskGameCopy(int nWorldMapId, int nLocaleId, int nMapId)
{
	MapCfg* pMapCfg = MapData.get(nMapId);
	if(!pMapCfg) return;
	GameCopy gameCopy = {nWorldMapId,nLocaleId,nMapId,false,true,GameMapTaskType(pMapCfg->task_copy_type)};
	m_gameCopys.push_back(gameCopy);
}

GameCopy* CCopyDataMgr::GetGameCopy(int nMapId)
{
	for (unsigned int i=0; i<m_gameCopys.size(); ++i)
	{
		if (m_gameCopys[i].mapId == nMapId)
		{
			return &m_gameCopys[i];
		}
	}
	return NULL;
}

bool CCopyDataMgr::IsGameCopyUnLock(int nMapId)
{
	GameCopy* pGameCopy = GetGameCopy(nMapId);
	if (pGameCopy)
	{
		return pGameCopy->unLock;
	}
	else
	{
		return false;
	}
}

int MapIdCompare(const void* idLeft, const void* idRight)
{
	return ((pk::OpenMap*)idLeft)->id - ((pk::OpenMap*)idRight)->id;
}

void CCopyDataMgr::InitPlacesLockInfo(pk::GS2C_OPEN_MAP_LIST *value)
{
	if (!value->bigMapList.empty())
	{
		qsort(&value->bigMapList[0],value->bigMapList.size(),sizeof(value->bigMapList[0]),MapIdCompare);
		for (unsigned int i=0; i<m_worldPlaces.size(); ++i)
		{
			pk::OpenMap BigPlace = {m_worldPlaces[i].worldMapId,0};
			//判断是否在解锁列表
			pk::OpenMap* pBigPlace = (pk::OpenMap*)bsearch(&BigPlace,&value->bigMapList[0],value->bigMapList.size(),sizeof(value->bigMapList[0]),MapIdCompare);
			m_worldPlaces[i].unLock = (pBigPlace?true:false);
		}
	}
	if (!value->smallMapList.empty())
	{
		qsort(&value->smallMapList[0],value->smallMapList.size(),sizeof(value->smallMapList[0]),MapIdCompare);
		for (unsigned int i=0; i<m_gameCopys.size(); ++i)
		{
			pk::OpenMap SmallPlace = {m_gameCopys[i].localeId,1};
			//判断是否在解锁列表
			pk::OpenMap* pSmallPlace = (pk::OpenMap*)bsearch(&SmallPlace,&value->smallMapList[0],value->smallMapList.size(),sizeof(value->smallMapList[0]),MapIdCompare);
			m_gameCopys[i].unLock = (pSmallPlace?true:false);
		}
	}

	//界面正在打开,实时刷新
	CUIWorldMap* pWorldMapUI = (CUIWorldMap*)gGameUILayer->getActiveUI(IDU_WORLDMAPUI);
	if(pWorldMapUI)
	{
		pWorldMapUI->UpdateBigPlaceLockUI();
		pWorldMapUI->UpdateSmallPlaceLockUI();
	}
}

void CCopyDataMgr::UpdatePlacesLockInfo(pk::GS2C_OPEN_MAP_UPDATE_OR_ADD* value)
{
	if (value->type == PlaceType_Big)
	{
		UpdateBigPlaceLockInfo(value->map);
		//界面正在打开,实时刷新
		CUIWorldMap* pWorldMapUI = (CUIWorldMap*)gGameUILayer->getActiveUI(IDU_WORLDMAPUI);
		if(pWorldMapUI) pWorldMapUI->UpdateBigPlaceLockUI();
	} 
	else
	{
		UpdateSmallPlaceLockInfo(value->map);
		//界面正在打开,实时刷新
		CUIWorldMap* pWorldMapUI = (CUIWorldMap*)gGameUILayer->getActiveUI(IDU_WORLDMAPUI);
		if(pWorldMapUI) pWorldMapUI->UpdateSmallPlaceLockUI();
	}
}

void CCopyDataMgr::UpdateBigPlaceLockInfo(pk::OpenMap openMap)
{
	for (unsigned int i=0; i<m_worldPlaces.size(); ++i)
	{
		if(m_worldPlaces[i].worldMapId == openMap.id)
		{
			m_worldPlaces[i].unLock = true;
			break;
		}
	}
}

void CCopyDataMgr::UpdateSmallPlaceLockInfo(pk::OpenMap openMap)
{
	vector<GameCopy*> gamecopys = GetMapList(openMap.id);
	for (unsigned int i=0; i<gamecopys.size(); ++i)
	{
		gamecopys[i]->unLock = true;
	}
}

bool CGameCopysItr::execute(WorldmapCfg* item)
{
	vector<int> locales;
	StringSplitToInt(item->locale_id,";",locales);
	for (unsigned int i=0; i<locales.size(); ++i)
	{
		LocaleCfg* pLocaleCfg = LocaleTableData.get(locales[i]);
		if(!pLocaleCfg) continue;
		GameCopy gameCopy = {item->id,locales[i],pLocaleCfg->area_id,true,false,GameMapTaskType_PT};
		m_vtrGameCopys.push_back(gameCopy);
	}
	WorldPlace worldPlace = { item->id, false };
	m_vtrWorldPlaces.push_back(worldPlace);
	return true;
}