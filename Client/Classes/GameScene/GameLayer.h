#ifndef __GameLayer_h_
#define __GameLayer_h_

#include "GameDef.h"
#include "Singleton.h"
#include "GameMap.h"

#define gGameLayer	CGameLayer::Instance()

class ResMap : public ResBase
{
public:
	ResMap() : m_nMapID(0),m_nCX(0),m_nCY(0),ResBase(0,ResType_File,""){}
	~ResMap(){}

public:
	bool load();
	void onLoadComplete(ResTask* pTask);

	inline void setMapID(int mapid,int cx,int cy){ m_nMapID = mapid; m_nCX=cx; m_nCY=cy; }

private:
	int m_nMapID;
	int m_nCX;
	int m_nCY;
};

class CGameLayer : public Layer,public Singleton<CGameLayer>
{
public:
	CGameLayer();
	~CGameLayer();

	void update(float dt);

public:
	inline GameMap* getCurrMap(){ return m_pMap; }

	void switchMap(int mapid,int cx,int cy);
	void deleteMap();

protected:
	GameMap*	m_pMap;
	ResMap		m_mapLoader;
};

#endif // __GameLayer_h_