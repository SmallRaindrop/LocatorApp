/****************************************************************************
 宠物UI
 李阳
 2015-10-13
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "../GameScene/GameUILayer.h"

class CPetUI : public GameUI
{
public:
	CPetUI();
	~CPetUI();

	bool			onInit();
	void			onOpen();
	void			onClose();

	CREATE_FUNC(CPetUI);
public:				
	void			clickBackButton(Ref*, TouchEventType);		//  点击返回按钮
	void			clickTianshuButton(Ref*, TouchEventType);	//	点击了天书按钮
	void			clickQianghuaButton(Ref*, TouchEventType);	//  点击了强化按钮

	void			clickCheckBox(Ref*, TouchEventType);		// 点击宠物分类checkbox 

	void			clickSwitch(Ref*, TouchEventType);		//  切换面板按钮

	void			updatePetList();						//  更新宠物列表

	void			updateAttributePanel();					//  更新属性面板

	void			updateQianghuaPanel();					//  更新强化面板
private:

	Button*		m_BackButton_btn_2;		// 强化面板的返回按钮
	Button*		m_Qianghua_btn_2;		// 强化面板的强化按钮
	Button*		m_Qianghua_btn;			// 强化按钮
	Button*		m_Tianshu_btn;			// 天书按钮

	ImageView*	m_attribute_panel;		// 属性面板
	ImageView*	m_qianghua_panel;		// 强化面板

	ListView*	m_listView_pet;			// 宠物列表

	ListView*	m_listView_attribute;	// 基本属性列表
	ListView*	m_attr_list;			// 强化属性列表

	CheckBox*	m_select_pet_item;		// 选择的宠物
public:
};

