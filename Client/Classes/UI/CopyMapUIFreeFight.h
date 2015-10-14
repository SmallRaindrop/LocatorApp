/* 
	自由战斗副本UI
	彭龙华
	2015-09-02
*/
#pragma once
#include "cocos2d.h"
#include "GameUI.h"
#include "CopyMapUI.h"

//自由战斗副本
class CCopyMapFreeFight:public CCopyMapUI
{
public:
	CCopyMapFreeFight();
	~CCopyMapFreeFight();

	virtual bool onInit();

	void		OnStartCountDown();
	void		OnEndCountDown();
	void		ClickBtnScore(Ref *pSender, TouchEventType type);
};