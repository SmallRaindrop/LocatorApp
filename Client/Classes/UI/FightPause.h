/****************************************************************************
 战斗暂停UI
 彭龙华
 2015-07-29
 ****************************************************************************/
#pragma once

#include "GameDef.h"
#include "GameUI.h"

class CFightPause : public GameUI
{
public:
	CFightPause();
	~CFightPause();

	bool					onInit();

private:
	//点击事件处理
	void					ClickBack(Ref *pSender, TouchEventType type);
	void					ClickLeave(Ref *pSender, TouchEventType type);
	void					ClickMusic(Ref*,CheckBoxEventType);
	void					ClickEffect(Ref*,CheckBoxEventType);
};