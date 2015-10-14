#include "GodDeviceUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "GameScene/GameUILayer.h"
#include "Net/NetDispatcher.h"
#include "Common/DataPool.h"
#include "GameScene/Hero.h"
#include "MessageBoxUI.h"
#include "Common/CommonDef.h"
#include "ShaderSprite.h"

CGodDeviceUI::CGodDeviceUI()
	:GameUI(IDU_GodDeviceUI,JsonFile_GodDeviceUI)
{
	m_select_type_item = nullptr;
	m_indexToGodCfgId_vec.clear();
}

CGodDeviceUI::~CGodDeviceUI()
{
	m_select_type_item = nullptr;
	m_indexToGodCfgId_vec.clear();
	m_skill_des_vec.clear();
	m_skill_name_vec.clear();
	m_skill_icon_vec.clear();
}

bool CGodDeviceUI::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());

		Button *pCloseBtn = (Button*)Helper::seekWidgetByName(m_pWidget, "close_btn");
		BREAK_IF(pCloseBtn==NULL);
		pCloseBtn->setButtonSpriteGray();
		pCloseBtn->addTouchEventListener(this, SEL_TouchEvent(&CGodDeviceUI::clickCloseButton));


		//  装备按钮
		m_dress_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "dress_btn");
		BREAK_IF(m_dress_btn==NULL);
		m_dress_btn->setButtonSpriteGray();
		m_dress_btn->addTouchEventListener(this, SEL_TouchEvent(&CGodDeviceUI::clickDressButton));
		
		m_name_label = (Text*)Helper::seekWidgetByName(m_pWidget, "att_name_text");
		m_des_label = (Text*)Helper::seekWidgetByName(m_pWidget, "att_des_text");

		Text* att_text_1 = (Text*)Helper::seekWidgetByName(m_pWidget, "att_text_1");
		att_text_1->setColor(Color3B(222,209,164));
		Text* att_text_2 = (Text*)Helper::seekWidgetByName(m_pWidget, "att_text_2");
		att_text_2->setColor(Color3B(222,209,164));
		Text* att_text_3 = (Text*)Helper::seekWidgetByName(m_pWidget, "att_text_3");
		att_text_3->setColor(Color3B(222,209,164));
		Text* att_text_4 = (Text*)Helper::seekWidgetByName(m_pWidget, "att_text_4");
		att_text_4->setColor(Color3B(222,209,164));

		m_attr_label_1 = (Text*)Helper::seekWidgetByName(m_pWidget, "att_text_number_1");
		m_attr_label_1->setColor(Color3B(47,245,1));
		m_attr_label_2 = (Text*)Helper::seekWidgetByName(m_pWidget, "att_text_number_2");
		m_attr_label_2->setColor(Color3B(47,245,1));
		m_attr_label_3 = (Text*)Helper::seekWidgetByName(m_pWidget, "att_text_number_3");
		m_attr_label_3->setColor(Color3B(47,245,1));
		m_attr_label_4 = (Text*)Helper::seekWidgetByName(m_pWidget, "att_text_number_4");
		m_attr_label_4->setColor(Color3B(47,245,1));


		m_skill_icon_bg_1 = (ImageView*)Helper::seekWidgetByName(m_pWidget, "skill_icon_1");
		m_skill_icon_bg_2 = (ImageView*)Helper::seekWidgetByName(m_pWidget, "skill_icon_2");
		m_skill_icon_bg_3 = (ImageView*)Helper::seekWidgetByName(m_pWidget, "skill_icon_3");
		m_skill_icon_bg_4 = (ImageView*)Helper::seekWidgetByName(m_pWidget, "skill_icon_4");

		m_skill_icon_bg_vec.push_back(m_skill_icon_bg_1);
		m_skill_icon_bg_vec.push_back(m_skill_icon_bg_2);
		m_skill_icon_bg_vec.push_back(m_skill_icon_bg_3);
		m_skill_icon_bg_vec.push_back(m_skill_icon_bg_4);

		m_skill_icon_1 = ShaderSprite::create();
		m_skill_icon_1->setPosition(m_skill_icon_bg_1->getPosition());

		m_skill_icon_2 = ShaderSprite::create();
		m_skill_icon_2->setPosition(m_skill_icon_bg_2->getPosition());

		m_skill_icon_3 = ShaderSprite::create();
		m_skill_icon_3->setPosition(m_skill_icon_bg_3->getPosition());

		m_skill_icon_4 = ShaderSprite::create();
		m_skill_icon_4->setPosition(m_skill_icon_bg_4->getPosition());

		m_skill_icon_vec.push_back(m_skill_icon_1);
		m_skill_icon_vec.push_back(m_skill_icon_2);
		m_skill_icon_vec.push_back(m_skill_icon_3);
		m_skill_icon_vec.push_back(m_skill_icon_4);

		m_skill_name_1 = (Text*)Helper::seekWidgetByName(m_pWidget, "skill_name_text_1");
		m_skill_name_1->setColor(Color3B(222,209,164));
		m_skill_name_2 = (Text*)Helper::seekWidgetByName(m_pWidget, "skill_name_text_2");
		m_skill_name_2->setColor(Color3B(222,209,164));
		m_skill_name_3 = (Text*)Helper::seekWidgetByName(m_pWidget, "skill_name_text_3");
		m_skill_name_3->setColor(Color3B(222,209,164));
		m_skill_name_4 = (Text*)Helper::seekWidgetByName(m_pWidget, "skill_name_text_4");
		m_skill_name_4->setColor(Color3B(222,209,164));

		m_skill_name_vec.push_back(m_skill_name_1);
		m_skill_name_vec.push_back(m_skill_name_2);
		m_skill_name_vec.push_back(m_skill_name_3);
		m_skill_name_vec.push_back(m_skill_name_4);

		m_skill_des_1 = (Text*)Helper::seekWidgetByName(m_pWidget, "skill_des_text_1");
		m_skill_des_2 = (Text*)Helper::seekWidgetByName(m_pWidget, "skill_des_text_2");
		m_skill_des_3 = (Text*)Helper::seekWidgetByName(m_pWidget, "skill_des_text_3");
		m_skill_des_4 = (Text*)Helper::seekWidgetByName(m_pWidget, "skill_des_text_4");

		m_skill_des_vec.push_back(m_skill_des_1);
		m_skill_des_vec.push_back(m_skill_des_2);
		m_skill_des_vec.push_back(m_skill_des_3);
		m_skill_des_vec.push_back(m_skill_des_4);

		//  神器类型列表
		m_type_list = (ListView*)Helper::seekWidgetByName(m_pWidget, "tab_list");
		m_type_list->setItemsMargin(10);

		ImageView* temp_bg_img_ = (ImageView*)Helper::seekWidgetByName(m_pWidget, "bg_img");
		temp_bg_img_->addChild(m_skill_icon_1);
		temp_bg_img_->addChild(m_skill_icon_2);
		temp_bg_img_->addChild(m_skill_icon_3);
		temp_bg_img_->addChild(m_skill_icon_4);

		updateGodDeviceList();

		return true;
	} while (0);

	return false;
}

void CGodDeviceUI::onOpen()
{
	updateGodDeviceList();
}

// 点击神器类型选项卡
void CGodDeviceUI::clickCheckBox(Ref* pSender, TouchEventType type) 
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
			updateGodDeviceData(index_);
			CCLOG("update\n");
		}
	}
}

Widget*	CGodDeviceUI::createTabItem()
{
	auto node = GUIReader::getInstance()->widgetFromJsonFile("assets/ui/GodDeviceTab.json");
	return node;
}

void CGodDeviceUI::clickCloseButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

void CGodDeviceUI::clickDressButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		int index_ = ((CheckBox*)pSender)->getTag();
		int godCfgId = m_indexToGodCfgId_vec[index_];
		auto GodDevice_ = gHero->GetGodDevice(godCfgId);
		string name_ = GodDevice_->GetGodName();
		CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,FORMAT_TO_STRING(STR_ChangeGodDevice_Text,name_.c_str()),[index_](bool type){
			if(type)
			{
				// 点击了装备按钮
				pk::C2GS_ChangeGodDevice cmd;
				cmd.index = index_;
				cmd.Send(gNetSocket);
			}
		},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
			this,NULL,CMessageBoxUI::Scene_Game);
	}
}

void CGodDeviceUI::updateGodDeviceList()
{
	m_select_type_item = nullptr;
	m_type_list->removeAllItems();
	m_indexToGodCfgId_vec.clear();

	GodDeviceManager& GetGodDeviceManager_ = gHero->GetGodDeviceManager();

	for (int i = 0;i<GetGodDeviceManager_.Count();i++)
	{
		auto GodDevice_ = GetGodDeviceManager_.GetDeviceList()[i];
		m_indexToGodCfgId_vec.push_back(GodDevice_->GetGodDataId());

		auto tab_ = createTabItem();
		auto checkbox_ = (CheckBox*)Helper::seekWidgetByName(tab_, "checkbox"); // 复选框
		checkbox_->setTag(i);
		checkbox_->addTouchEventListener(this, SEL_TouchEvent(&CGodDeviceUI::clickCheckBox));

		if (GodDevice_->GetGodIsDress() == 1) // 默认选中已装备的神器
		{
			checkbox_->setSelectedState(true);
			clickCheckBox(checkbox_,TOUCH_EVENT_ENDED);
		}
	
		auto img_bg_ = (ImageView*)Helper::seekWidgetByName(tab_, "img_bg");
		img_bg_->setVisible(false);
		if (GodDevice_->GetGodIsDress()==1)
		{
			img_bg_->setVisible(true);
		}
		auto title_label_ = (Text*)Helper::seekWidgetByName(tab_, "title_label");
		title_label_->setColor(Color3B(135,244,248));
		title_label_->setText(GodDevice_->GetGodName());

		m_type_list->pushBackCustomItem(tab_);
	}
}

void CGodDeviceUI::updateGodDeviceData(int index)
{
	for (int i = 0;i<4;++i)
	{
		m_skill_des_vec[i]->setVisible(false);
		m_skill_icon_vec[i]->setVisible(false);
		m_skill_name_vec[i]->setVisible(false);
		m_skill_icon_bg_vec[i]->setVisible(false);
	}

	int godCfgId = m_indexToGodCfgId_vec[index];
	auto GodDevice_ = gHero->GetGodDevice(godCfgId);
	auto GodSkillIdVec_ = GodDevice_->GetGodSkillIdVec();
	int refineLevel_ = GodDevice_->GetGodRefineLevel();					// 精炼等级
	int enhanceLevel_= GodDevice_->GetGodEnhanceLevel();				// 进阶等级

	m_dress_btn->setTag(index);

	if (GodDevice_->GetGodIsDress() == 1)
	{
		//m_dress_btn->setEnabled(false);
		m_dress_btn->setButtonShowType(Button_ShowType::Disable_TYPE);
		m_dress_btn->setTitleText(STR_Btn_Text_Dressed);
	}else
	{
		//m_dress_btn->setEnabled(true);
		m_dress_btn->setButtonShowType(Button_ShowType::Normal_TYPE);
		m_dress_btn->setTitleText(STR_Btn_Text_Dress);
	}

	m_name_label = (Text*)Helper::seekWidgetByName(m_pWidget, "att_name_text");
	m_name_label->setText(GodDevice_->GetGodName());

	m_des_label = (Text*)Helper::seekWidgetByName(m_pWidget, "att_des_text");
	m_des_label->setText(GodDevice_->GetGodDes());

	// 精炼加成配置表
	int hp_ = getEquipTotalAttribute(enhanceLevel_,refineLevel_,0,GodDevice_->m_all_attr_vec);
	//  生命
	char attr_str_1[1000];
	sprintf(attr_str_1,"%d",hp_);
	m_attr_label_1->setText(attr_str_1);

	// 魔法
	char attr_str_2[1000];
	sprintf(attr_str_2,"%d",getEquipTotalAttribute(enhanceLevel_,refineLevel_,1,GodDevice_->m_all_attr_vec));
	m_attr_label_2->setText(attr_str_2);

	//  护甲
	char attr_str_3[1000];
	sprintf(attr_str_3,"%d",getEquipTotalAttribute(enhanceLevel_,refineLevel_,2,GodDevice_->m_all_attr_vec));
	m_attr_label_3->setText(attr_str_3);
	
	// 移动速度
	char attr_str_4[1000];
	sprintf(attr_str_4,"%d",getEquipTotalAttribute(enhanceLevel_,refineLevel_,3,GodDevice_->m_all_attr_vec));
	m_attr_label_4->setText(attr_str_4);

	for (size_t i = 0;i<GodSkillIdVec_.size();++i)
	{
		SkillCfg* temp_pSkill_ = SkillData.get(GodSkillIdVec_[i]);

		m_skill_icon_vec[i]->setTexture(temp_pSkill_->icon,1);
		m_skill_icon_vec[i]->setScale(0.6f);

		if (gHero->IsSkillStudyed(temp_pSkill_->id))
		{
			m_skill_icon_vec[i]->setTexture(temp_pSkill_->icon,1);
		}else
		{
			m_skill_icon_vec[i]->setTexture(temp_pSkill_->icon,0.5);
		}

		m_skill_name_vec[i]->setText(temp_pSkill_->name);

		string temp_text_ = StringUtil::StringCut(temp_pSkill_->desc,100,"...");
		m_skill_des_vec[i]->setText(temp_text_);

		m_skill_des_vec[i]->setVisible(true);
		m_skill_icon_vec[i]->setVisible(true);
		m_skill_name_vec[i]->setVisible(true);
		m_skill_icon_bg_vec[i]->setVisible(true);
	}
}