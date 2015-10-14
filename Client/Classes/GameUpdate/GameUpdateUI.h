/***
 * 模块：游戏更新界面展示
 * 作者：yueliangyou
 * 时间：2015-07-21
 * 说明：更新界面资源来源于update文件夹，这里的资源相对固定，未进行打包。
 */
#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UI/CustomCtrl/ProgressBar.h"
USING_NS_CC;
using namespace std;
using namespace ui;

class GameUpdateUI : public Layer
{
public:
	GameUpdateUI();
	~GameUpdateUI();

	CREATE_FUNC(GameUpdateUI);

	/**
	 * Name : init
	 * Des  : 初始化界面对象指针
	 * Param:
	 */
	bool init();

	/**
	 * Name : GetProgressBar
	 * Des  : 获取进度条
	 * Param: none
	 */
	inline ProgerssBar* GetProgressBar(){ return m_pProgressBar; }

	/**
	 * Name : GetTipsLabel
	 * Des  : 获取提示标签
	 * Param: none
	 */
	inline Label* GetTipsLabel(){ return m_pLabelTips; }

	/**
	 * Name : update
	 * Des  : 更新加载进度
	 * Parma: fd 时间间隔
	 */
	void update(float dt);

private:
	Label*						m_pLabelTips;		// 进度显示标签
	ProgerssBar*				m_pProgressBar;		// 进度条
};