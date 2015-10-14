/* 
	防守副本UI
	彭龙华
	2015-09-02
*/
#pragma once
#include "cocos2d.h"
#include "GameUI.h"
#include "CopyMapUI.h"

//守护副本
class CCopyMapUIDef:public CCopyMapUI
{
public:
	CCopyMapUIDef();
	~CCopyMapUIDef();

	virtual bool			onInit();

	virtual void			updateMonsterWave(pk::GS2C_MonsterSpawnRemind* value);
};