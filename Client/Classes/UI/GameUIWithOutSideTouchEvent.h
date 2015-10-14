/*
带触摸事件GameUI
彭龙华
2015-9-1
*/
#pragma once

#include "GameDef.h"
#include "GameUI.h"

typedef void (Ref::*OutSide_TouchEvent)();

class GameUIWithOutSideTouchEvent : public GameUI
{
public:
	GameUIWithOutSideTouchEvent(int idu,const std::string& strJsonFile);
	virtual ~GameUIWithOutSideTouchEvent();

	virtual bool		onInit();
	virtual void		onOpen();
	virtual void		onClose();
	virtual bool		onTouchBegan(Touch *touch, Event *unusedEvent);
    void				addOutSideTouchEventListener(Ref* target,OutSide_TouchEvent selector);

private:
	Ref*				_outSideTouchEventListener;
	OutSide_TouchEvent	_outSideTouchEventSelector;
	EventListenerTouchOneByOne*		m_pEventListener;
};