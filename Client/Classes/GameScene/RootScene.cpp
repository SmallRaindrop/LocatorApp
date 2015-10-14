#include "RootScene.h"
#include "MemoryMonitor.h"

CRootScene* CRootScene::s_pRootScene = nullptr; 

CRootScene::CRootScene() : m_pCurrScene(nullptr)
{
	
}

CRootScene::~CRootScene()
{
	unschedule(schedule_selector(CRootScene::updateFPS));
}

CRootScene* CRootScene::getInstance()
{
	if ( s_pRootScene )
	{
		return s_pRootScene;
	}

	s_pRootScene = CRootScene::create();

	return s_pRootScene;
}

bool CRootScene::init()
{
	Point pos = gDirector->getVisibleOrigin();

	m_pLayerWhite = LayerColor::create(Color4B::WHITE);
	m_pLayerBlack = LayerColor::create(Color4B::BLACK);
	m_pLayerWhite->setPosition(pos+Point(-1,-1));
	m_pLayerBlack->setPosition(pos);
	addChild(m_pLayerWhite,1);
	addChild(m_pLayerBlack,2);

	m_pLabel = Label::createWithSystemFont("","Arial",24);
	m_pLabel->setAnchorPoint(Point::ZERO);
	m_pLayerBlack->addChild(m_pLabel);

	schedule(schedule_selector(CRootScene::updateFPS),FPS_INTERVAL);
	
	return true;
}

void CRootScene::update(float delta)
{
	//updateFPS();
}

void CRootScene::updateFPS(float delta)
{
	__String str;
	str.initWithFormat("FPS %.2f Time %.1fms RAM %.1fMB/%.1fMB",gDirector->getFrameRate(),gDirector->getSecondsPerFrame()*1000.0f,gMemoryMonitor->usedMemory(),gMemoryMonitor->freeMemory());
	if ( m_pLabel )
	{
		m_pLabel->setString(str.getCString());
		m_pLayerBlack->setContentSize(m_pLabel->getContentSize()+Size(10,0));
		m_pLayerWhite->setContentSize(m_pLayerBlack->getContentSize()+Size(2,2));
	}
}

void CRootScene::replaceScene(Scene* pScene)
{
	if ( m_pCurrScene )
	{
		m_pCurrScene->removeFromParent();
		m_pCurrScene = nullptr;
	}

	if ( pScene )
	{
		m_pCurrScene = pScene;
		addChild(pScene);
	}
}