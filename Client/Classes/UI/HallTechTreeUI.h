/****************************************************************************
 战舰科技树UI
 李阳
 2015-9-29
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "../GameScene/GameUILayer.h"

class CHallTechTreeUI : public GameUI
{
public:
	CHallTechTreeUI();
	~CHallTechTreeUI();

	bool			onInit();
	void			onOpen();
	void			onClose();
	
	void			UpdateAll();

	void			update(float dt);

	CREATE_FUNC(CHallTechTreeUI);
public:				
	void			clickBackButton(Ref*, TouchEventType);			//  点击返回主界面按钮
	void			clickUpgradeButton(Ref*, TouchEventType);		//  点击入口按钮
	
	void			clickCheckBox(Ref*, TouchEventType);			// 点击科技树分类checkbox 

	void			updateRightPanel(int index);					// 更新右侧面板
private:
	Text*						m_name_text;		// 科技树名字文本
	Text*						m_des_text;			// 科技树描述文本
	Text*						m_need_text;		// 科技树升级需求文本

	Button *					upgrade_btn_;
	Text*						m_time_text;		// 科技树升级需时间

	ImageView*					m_bar_bg;			// 进度条背景 
		
	LoadingBar*					m_bar;				// 进度条

	Layout*						m_tree_panel;		// 科技树分类面板

	ListView*					m_listView;			// 科技树升级需求列表
	ui::ScrollView*				m_scrollView;		// 科技树分类滚动列表

	Button*						m_upgrade_btn;		// 升级按钮

	vector<ui::Widget*>			m_treeIcon;			// 自定义ICON图标vec

	CheckBox*					m_select_node_item;    // 选择的科技树节点

	int	m_index;	// 选择的科技树下标
public:
};

