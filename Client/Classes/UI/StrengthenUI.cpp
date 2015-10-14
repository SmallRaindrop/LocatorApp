#include "StrengthenUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "GameScene/GameUILayer.h"
#include "Net/NetDispatcher.h"
#include "Common/DataPool.h"
#include "GameScene/Hero.h"
#include "MessageBoxUI.h"
#include "Common/CommonDef.h"
#include "GameScene/MessageCenter.h"

#define MAX_JINGLIAN_LEVEL 30
#define MAX_JINJIE_LEVEL 5

CStrengthenUI::CStrengthenUI()
	:GameUI(IDU_StrengthenUI,JsonFile_StrengthenUI)
{
	m_select_type_item = nullptr;
	m_img_jinjie_star_vec.clear();
	m_img_attr_jinjie_star_vec.clear();
}

CStrengthenUI::~CStrengthenUI()
{
	m_select_type_item = nullptr;
	m_img_jinjie_star_vec.clear();
	m_img_attr_jinjie_star_vec.clear();
}

void CStrengthenUI::setItemType(CItem* item)
{
	m_item_type = ItemType::ItemType_Equip;
	m_item = item; 
	m_jinglian_checkbox->setSelectedState(true);
	clickCheckBox(m_jinglian_checkbox,TOUCH_EVENT_ENDED);
}

void CStrengthenUI::setItemType(GodDevice* godDevice)
{
	m_item_type = ItemType::ItemType_GodDevice;
	m_godDevice = godDevice;
	m_jinglian_checkbox->setSelectedState(true);
	clickCheckBox(m_jinglian_checkbox,TOUCH_EVENT_ENDED);
}
bool CStrengthenUI::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());

		Button *pBackBtn = (Button*)Helper::seekWidgetByName(m_pWidget, "back_btn");
		BREAK_IF(pBackBtn==NULL);
		pBackBtn->setButtonSpriteGray();
		pBackBtn->addTouchEventListener(this, SEL_TouchEvent(&CStrengthenUI::clickBackButton));


		//  精炼按钮
		m_jinglian_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "btn_jinglian");
		BREAK_IF(m_jinglian_btn==NULL);
		m_jinglian_btn->setButtonSpriteGray();
		m_jinglian_btn->addTouchEventListener(this, SEL_TouchEvent(&CStrengthenUI::clickJinglianButton));
		
		//  最大精炼按钮
		m_jinglian_max_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "btn_jinglian_max");
		BREAK_IF(m_jinglian_max_btn==NULL);
		m_jinglian_max_btn->setButtonSpriteGray();
		m_jinglian_max_btn->addTouchEventListener(this, SEL_TouchEvent(&CStrengthenUI::clickJinglianMaxButton));

		//  进阶按钮
		m_jinjie_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "btn_jinjie");
		BREAK_IF(m_jinjie_btn==NULL);
		m_jinjie_btn->setButtonSpriteGray();
		m_jinjie_btn->addTouchEventListener(this, SEL_TouchEvent(&CStrengthenUI::clickJinjieButton));

		m_jinglian_checkbox = (CheckBox*)Helper::seekWidgetByName(m_pWidget, "checkbox_jinglian");				// 精炼checkbox
		m_jinglian_checkbox->setTag(1);
		m_jinglian_checkbox->addTouchEventListener(this, SEL_TouchEvent(&CStrengthenUI::clickCheckBox));
		m_jinglian_checkbox_text = (Text*)Helper::seekWidgetByName(m_pWidget, "checkbox_title_jinglian");		// 精炼checkbox的title

		m_jinjie_checkbox = (CheckBox*)Helper::seekWidgetByName(m_pWidget, "checkbox_jinjie");					// 进阶check
		m_jinjie_checkbox->setTag(2);
		m_jinjie_checkbox->addTouchEventListener(this, SEL_TouchEvent(&CStrengthenUI::clickCheckBox));
		m_jinjie_checkbox_text = (Text*)Helper::seekWidgetByName(m_pWidget, "checkbox_title_jinjie");			// 进阶checkbox的title

		// 左侧物品图标
		m_bg_item_icon = (ImageView*)Helper::seekWidgetByName(m_pWidget,"bg_item_icon");
	
		m_img_jinjie_star_1 = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_jinjie_star_1");		// 左侧物品星级1
		m_img_jinjie_star_2 = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_jinjie_star_2");		// 左侧物品星级2
		m_img_jinjie_star_3 = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_jinjie_star_3");		// 左侧物品星级3
		m_img_jinjie_star_4 = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_jinjie_star_4");		// 左侧物品星级4
		m_img_jinjie_star_5 = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_jinjie_star_5");		// 左侧物品星级5

		m_img_jinjie_star_vec.push_back(m_img_jinjie_star_1);
		m_img_jinjie_star_vec.push_back(m_img_jinjie_star_2);
		m_img_jinjie_star_vec.push_back(m_img_jinjie_star_3);
		m_img_jinjie_star_vec.push_back(m_img_jinjie_star_4);
		m_img_jinjie_star_vec.push_back(m_img_jinjie_star_5);

		// 左侧精炼文字
		m_jingian_level_font = (Text*)Helper::seekWidgetByName(m_pWidget, "jingian_level_font");
		// 左侧精炼等级
		m_jinglian_level_text = (Text*)Helper::seekWidgetByName(m_pWidget, "jinglian_level_text");

		// 右侧物品图标
		m_img_attr_head_icon = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_attr_head_icon");

		// 右侧物品名字
		m_item_name_text = (Text*)Helper::seekWidgetByName(m_pWidget, "item_name_text");		
		// 右侧精炼文字
		m_item_type_text = (Text*)Helper::seekWidgetByName(m_pWidget, "item_type_text");
		// 右侧精炼等级
		m_item_level_text = (Text*)Helper::seekWidgetByName(m_pWidget, "item_level_text");

		m_img_attr_jinjie_star_1 = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_attr_jinjie_star_1");	// 右侧物品星级1
		m_img_attr_jinjie_star_2 = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_attr_jinjie_star_2");	// 右侧物品星级2
		m_img_attr_jinjie_star_3 = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_attr_jinjie_star_3");	// 右侧物品星级3
		m_img_attr_jinjie_star_4 = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_attr_jinjie_star_4");	// 右侧物品星级4
		m_img_attr_jinjie_star_5 = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_attr_jinjie_star_5");	// 右侧物品星级5

		m_img_attr_jinjie_star_vec.push_back(m_img_attr_jinjie_star_1);
		m_img_attr_jinjie_star_vec.push_back(m_img_attr_jinjie_star_2);
		m_img_attr_jinjie_star_vec.push_back(m_img_attr_jinjie_star_3);
		m_img_attr_jinjie_star_vec.push_back(m_img_attr_jinjie_star_4);
		m_img_attr_jinjie_star_vec.push_back(m_img_attr_jinjie_star_5);

		// 右侧技能描述
		m_item_skill_desc_text = (Text*)Helper::seekWidgetByName(m_pWidget, "item_skill_desc_text");		
		// 装备穿戴需要等级
		m_item_level_need_text = (Text*)Helper::seekWidgetByName(m_pWidget, "item_level_need_text");			
		// 消耗类型文本
		m_item_consume_text = (Text*)Helper::seekWidgetByName(m_pWidget, "item_consume_text");
		// 消耗金币数量文本
		m_item_consume_gold_text = (Text*)Helper::seekWidgetByName(m_pWidget, "item_consume_gold_text");
		// 消耗材料数量文本名字
		m_item_consume_item_name = (Text*)Helper::seekWidgetByName(m_pWidget, "item_consume_item_name");
		// 消耗材料数量文本拥有
		m_item_consume_item_have = (Text*)Helper::seekWidgetByName(m_pWidget, "item_consume_item_have");
		// 消耗材料数量文本需要
		m_item_consume_item_need = (Text*)Helper::seekWidgetByName(m_pWidget, "item_consume_item_need");

		// 消耗材料物品图标
		m_img_consume_head_icon = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_consume_head_icon");	

		// 消耗材料物品图标背景
		m_img_consume_head_frame_icon = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_consume_head_frame_icon");	
		// 消耗金币物品图标背景
		m_img_gold_frame_icon = (ImageView*)Helper::seekWidgetByName(m_pWidget,"img_gold_frame_icon");	
		

		//  属性列表
		m_attr_list = (ListView*)Helper::seekWidgetByName(m_pWidget, "attr_list");
		m_attr_list->setItemsMargin(8);

		m_skill_desc_list = (ListView*)Helper::seekWidgetByName(m_pWidget, "skill_desc_list");
		m_skill_desc_list->setItemsMargin(1);

		/*m_item_type = ItemType_GodDevice;
		m_godDevice = gHero->GetGodDeviceManager().GetIsDressGodPtr();*/

		//m_item_type = ItemType_Equip;
		//m_item = gGridsManager->findItemByDataID(emGrids_Role,1);
		
		return true;
	} while (0);

	return false;
}

void CStrengthenUI::onOpen()
{
	
}

// 点击强化的分类checkbox 1精炼 2进阶
void CStrengthenUI::clickCheckBox(Ref* pSender, TouchEventType type) 
{
	if(TOUCH_EVENT_ENDED == type)
	{
		int index_ = ((CheckBox*)pSender)->getTag();	// 神器在列表中的index

		if (m_select_type_item != nullptr) 
		{
			m_select_type_item->setSelectedState(false); // 设置为不可点击的状态
		}

		if(m_select_type_item == (CheckBox*)pSender) // 点击的就是当前选择的选项卡
		{
			CCLOG("not update\n");
		}else
		{
			m_select_type_item =  ((CheckBox*)pSender);
			updateSelectType(index_);
			CCLOG("update\n");
		}
	}
}

Widget*	CStrengthenUI::createAtrributeItem()
{
	auto node = GUIReader::getInstance()->widgetFromJsonFile("assets/ui/StrengthenAtrributeItem.json");
	return node;
}

void CStrengthenUI::clickBackButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->destroyUI(this);
	}
}

// 点击了精炼按钮
void CStrengthenUI::clickJinglianButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		int jinjie_level_ = 0;
		int jinglian_level_ = 0;
		int need_gold_number_ = 0;
		int need_item_number_ = 0;
		int need_item_id_ = 0;

		if (m_item_type == ItemType_GodDevice)
		{
			jinjie_level_ =  m_godDevice->GetGodEnhanceLevel();
			jinglian_level_ = m_godDevice->GetGodRefineLevel();

			if (jinglian_level_>=MAX_JINGLIAN_LEVEL)
			{
				gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_jinglian_max);
				return;
			}
			
			need_item_id_ = getEquipItemCfgID(1,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
			need_gold_number_ = getEquipGoldConsume(1,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
			need_item_number_ = getEquipItemNumebr(1,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
		}else
		{
			jinjie_level_ =  m_item->getEnhanceLv();
			jinglian_level_ = m_item->getRefinedLv();

			if (jinglian_level_>=MAX_JINGLIAN_LEVEL)
			{
				gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_jinglian_max);
				return;
			}

			need_item_id_ = getEquipItemCfgID(1,jinjie_level_,jinglian_level_,m_item->getDataID());
			need_gold_number_ = getEquipGoldConsume(1,jinjie_level_,jinglian_level_,m_item->getDataID());
			need_item_number_ = getEquipItemNumebr(1,jinjie_level_,jinglian_level_,m_item->getDataID());
		}

		bool is_level_over_ = jinglian_level_ >= gHero->GetLevel()/2;
		if (is_level_over_)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_level_not_enough);
			return;
		}
		int temp_gold_ = gHero->GetMoney();
		bool is_gold_enough_ = gHero->GetMoney() >= need_gold_number_;
		if (!is_gold_enough_)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_gold_not_enough);
			return;
		}

		int temp_material_ = gGridsManager->getItemCountByDataID(emGrids_BagMaterial,need_item_id_);
		bool is_material_enough_ = gGridsManager->getItemCountByDataID(emGrids_BagMaterial,need_item_id_) >= need_item_number_;
		if (!is_material_enough_)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_item_not_enough);
			return;
		}

		CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,STR_Text_Tip_Jinglian,[&](bool type){
			if(type)
			{
				pk::C2GS_Refine cmd;
				if (m_item_type == ItemType_Equip)
				{
					cmd.type = 2;
					cmd.equipId = m_item->getId();
				}else
				{
					cmd.type = 1;
					cmd.equipId = 0;
				}
				cmd.isRefineMaxLevel = 0;
				cmd.Send(gNetSocket);
			}
		},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
			this,NULL,CMessageBoxUI::Scene_Game);
	}
}

// 点击了最大精炼按钮
void CStrengthenUI::clickJinglianMaxButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		int jinjie_level_ = 0;
		int jinglian_level_ = 0;
		int need_gold_number_ = 0;
		int need_item_number_ = 0;
		int need_item_id_ = 0;

		if (m_item_type == ItemType_GodDevice)
		{
			jinjie_level_ =  m_godDevice->GetGodEnhanceLevel();
			jinglian_level_ = m_godDevice->GetGodRefineLevel();

			if (jinglian_level_>=MAX_JINGLIAN_LEVEL)
			{
				gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_jinglian_max);
				return;
			}

			need_item_id_ = getEquipItemCfgID(1,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
			need_gold_number_ = getEquipGoldConsume(1,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
			need_item_number_ = getEquipItemNumebr(1,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
		}else
		{
			jinjie_level_ =  m_item->getEnhanceLv();
			jinglian_level_ = m_item->getRefinedLv();

			if (jinglian_level_>=MAX_JINGLIAN_LEVEL)
			{
				gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_jinglian_max);
				return;
			}

			need_item_id_ = getEquipItemCfgID(1,jinjie_level_,jinglian_level_,m_item->getDataID());
			need_gold_number_ = getEquipGoldConsume(1,jinjie_level_,jinglian_level_,m_item->getDataID());
			need_item_number_ = getEquipItemNumebr(1,jinjie_level_,jinglian_level_,m_item->getDataID());
		}

		bool is_level_over_ = jinglian_level_ >= gHero->GetLevel()/2;
		if (is_level_over_)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_level_not_enough);
			return;
		}

		bool is_gold_enough_ = gHero->GetMoney() >= need_gold_number_;
		if (!is_gold_enough_)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_gold_not_enough);
			return;
		}
		bool is_material_enough_ = gGridsManager->getItemCountByDataID(emGrids_BagMaterial,need_item_id_) >= need_item_number_;
		if (!is_material_enough_)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_item_not_enough);
			return;
		}

		CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,STR_Text_Tip_Jinglian_Max,[&](bool type){
			if(type)
			{
				pk::C2GS_Refine cmd;
				if (m_item_type == ItemType_Equip)
				{
					cmd.type = 2;
					cmd.equipId = m_item->getId();
				}else
				{
					cmd.type = 1;
					cmd.equipId = 0;
				}
				cmd.isRefineMaxLevel = 1;
				cmd.Send(gNetSocket);
			}
		},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
			this,NULL,CMessageBoxUI::Scene_Game);

	}
}

// 点击了进阶按钮
void CStrengthenUI::clickJinjieButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{

		int jinjie_level_ = 0;
		int jinglian_level_ = 0;
		int need_gold_number_ = 0;
		int need_item_number_ = 0;
		int need_item_id_ = 0;

		if (m_item_type == ItemType_GodDevice)
		{
			jinjie_level_ =  m_godDevice->GetGodEnhanceLevel();
			jinglian_level_ = m_godDevice->GetGodRefineLevel();

			if (jinjie_level_>=MAX_JINJIE_LEVEL)
			{
				gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_jinjie_max);
				return;
			}

			need_item_id_ = getEquipItemCfgID(2,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
			need_gold_number_ = getEquipGoldConsume(2,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
			need_item_number_ = getEquipItemNumebr(2,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
		}else
		{
			jinjie_level_ =  m_item->getEnhanceLv();
			jinglian_level_ = m_item->getRefinedLv();

			if (jinjie_level_>=MAX_JINJIE_LEVEL)
			{
				gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_jinjie_max);
				return;
			}

			need_item_id_ = getEquipItemCfgID(2,jinjie_level_,jinglian_level_,m_item->getDataID());
			need_gold_number_ = getEquipGoldConsume(2,jinjie_level_,jinglian_level_,m_item->getDataID());
			need_item_number_ = getEquipItemNumebr(2,jinjie_level_,jinglian_level_,m_item->getDataID());
		}

		if (jinglian_level_<MAX_JINGLIAN_LEVEL/2)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_Jinjie_need);
			return;
		}

		bool is_gold_enough_ = gHero->GetMoney() >= need_gold_number_;
		if (!is_gold_enough_)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_gold_not_enough);
			return;
		}
		bool is_material_enough_ = gGridsManager->getItemCountByDataID(emGrids_BagMaterial,need_item_id_) >= need_item_number_;
		if (!is_material_enough_)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_item_not_enough);
			return;
		}

		CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,STR_Text_Tip_Jinjie,[&](bool type){
			if(type)
			{
				pk::C2GS_Enhance cmd;
				if (m_item_type == ItemType_Equip)
				{
					cmd.type = 2;
					cmd.equipId = m_item->getId();
				}else
				{
					cmd.type = 1;
					cmd.equipId = 0;
				}
				cmd.Send(gNetSocket);
			}
		},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
			this,NULL,CMessageBoxUI::Scene_Game);
	}
}
void CStrengthenUI::updateSelectType(int index)
{
	switch (index)
	{
	case 1:// 精炼
		m_jinglian_checkbox_text->setColor(Color3B(222,209,164));
		m_jinjie_checkbox_text->setColor(Color3B::WHITE);
		updatejinglian();
		break;
	case 2:// 进阶
		m_jinglian_checkbox_text->setColor(Color3B::WHITE);
		m_jinjie_checkbox_text->setColor(Color3B(222,209,164));
		updatejinjie();
		break;
	default:
		break;
	}
}

// 更新精炼
void CStrengthenUI::updatejinglian()
{	
	m_jinglian_max_btn->setEnabled(true);
	m_jinglian_btn->setEnabled(true);
	m_jinjie_btn->setEnabled(false);

	m_img_jinjie_star_1->setVisible(false);
	m_img_jinjie_star_2->setVisible(false);
	m_img_jinjie_star_3->setVisible(false);
	m_img_jinjie_star_4->setVisible(false);
	m_img_jinjie_star_5->setVisible(false);

	m_jingian_level_font->setVisible(true);
	m_jinglian_level_text->setVisible(true);

	int jinglian_level_ = 1;

	if (m_item_type == ItemType_GodDevice)
	{
		jinglian_level_ = m_godDevice->GetGodRefineLevel();
	}else
	{
		jinglian_level_ = m_item->getRefinedLv();
	}

	if (jinglian_level_<MAX_JINGLIAN_LEVEL)
	{
		m_img_gold_frame_icon->setVisible(true);
		m_img_consume_head_frame_icon->setVisible(true);
		m_item_consume_text->setVisible(true);
		m_item_consume_gold_text->setVisible(true);
		m_item_consume_item_name->setVisible(true);
		m_item_consume_item_need->setVisible(true);
		m_item_consume_item_have->setVisible(true);
	}else
	{
		m_img_gold_frame_icon->setVisible(false);
		m_img_consume_head_frame_icon->setVisible(false);
		m_item_consume_text->setVisible(false);
		m_item_consume_gold_text->setVisible(false);
		m_item_consume_item_name->setVisible(false);
		m_item_consume_item_need->setVisible(false);
		m_item_consume_item_have->setVisible(false);
	}

	m_jinglian_level_text->setText(FORMAT_TO_STRING("%d",jinglian_level_));
	m_item_consume_text->setText(STR_Text_Jinglian_Consume);

	updateAttribute(1);
}

// 更新进阶
void CStrengthenUI::updatejinjie()
{
	m_jinglian_max_btn->setEnabled(false);
	m_jinglian_btn->setEnabled(false);
	m_jinjie_btn->setEnabled(true);

	m_jingian_level_font->setVisible(false);
	m_jinglian_level_text->setVisible(false);

	int jinjie_level_ = 1;
	if (m_item_type == ItemType_GodDevice)
	{
		jinjie_level_ = m_godDevice->GetGodEnhanceLevel();
	}else
	{
		jinjie_level_ = m_item->getEnhanceLv();
	}
	setLeftStar(jinjie_level_);

	if (jinjie_level_<MAX_JINJIE_LEVEL)
	{
		m_img_gold_frame_icon->setVisible(true);
		m_img_consume_head_frame_icon->setVisible(true);
		m_item_consume_text->setVisible(true);
		m_item_consume_gold_text->setVisible(true);
		m_item_consume_item_name->setVisible(true);
		m_item_consume_item_have->setVisible(true);
		m_item_consume_item_need->setVisible(true);
	}else
	{
		m_img_gold_frame_icon->setVisible(false);
		m_img_consume_head_frame_icon->setVisible(false);
		m_item_consume_text->setVisible(false);
		m_item_consume_gold_text->setVisible(false);
		m_item_consume_item_name->setVisible(false);
		m_item_consume_item_have->setVisible(false);
		m_item_consume_item_need->setVisible(false);
	}

	m_item_consume_text->setText(STR_Text_Jinjie_Consume);
	updateAttribute(2);
}

// 更新属性
void CStrengthenUI::updateAttribute(int type) // type:1精炼 2进阶
{
	m_attr_list->removeAllItems();
	m_skill_desc_list->removeAllItems();

	int need_level_ = 0;
	int need_gold_number_ = 0;
	int need_item_number_ = 0;
	int need_item_id_ = 0;

	int jinjie_level_ = 0;
	int jinglian_level_ = 0; 
	string item_name_text_; 

	if (m_item_type == ItemType_GodDevice)
	{
		jinjie_level_ =  m_godDevice->GetGodEnhanceLevel();
		jinglian_level_ = m_godDevice->GetGodRefineLevel();
		item_name_text_ = m_godDevice->GetGodName();

		auto all_attr_vec = m_godDevice->m_all_attr_vec[jinjie_level_];
		need_level_ = ItemData.get(m_godDevice->GetGodDataId())->uselevel;

		if (1 == type )
		{
			if (jinglian_level_<MAX_JINGLIAN_LEVEL)
			{
				need_gold_number_ = getEquipGoldConsume(type,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
				need_item_number_ = getEquipItemNumebr(type,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
				need_item_id_ = getEquipItemCfgID(type,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
			}
		}else
		{
			if (jinjie_level_<MAX_JINJIE_LEVEL)
			{
				need_gold_number_ = getEquipGoldConsume(type,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
				need_item_number_ = getEquipItemNumebr(type,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
				need_item_id_ = getEquipItemCfgID(type,jinjie_level_,jinglian_level_,m_godDevice->GetGodDataId());
			}
		}

		for (size_t i = 0;i<m_godDevice->GetGodSkillIdVec().size();i++)
		{
			int skill_id_ = m_godDevice->GetGodSkillIdVec()[i];
			string desc_string_ = SkillData.get(skill_id_)->desc;
			Text* desc_text_ = Text::create(desc_string_,"arial",18);
			desc_text_->setColor(Color3B(44,240,12)); // 把技能描述设为绿色

			m_skill_desc_list->pushBackCustomItem(desc_text_);
		}

		for (size_t i = 0;i<all_attr_vec.size();++i)
		{
			auto temp_item_ = createAtrributeItem();
			auto attr_name_text_ = (Text*)Helper::seekWidgetByName(temp_item_, "attr_name_text");
			auto attr_number_text_ = (Text*)Helper::seekWidgetByName(temp_item_, "attr_number_text");
			auto attr_dif_number_text_ = (Text*)Helper::seekWidgetByName(temp_item_, "attr_dif_number_text");

			string attribute_name_ = getEquipAttributeName(jinjie_level_,i,m_godDevice->m_all_attr_vec);
			attribute_name_.append(":");
			attr_name_text_->setText(attribute_name_);

			string attribute_total_value_ = FORMAT_TO_STRING("%d",getEquipTotalAttribute(jinjie_level_,jinglian_level_,i,m_godDevice->m_all_attr_vec));
			attr_number_text_->setText(attribute_total_value_);
	
			if (1 == type )
			{
				if (jinglian_level_<MAX_JINGLIAN_LEVEL)
				{
					if (getEquipAtrributeIfChange(type,jinjie_level_,jinglian_level_,i,m_godDevice->m_all_attr_vec))
					{
						attr_dif_number_text_->setVisible(true);
						string attribute_change_value_ = getEquipAtrributeChange(type,jinjie_level_,jinglian_level_,i,m_godDevice->m_all_attr_vec);
						attr_dif_number_text_->setText(attribute_change_value_);
						attr_dif_number_text_->setColor(Color3B(44,240,12));
					}else
					{
						attr_dif_number_text_->setVisible(false);
					}
				}else
				{
					attr_dif_number_text_->setVisible(false);
				}
			}else
			{
				if (jinjie_level_<MAX_JINJIE_LEVEL)
				{
					if (getEquipAtrributeIfChange(type,jinjie_level_,jinglian_level_,i,m_godDevice->m_all_attr_vec))
					{
						attr_dif_number_text_->setVisible(true);
						string attribute_change_value_ = getEquipAtrributeChange(type,jinjie_level_,jinglian_level_,i,m_godDevice->m_all_attr_vec);
						attr_dif_number_text_->setText(attribute_change_value_);
						attr_dif_number_text_->setColor(Color3B(44,240,12));
					}else
					{
						attr_dif_number_text_->setVisible(false);
					}
				}else
				{
					attr_dif_number_text_->setVisible(false);
				}
			}

			m_attr_list->pushBackCustomItem(temp_item_);
		}

	}else if (m_item_type == ItemType_Equip)
	{
		jinjie_level_ =  m_item->getEnhanceLv();
		jinglian_level_ = m_item->getRefinedLv();
		item_name_text_ = m_item->getEquipBaseData()->name;

		auto all_attr_vec = m_item->m_all_attr_vec[jinjie_level_];
		need_level_ = ItemData.get(m_item->getDataID())->uselevel;

		if (type == 1)
		{
			if (jinglian_level_<MAX_JINGLIAN_LEVEL)
			{
				need_gold_number_ = getEquipGoldConsume(type,jinjie_level_,jinglian_level_,m_item->getDataID());
				need_item_number_ = getEquipItemNumebr(type,jinjie_level_,jinglian_level_,m_item->getDataID());
				need_item_id_ = getEquipItemCfgID(type,jinjie_level_,jinglian_level_,m_item->getDataID());
			}
		}else
		{
			if (jinjie_level_<MAX_JINJIE_LEVEL)
			{
				need_gold_number_ = getEquipGoldConsume(type,jinjie_level_,jinglian_level_,m_item->getDataID());
				need_item_number_ = getEquipItemNumebr(type,jinjie_level_,jinglian_level_,m_item->getDataID());
				need_item_id_ = getEquipItemCfgID(type,jinjie_level_,jinglian_level_,m_item->getDataID());
			}
		}
		
		for (size_t i = 0;i<m_item->m_skillId_vec.size();i++)
		{
			int skill_id_ = m_item->m_skillId_vec[i];
			string desc_string_ = SkillData.get(skill_id_)->desc;
			Text* desc_text_ = Text::create(desc_string_,"arial",18);
			desc_text_->setColor(Color3B(44,240,12)); // 把技能描述设为绿色

			m_skill_desc_list->pushBackCustomItem(desc_text_);
		}

		for (size_t i = 0;i<all_attr_vec.size();i++)
		{
			auto temp_item_ = createAtrributeItem();
			auto attr_name_text_ = (Text*)Helper::seekWidgetByName(temp_item_, "attr_name_text");
			auto attr_number_text_ = (Text*)Helper::seekWidgetByName(temp_item_, "attr_number_text");
			auto attr_dif_number_text_ = (Text*)Helper::seekWidgetByName(temp_item_, "attr_dif_number_text");

			string attribute_name_ = getEquipAttributeName(jinjie_level_,i,m_item->m_all_attr_vec);
			attribute_name_.append(":");
			attr_name_text_->setText(attribute_name_);

			string attribute_total_value_ = FORMAT_TO_STRING("%d",getEquipTotalAttribute(jinjie_level_,jinglian_level_,i,m_item->m_all_attr_vec));
			attr_number_text_->setText(attribute_total_value_);

			if (type == 1)
			{
				if (jinglian_level_<MAX_JINGLIAN_LEVEL)
				{
					if (getEquipAtrributeIfChange(type,jinjie_level_,jinglian_level_,i,m_item->m_all_attr_vec))
					{
						attr_dif_number_text_->setVisible(true);
						string attribute_change_value_ = getEquipAtrributeChange(type,jinjie_level_,jinglian_level_,i,m_item->m_all_attr_vec);
						attr_dif_number_text_->setText(attribute_change_value_);
						attr_dif_number_text_->setColor(Color3B(44,240,12));
					}else
					{
						attr_dif_number_text_->setVisible(false);
					}
				}else
				{
					attr_dif_number_text_->setVisible(false);
				}
			}else
			{
				if (jinjie_level_<MAX_JINJIE_LEVEL)
				{
					if (getEquipAtrributeIfChange(type,jinjie_level_,jinglian_level_,i,m_item->m_all_attr_vec))
					{
						attr_dif_number_text_->setVisible(true);
						string attribute_change_value_ = getEquipAtrributeChange(type,jinjie_level_,jinglian_level_,i,m_item->m_all_attr_vec);
						attr_dif_number_text_->setText(attribute_change_value_);
						attr_dif_number_text_->setColor(Color3B(44,240,12));
					}else
					{
						attr_dif_number_text_->setVisible(false);
					}
				}else
				{
					attr_dif_number_text_->setVisible(false);
				}
			}

			m_attr_list->pushBackCustomItem(temp_item_);
		}
	}

	setRightStar(jinjie_level_);
	
	m_item_level_text->setText(FORMAT_TO_STRING("%d",jinglian_level_));
	m_item_name_text->setText(item_name_text_);

	m_item_level_need_text->setVisible(need_level_ != 1);
	m_item_level_need_text->setColor(Color3B(240,12,12)); // 把需求等级设为红色
	m_item_level_need_text->setText(FORMAT_TO_STRING("Need:%d",need_level_));

	bool is_gold_enough_ = gHero->GetMoney() >= need_gold_number_;
	if (!is_gold_enough_)
	{
		m_item_consume_gold_text->setColor(Color3B::RED);
	}else
	{
		m_item_consume_gold_text->setColor(Color3B::WHITE);
	}
	m_item_consume_gold_text->setText(FORMAT_TO_STRING("%d",need_gold_number_));

	if (type == 1)
	{
		m_item_consume_item_name->setText(FORMAT_TO_STRING("%s:",STR_Text_Jinglian_Stone));
	}else if(type == 2)
	{
		m_item_consume_item_name->setText(FORMAT_TO_STRING("%s:",STR_Text_Jinjie_Stone));
	}

	m_item_consume_item_have->setText(FORMAT_TO_STRING("/%d",gGridsManager->getItemCountByDataID(emGrids_BagMaterial,need_item_id_)));
	m_item_consume_item_need->setText(FORMAT_TO_STRING("%d",need_item_number_));
	
	bool is_material_enough_ = gGridsManager->getItemCountByDataID(emGrids_BagMaterial,need_item_id_) >= need_item_number_;
	if (!is_material_enough_)
	{
		m_item_consume_item_need->setColor(Color3B::RED);
		m_item_consume_item_have->setColor(Color3B::RED);
	}else
	{
		m_item_consume_item_need->setColor(Color3B::WHITE);
		m_item_consume_item_have->setColor(Color3B::WHITE);
	}
	m_item_consume_item_need->setPositionX(m_item_consume_item_name->getPositionX()+ m_item_consume_item_name->getContentSize().width);
	m_item_consume_item_have->setPositionX(m_item_consume_item_need->getPositionX()+ m_item_consume_item_need->getContentSize().width);
}

void CStrengthenUI::setLeftStar(int star)
{

	for (int i = 0;i < 5;i++)
	{
		m_img_jinjie_star_vec[i]->setVisible(false);
	}

	for (int i = 0;i < star;i++)
	{
		m_img_jinjie_star_vec[i]->setVisible(true);
	}
}

void CStrengthenUI::setRightStar(int star)
{

	for (int i = 0;i < 5;i++)
	{
		m_img_attr_jinjie_star_vec[i]->setVisible(false);
	}

	for (int i = 0;i < star;i++)
	{
		m_img_attr_jinjie_star_vec[i]->setVisible(true);
	}
}


