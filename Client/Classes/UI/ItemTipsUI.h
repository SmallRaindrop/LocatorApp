/*
 * 模块: item弹出提示界面
 * 作者: Tangbo
 * 时间: 2015/9/23
 */

#pragma once
#include "GameUIWithOutSideTouchEvent.h"
class ItemTipsUI :public GameUIWithOutSideTouchEvent
{
public:
	ItemTipsUI(void);
	~ItemTipsUI(void);

	bool   onInit();

	//清楚上次显示的设置
	void   resetData();

	void   initByItem(CItem* item,Point locationpos, GameUI * ui);

	void   initByGoddevice(GodDevice* goddevice, Point locationpos, GameUI * ui);

	//显示天书的提示
	static void   show(GodDevice* goditem,Point locationpos, GameUI * ui = nullptr);
	
	//显示普通物品的提示
	static void   show(CItem* item, Point locationpos, GameUI * ui = nullptr);

	//事件回调
	void   eventCallBack(Ref* pSender, TouchEventType touchevent);

	//外部事件
	void   outsideCallback();

private:

	//道具根节点
	ImageView* m_pRoot;

	//道具icon
	ImageView * m_pIcon;

	//道具名字
	Text*       m_pName;

	//道具精炼等级
	Text*       m_pRefineVal;

	//星级列表
	ListView*   m_pStarList;

	//属性列表
	ListView*   m_pAttriList;

	//控制按钮
	Button*     m_pOptionBtn;

	//技能描述
	Text*       m_pSkillText;

	//规则限制
	Text*       m_pRuleText;

	//星星节点
	Widget*     m_pStar;

	//属性节点
	Widget*     m_pAttri;

	//道具数据
	CItem*      m_pItem;

	//神器数据
	GodDevice*  m_pGodDevice;

	//要关闭的ui
	GameUI*     m_pGameUI;
};

