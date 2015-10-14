#include "GameLayer.h"
#include "GameMap.h"
#include "Hero.h"
#include "UI/CustomCtrl/JoyStick.h"
#include "GameDataManager.h"
#include "GameUILayer.h"
#include "UI/LoadingUI.h"
#include "Net/NetDispatcher.h"
#include "GameScene/Monster.h"
#include "UI/DramaUi.h"

bool ResMap::load()
{
	GameMap* pMap = gGameLayer->getCurrMap();
	CCLOG("ResMap =============load start============");
	if ( pMap->loadMap(m_nMapID) )
	{
		CCLOG("ResMap =============load succ============");
		return true;
	}
	CCLOG("ResMap =============load fail============");
	return false;
}

void ResMap::onLoadComplete(ResTask* pTask)
{
	ResBase::onLoadComplete(pTask);

	GameMap* pMap = gGameLayer->getCurrMap();

	// ´´½¨Ä£ºý±³¾°
	Sprite* pBg = Sprite::create(pMap->getMapBgFileName());
	if ( pBg )
	{
		float scaleX = (float)pMap->getMapWidth()/pBg->getContentSize().width;
		float scaleY = (float)pMap->getMapHeight()/pBg->getContentSize().height;
		pBg->setScaleX(scaleX);
		pBg->setScaleY(scaleY);
		pBg->setAnchorPoint(Point::ZERO);
		pMap->addChild(pBg,-9999);
	}
	else
	{
		LOGE("can't find map file[%s]",pMap->getMapBgFileName());
	}

	gGameLayer->addChild(pMap);
	gHero->EnterMap(pMap,m_nCX,m_nCY);
	gLoadingUI->SetPercent(100.f, 4.f);
	LOGD("========ResMap::onLoadComplete=========");
	gNetDispatcher->Unlock();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CGameLayer::CGameLayer() : m_pMap(NULL)
{
	
}

CGameLayer::~CGameLayer()
{
	removeFromParent();
	deleteMap();
}

void CGameLayer::update(float dt)
{
	if ( m_pMap && m_mapLoader.isOk() )
	{
		m_pMap->update(dt);
	}
}

void CGameLayer::switchMap(int mapid,int cx,int cy)
{
	deleteMap();
	m_pMap = GameMap::create();
	if ( !m_pMap )
	{
		return ;
	}

	gNetDispatcher->Lock();
	m_pMap->retain();

	m_mapLoader.setMapID(mapid,cx,cy);
	m_mapLoader.loadAsync();
}

void CGameLayer::deleteMap()
{
	if ( m_pMap )
	{
		m_pMap->removeFromParentAndCleanup(true);
		m_pMap->release();
		m_pMap = NULL;
	}
}