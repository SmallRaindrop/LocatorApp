/****************************************************************************
 神器系统UI
 李阳
 2015-9-2
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"

class ShaderSprite;

class CGodDeviceUI : public GameUI
{
public:
	CGodDeviceUI();
	~CGodDeviceUI();

	bool			onInit();
	void			onOpen();

	CREATE_FUNC(CGodDeviceUI);
public:
	Widget*			createTabItem();						

	void			clickCheckBox(Ref*, TouchEventType);		// 点击神器的分类checkbox
	void			clickCloseButton(Ref*, TouchEventType);
	void			clickDressButton(Ref*, TouchEventType);     // 点击了穿戴按钮
	void			updateGodDeviceList();						// 刷新神器列表
	void			updateGodDeviceData(int index);			// 刷新选择神器的数据
private:
	ListView*					m_type_list;	// 神器类型的列表

	CheckBox*					m_select_type_item;    // 选择的神器类型
	Button*						m_dress_btn;		   // 装备按钮

	Text*						m_name_label;		// 神器名字
	Text*						m_des_label;		// 神器描述
	Text*						m_attr_label_1;		// 神器属性1
	Text*						m_attr_label_2;		// 神器属性2
	Text*						m_attr_label_3;		// 神器属性3
	Text*						m_attr_label_4;		// 神器属性4

	ShaderSprite*				m_skill_icon_1;		// 技能图标1
	ShaderSprite*				m_skill_icon_2;		// 技能图标2
	ShaderSprite*				m_skill_icon_3;		// 技能图标3
	ShaderSprite*				m_skill_icon_4;		// 技能图标4

	vector<ShaderSprite*>		m_skill_icon_vec;		// 技能图标vec

	ImageView* m_skill_icon_bg_1;
	ImageView* m_skill_icon_bg_2;
	ImageView* m_skill_icon_bg_3;
	ImageView* m_skill_icon_bg_4;
	vector<ImageView*>		    m_skill_icon_bg_vec;	// 技能图标背框vec

	Text*						m_skill_name_1;		// 技能名字1
	Text*						m_skill_name_2;		// 技能名字2
	Text*						m_skill_name_3;		// 技能名字3
	Text*						m_skill_name_4;		// 技能名字4

	vector<Text*>				m_skill_name_vec;	// 技能名字vec

	Text*						m_skill_des_1;		// 技能描述1
	Text*						m_skill_des_2;		// 技能描述2
	Text*						m_skill_des_3;		// 技能描述3
	Text*						m_skill_des_4;		// 技能描述4

	vector<Text*>				m_skill_des_vec;	// 技能描述vec

	vector<int>					m_indexToGodCfgId_vec; // 下标对应的cfgId
public:
};

