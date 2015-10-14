/*
	游戏功能提示管理器
	2015-8-6
	彭龙华
*/
#pragma once
#include "GameDef.h"
#include "UI/GameUI.h"

typedef enum _sysType
{
	systype_team,	//组队
	systype_chat,	//聊天
	systype_max,
}SysType;

//提示动作
typedef enum _actionType
{
	action_none,
	action_visible,
	action_blink,
	action_max,
}ActionType;

typedef union _tipsAction
{
	bool visible;		//是否可见
	bool blink;			//是否闪烁
}TipsAction;

class CSysTipsMgr : public Singleton<CSysTipsMgr>
{
public:
	typedef struct _sysTips
	{
		Widget*	widget;	//提示UI
		ActionType actionType;
		TipsAction	tipsAction;
	}SysTips;

	CSysTipsMgr();
	~CSysTipsMgr();

	//设置tips控件 tips动作
	void			SetWidget(SysType type, ActionType actionType, Widget* widget);
	//激活tips
	void			RunTipsAction(SysType type);
	void			RunTipsAction(SysTips& sysTips);
	//停止tips
	void			StopTipsAction(SysType type);

private:
	std::map<SysType,SysTips>			mTipsMap;
};

#define gSysTipsMgr		CSysTipsMgr::Instance()
