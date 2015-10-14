/****************************************************************************
 强化系统UI
 李阳
 2015-9-9
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"

class CStrengthenUI : public GameUI
{
public:
	CStrengthenUI();
	~CStrengthenUI();

	void			setItemType(CItem* item);
	void			setItemType(GodDevice* item);

	bool			onInit();
	void			onOpen();

	CREATE_FUNC(CStrengthenUI);
public:
	Widget*			createAtrributeItem();						

	void			clickCheckBox(Ref*, TouchEventType);			// 点击强化的分类checkbox 1精炼 2进阶
	void			clickBackButton(Ref*, TouchEventType);
	void			clickJinglianButton(Ref*, TouchEventType);      // 点击了精炼按钮
	void			clickJinglianMaxButton(Ref*, TouchEventType);   // 点击了最大精炼按钮
	void			clickJinjieButton(Ref*, TouchEventType);		// 点击了进阶按钮
	void			updateSelectType(int index);					// 刷新当前选择强化类型的相关面板
	void			updatejinglian();								// 更新精炼
	void			updatejinjie();									// 更新进阶
	void			updateAttribute(int type);						// 更新属性
	void			setLeftStar(int star);							// 设置左侧进阶的星级
	void			setRightStar(int star);							// 设置右侧进阶的星级
private:
	ListView*					m_attr_list;				// 属性的list列表
	ListView*					m_skill_desc_list;			// 技能描述的list列表

	CheckBox*					m_select_type_item;			// 选择的强化类型checkbox

	CheckBox*					m_jinglian_checkbox;		// 精炼checkbox
	Text*						m_jinglian_checkbox_text;	// 精炼checkbox的title
	CheckBox*					m_jinjie_checkbox;			// 进阶check
	Text*						m_jinjie_checkbox_text;		// 进阶checkbox的title

	Button*						m_jinglian_btn;				// 精炼按钮
	Button*						m_jinglian_max_btn;			// 最大精炼按钮
	Button*						m_jinjie_btn;				// 进阶按钮

	ImageView*					m_bg_item_icon;				// 左侧物品图标

	ImageView*					m_img_jinjie_star_1;		// 左侧物品星级1
	ImageView*					m_img_jinjie_star_2;		// 左侧物品星级2
	ImageView*					m_img_jinjie_star_3;		// 左侧物品星级3
	ImageView*					m_img_jinjie_star_4;		// 左侧物品星级4
	ImageView*					m_img_jinjie_star_5;		// 左侧物品星级5

	vector<ImageView*>			m_img_jinjie_star_vec;			//左侧物品星级容器
	vector<ImageView*>			m_img_attr_jinjie_star_vec;		//右侧物品星级容器

	Text*						m_jingian_level_font;		// 左侧精炼文字
	Text*						m_jinglian_level_text;		// 左侧精炼等级

	ImageView*					m_img_attr_head_icon;		// 右侧物品图标
	Text*						m_item_name_text;			// 右侧物品名字
	Text*						m_item_type_text;			// 右侧精炼文字
	Text*						m_item_level_text;			// 右侧精炼等级

	ImageView*					m_img_attr_jinjie_star_1;	// 右侧物品星级1
	ImageView*					m_img_attr_jinjie_star_2;	// 右侧物品星级2
	ImageView*					m_img_attr_jinjie_star_3;	// 右侧物品星级3
	ImageView*					m_img_attr_jinjie_star_4;	// 右侧物品星级4
	ImageView*					m_img_attr_jinjie_star_5;	// 右侧物品星级5

	Text*						m_item_skill_desc_text;		// 右侧技能描述
	Text*						m_item_level_need_text;		// 装备穿戴需要等级
	Text*						m_item_consume_text;		// 消耗类型文本
	Text*						m_item_consume_gold_text;	// 消耗金币数量文本
	Text*						m_item_consume_item_name;	// 消耗材料数量文本名字
	Text*						m_item_consume_item_have;	// 消耗材料数量文本拥有
	Text*						m_item_consume_item_need;	// 消耗材料数量文本需要

	ImageView*					m_img_consume_head_frame_icon;	// 消耗金币物品图标背景
	ImageView*					m_img_gold_frame_icon;			// 消耗金币物品图标背景

	ImageView*					m_img_consume_head_icon;	// 消耗材料物品图标

	ItemType m_item_type;		// 强化物品的类型：1神器 2物品
	CItem* m_item;				// 物品指针
	GodDevice* m_godDevice;		// 神器指针
public:
};

