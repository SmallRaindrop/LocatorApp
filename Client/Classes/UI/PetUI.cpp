#include "PetUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "GameScene/GameUILayer.h"
#include "Net/NetDispatcher.h"
#include "Common/DataPool.h"
#include "GameScene/MessageCenter.h"
#include "MessageBoxUI.h"
#include "GameScene/MessageCenter.h"
#include "UI/ResMgr/CtrlAllocator.h"
#include "ShaderSprite.h"
#include "GameScene/Hero.h"

CPetUI::CPetUI()
	:GameUI(IDU_PetUI,JsonFile_PetUI)
{
	m_select_pet_item = nullptr;
}

CPetUI::~CPetUI()
{
	m_select_pet_item = nullptr;
}

bool CPetUI::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());

		Button *pBack_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "back_btn");
		BREAK_IF(pBack_btn==NULL);
		pBack_btn->setButtonSpriteGray();
		pBack_btn->addTouchEventListener(this, SEL_TouchEvent(&CPetUI::clickBackButton));

		m_BackButton_btn_2 = (Button*)Helper::seekWidgetByName(m_pWidget, "back2_btn");
		BREAK_IF(m_BackButton_btn_2==NULL);
		m_BackButton_btn_2->setButtonSpriteGray();
		m_BackButton_btn_2->addTouchEventListener(this, SEL_TouchEvent(&CPetUI::clickSwitch));
		m_BackButton_btn_2->setTag(1001);

		m_Qianghua_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "qianghua_btn");
		BREAK_IF(m_Qianghua_btn==NULL);
		m_Qianghua_btn->setButtonSpriteGray();
		m_Qianghua_btn->addTouchEventListener(this, SEL_TouchEvent(&CPetUI::clickSwitch));
		m_Qianghua_btn->setTag(1002);

		m_Tianshu_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "tianshu_btn");
		BREAK_IF(m_Tianshu_btn==NULL);
		m_Tianshu_btn->setButtonSpriteGray();
		m_Tianshu_btn->addTouchEventListener(this, SEL_TouchEvent(&CPetUI::clickTianshuButton));

		m_Qianghua_btn_2 = (Button*)Helper::seekWidgetByName(m_pWidget, "qianghua2_btn");
		BREAK_IF(m_Qianghua_btn_2==NULL);
		m_Qianghua_btn_2->setButtonSpriteGray();
		m_Qianghua_btn_2->addTouchEventListener(this, SEL_TouchEvent(&CPetUI::clickQianghuaButton));

		m_attribute_panel = (ImageView*)Helper::seekWidgetByName(m_pWidget, "bg_img_3");
		m_qianghua_panel = (ImageView*)Helper::seekWidgetByName(m_pWidget, "bg_img_4");
		
		m_attribute_panel->setVisible(true);
		m_Tianshu_btn->setTouchEnabled(true);
		m_Qianghua_btn->setTouchEnabled(true);
		
		m_qianghua_panel->setVisible(false);
		m_Qianghua_btn_2->setTouchEnabled(false);
		m_BackButton_btn_2->setTouchEnabled(false);

		// 宠物列表
		m_listView_pet = (ListView*)Helper::seekWidgetByName(m_pWidget, "listView_pet");

		// 基本属性列表
		m_listView_attribute = (ListView*)Helper::seekWidgetByName(m_pWidget, "listView_attribute");

		// 强化属性列表
		m_attr_list = (ListView*)Helper::seekWidgetByName(m_pWidget, "attr_list");

		updatePetList();
		updateAttributePanel();
		updateQianghuaPanel();
		return true;
	} while (0);

	return false;
}

void CPetUI::updateAttributePanel()
{
	CPetItem* temp_pet_data_ = gHero->GetPetItemManager().GetPetDataList()[0];
	m_listView_attribute->removeAllItems();
	Widget* temp_Attribute_panel_ = (Widget*)Helper::seekWidgetByName(m_pWidget, "Attribute_panel");
	for (int i = 0;i<13;++i)
	{
		Widget* attr_panel_ = temp_Attribute_panel_->clone();

		Text* attr_name_text_ = (Text*)Helper::seekWidgetByName(attr_panel_, "attr_name_text");
		Text* attr_number_text_ = (Text*)Helper::seekWidgetByName(attr_panel_, "attr_number_text");

		int number_ = 0;
		string name_ = "";

		attr_name_text_->setText(name_);
		attr_number_text_->setText(FORMAT_TO_STRING("%d",number_));

		m_listView_attribute->pushBackCustomItem(attr_panel_);
	}
}

void CPetUI::updateQianghuaPanel()
{
	m_attr_list->removeAllItems();
	Widget* temp_Attribute_panel_ = (Widget*)Helper::seekWidgetByName(m_pWidget, "Attribute_panel_qianghua");
	for (int i = 0;i<13;++i)
	{
		Widget* attr_panel_ = temp_Attribute_panel_->clone();

		Text* attr_name_text_ = (Text*)Helper::seekWidgetByName(attr_panel_, "attr_name_text");
		Text* attr_before_number_text_ = (Text*)Helper::seekWidgetByName(attr_panel_, "attr_before_number_text");
		Text* attr_after_number_text_ = (Text*)Helper::seekWidgetByName(attr_panel_, "attr_after_number_text");

		m_attr_list->pushBackCustomItem(attr_panel_);
	}
}

void CPetUI::updatePetList()
{

	Widget* temp_pet_head_ = (Widget*)Helper::seekWidgetByName(m_pWidget, "PetHead_panel");

	for (int i = 0;i<6;++i)
	{
		Widget* pet_head_ = temp_pet_head_->clone();

		CheckBox* checbox_ = (CheckBox*)Helper::seekWidgetByName(pet_head_, "checkbox");
		checbox_->setTag(i);
		checbox_->addTouchEventListener(this, SEL_TouchEvent(&CPetUI::clickCheckBox));

		Text* qianghua_lv_ = (Text*)Helper::seekWidgetByName(pet_head_, "qianghua_lv");
		qianghua_lv_->enableOutline( Color4B(1,46,13,255) ,2);

		Text* lv_ = (Text*)Helper::seekWidgetByName(pet_head_, "lv");
		qianghua_lv_->enableOutline( Color4B(0,0,0,255) ,2);

		if (i == 0)
		{
			checbox_->setSelectedState(true);
			clickCheckBox(checbox_,TOUCH_EVENT_ENDED);
		}

		m_listView_pet->pushBackCustomItem(pet_head_);
	}

}

void CPetUI::clickCheckBox(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		int index_ = ((CheckBox*)pSender)->getTag();	// 科技节点在列表中的index

		if (m_select_pet_item != nullptr) 
		{
			m_select_pet_item->setSelectedState(false); // 设置为不可点击的状态
		}

		if(m_select_pet_item == (CheckBox*)pSender) // 点击的就是当前选择的科技节点
		{
			CCLOG("not update\n");
		}else
		{
			m_select_pet_item =  ((CheckBox*)pSender);
			//updateRightPanel(index_);
			CCLOG("update\n");
		}
	}
}

void CPetUI::onOpen()
{

}

void CPetUI::onClose()
{

}

void CPetUI::clickBackButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->destroyUI(this);
	}
}

void CPetUI::clickTianshuButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		//  点击了天书
	}
}

void CPetUI::clickQianghuaButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		//  点击了强化
	}
}

void CPetUI::clickSwitch(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		int Tag_ = dynamic_cast<Button*>(pSender)->getTag();

		switch (Tag_)
		{
		case 1001:
			m_attribute_panel->setVisible(true);
			m_qianghua_panel->setVisible(false);

			m_Tianshu_btn->setTouchEnabled(true);
			m_Qianghua_btn->setTouchEnabled(true);

			m_Qianghua_btn_2->setTouchEnabled(false);
			m_BackButton_btn_2->setTouchEnabled(false);

			break;
		case 1002:
			m_attribute_panel->setVisible(false);
			m_qianghua_panel->setVisible(true);
			 
			m_Tianshu_btn->setTouchEnabled(false);
			m_Qianghua_btn->setTouchEnabled(false);

			m_Qianghua_btn_2->setTouchEnabled(true);
			m_BackButton_btn_2->setTouchEnabled(true);

			break;
		default:
			break;
		}
	}
}
