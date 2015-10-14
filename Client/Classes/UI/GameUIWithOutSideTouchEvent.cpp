#include "GameUIWithOutSideTouchEvent.h"

GameUIWithOutSideTouchEvent::GameUIWithOutSideTouchEvent(int idu, const string& strJsonFile)
:GameUI(idu,strJsonFile)
,_outSideTouchEventListener(nullptr)
,_outSideTouchEventSelector(nullptr)
,m_pEventListener(nullptr)
{

}

GameUIWithOutSideTouchEvent::~GameUIWithOutSideTouchEvent()
{
	_outSideTouchEventListener = nullptr;
	_outSideTouchEventSelector = nullptr;
}

bool GameUIWithOutSideTouchEvent::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());
		return true;
	} while (0);
	return false;
}

void GameUIWithOutSideTouchEvent::onOpen()
{
	m_pEventListener = EventListenerTouchOneByOne::create();
	m_pEventListener->setSwallowTouches(false);
	m_pEventListener->onTouchBegan = CC_CALLBACK_2(GameUIWithOutSideTouchEvent::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pEventListener, this);
}

void GameUIWithOutSideTouchEvent::onClose()
{
	if(m_pEventListener)
	{
		_eventDispatcher->removeEventListener(m_pEventListener);
		m_pEventListener = nullptr;
	}
}

bool GameUIWithOutSideTouchEvent::onTouchBegan(Touch *touch, Event *unusedEvent)
{
	if (_outSideTouchEventListener&&_outSideTouchEventSelector)
	{
		(_outSideTouchEventListener->*_outSideTouchEventSelector)();
	}
	return false;
}

void GameUIWithOutSideTouchEvent::addOutSideTouchEventListener(Ref* target,OutSide_TouchEvent selector)
{
	_outSideTouchEventListener = target;
	_outSideTouchEventSelector = selector;
}