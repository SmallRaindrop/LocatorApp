#include "SysTipsMgr.h"

CSysTipsMgr::CSysTipsMgr()
{
	SysTips sysTips = {NULL,action_none,false,};

	//添加所有提示
	mTipsMap[systype_team] = sysTips;
	mTipsMap[systype_chat] = sysTips;
}

CSysTipsMgr::~CSysTipsMgr()
{
	mTipsMap.clear();
}

void CSysTipsMgr::SetWidget(SysType type, ActionType actionType, Widget* widget)
{
	std::map<SysType,SysTips>::iterator itr = mTipsMap.find(type);
	if ( itr == mTipsMap.end() ) return;

	itr->second.widget = widget;
	itr->second.actionType = actionType;
	RunTipsAction(itr->second);
}

void CSysTipsMgr::RunTipsAction(SysType type)
{
	std::map<SysType,SysTips>::iterator itr = mTipsMap.find(type);
	if ( itr == mTipsMap.end() ) return;

	if (action_visible == itr->second.actionType)
	{
		itr->second.tipsAction.visible = true;
	}
	else if(action_blink == itr->second.actionType)
	{
		itr->second.tipsAction.blink = true;
	}
	RunTipsAction(itr->second);
}

void CSysTipsMgr::RunTipsAction(SysTips& sysTips)
{
	if(!sysTips.widget) return;

	if (action_visible == sysTips.actionType)
	{
		sysTips.widget->setVisible(sysTips.tipsAction.visible);
	}
	else if(action_blink == sysTips.actionType)
	{
		if(sysTips.tipsAction.blink)
		{
			sysTips.widget->stopAllActions();
			sysTips.widget->runAction(RepeatForever::create(Blink::create(1.0f, 1)));
		}
	}
}

void CSysTipsMgr::StopTipsAction(SysType type)
{
	std::map<SysType,SysTips>::iterator itr = mTipsMap.find(type);
	if ( itr == mTipsMap.end() ) return;

	if (action_visible == itr->second.actionType)
	{
		itr->second.tipsAction.visible = false;
		itr->second.widget->setVisible(false);
	}
	else if(action_blink == itr->second.actionType)
	{
		itr->second.tipsAction.blink = false;
		itr->second.widget->stopAllActions();
		itr->second.widget->setVisible(true);
		itr->second.widget->setEnabled(true);
	}
}