/****************************************************************************
 英雄信息UI
 彭龙华
 2015-07-29
 ****************************************************************************/

#pragma once

#include "GameDef.h"
#include "GameUI.h"

class CHeroInfo : public GameUI
{
public:
	CHeroInfo();
	~CHeroInfo();

	bool					onInit();
	void					onOpen();

private:
	//点击事件处理
	void					ClickClose(Ref *pSender, TouchEventType type);

private:
	Text*					m_TxtVip;
	Text*					m_TxtLv;
	Text*					m_TxtGold;
	Text*					m_TxtMoney;
	Text*					m_TxtPower;
	Text*					m_TxtPowerTimes;
	Layout*					m_pExpFrame;
	Widget*					m_pExpBar;
	Text*					m_pExpValue;
};