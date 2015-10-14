/* 
	副本通用UI
	彭龙华
	2015-09-02
*/
#pragma once
#include "cocos2d.h"
#include "GameUI.h"
#include "CopyMapUI.h"

//通用副本 (歼灭,破坏,捕获,寻宝,营救)
class CCopyMapCommon:public CCopyMapUI
{
public:
	CCopyMapCommon();
	~CCopyMapCommon();

	virtual bool onInit();
	virtual void onOpen();
};