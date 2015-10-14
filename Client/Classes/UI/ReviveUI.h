/****************************************************************************
 复活UI
 李阳
 2015-9-17
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "../GameScene/GameUILayer.h"

#define MAX_FREE_REVIVE_COUNT 3
class CReviveUI : public GameUI
{
public:
	CReviveUI();
	~CReviveUI();

	bool			onInit();
	void			onOpen();
	void			onClose();

	void			update(float dt);
	void			updateUI();		//	刷新界面

	CREATE_FUNC(CReviveUI);
public:				
	void			updateTimer();								//  倒计时更新函数
	void			updateProgress();							//  进度条更新函数
	void			clickGiveupButton(Ref*, TouchEventType);	//  点击放弃副本按钮
	void			clickReviveButton(Ref*, TouchEventType);	//  点击立即复活按钮

	void			deadTimeOut();								//  假死状态结束

private:
	Text*						m_title_text;		// 标题文本
	Text*						m_timer_text;		// 倒计时文本

	ProgressTimer*				m_progressBar;		// 环形进度条

	int m_deadRestTime;			//	倒计时计数 单位：秒
	int	m_restPoint;			//	环形进度条剩余的点数 满值为10000
	int m_need_gold;			//  复活需要的金币 

public:
};

