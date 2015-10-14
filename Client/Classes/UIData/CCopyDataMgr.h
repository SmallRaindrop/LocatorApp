/****************************************************************************
 副本数据管理器
 彭龙华
 2015-09-10
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "Net/pk_map.h"
#include "GameScene/db.h"
#include "GameScene/GameMapTypes.h"

typedef enum _placeType
{
	PlaceType_None = -1,
	PlaceType_Big,			//大地点
	PlaceType_Small,		//小地点
	PlaceType_Count,
}PlaceType;

typedef struct _worldPlace
{
	int worldMapId;			//大地点
	bool unLock;			//是否解锁
}WorldPlace;

typedef struct _gameCopy
{
	int worldMapId;			//大地点
	int localeId;			//小地点
	int mapId;				//副本
	bool baseCopy;			//true 基础副本,false 任务副本
	bool unLock;			//是否解锁
	GameMapTaskType TaskType;
}GameCopy;

typedef	 vector<GameCopy>			 GameCopys;
typedef	 vector<WorldPlace>			 WorldPlaces;

class CCopyDataMgr
{
public:
	CCopyDataMgr();
	~CCopyDataMgr();

	void					Init();
	void					Clear();

	//获得大地点列表
	WorldPlaces&			GetWorldPlaces() { return m_worldPlaces; }
	//获得大地点的小地点列表(基础副本列表)
	vector<GameCopy*>		GetLocaleList(int nWorldMapId);
	//获得小地点的副本列表
	vector<GameCopy*>		GetMapList(int nLocaleId);
	//特殊副本是否在副本列表
	bool					IsSpecialTaskExist(vector<GameCopy*>& gameCopys,GameMapTaskType type);
	//获得小地点的副本列表及基础副本
	vector<GameCopy*>		GetMapListAndBaseGameCopy(int nLocaleId,GameCopy* &pBaseGameCopy);
	//增加任务副本
	void					AddTaskGameCopy(int nWorldMapId, int nLocaleId, int nMapId);
	//获得游戏副本
	GameCopy*				GetGameCopy(int nMapId);

	//初始化大地点和小地点解锁信息
	void					InitPlacesLockInfo(pk::GS2C_OPEN_MAP_LIST *value);
	//更新解锁信息
	void					UpdatePlacesLockInfo(pk::GS2C_OPEN_MAP_UPDATE_OR_ADD* value);
	void					UpdateBigPlaceLockInfo(pk::OpenMap openMap);
	void					UpdateSmallPlaceLockInfo(pk::OpenMap openMap);
	//副本是否解锁
	//大地点是否锁着
	bool					IsWorldPlaceUnLock(int nWorldPlaceId);
	bool					IsGameCopyUnLock(int nMapId);

	//副本UI
	class CCopyMapUI*		GetCopyMapUI() { return m_copyMapUIOpened; }
	void					SetCopyMapUI(class CCopyMapUI* pMapUI) { m_copyMapUIOpened=pMapUI; }

	//进入的副本正在做的任务
	class Task*				GetCopyDoingTask() { return m_copyDoingTask; }
	void					SetCopyDoingTask(class Task* pTask) { m_copyDoingTask=pTask; }

private:
	GameCopys				m_gameCopys;						  //游戏所有的副本
	WorldPlaces				m_worldPlaces;						  //游戏大地点

	class CCopyMapUI*		m_copyMapUIOpened;					  //打开的副本UI
	class Task*				m_copyDoingTask;					  //进入的副本正在做的任务
};

class CGameCopysItr :public ForeachIterator<WorldmapCfg>
{
public:
	CGameCopysItr(GameCopys& vtrGameCopys,WorldPlaces& vtrWorldPlaces)
		:m_vtrGameCopys(vtrGameCopys)
		,m_vtrWorldPlaces(vtrWorldPlaces)
	{

	}
	~CGameCopysItr()
	{

	}

	virtual bool execute(WorldmapCfg* item);

private:
	GameCopys&			m_vtrGameCopys;
	WorldPlaces&		m_vtrWorldPlaces;
};