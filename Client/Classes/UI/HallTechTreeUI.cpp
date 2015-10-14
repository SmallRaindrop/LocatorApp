#include "HallTechTreeUI.h"
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
#include "HallTechUI.h"

CHallTechTreeUI::CHallTechTreeUI()
	:GameUI(IDU_HallTechTreeUI,JsonFile_HallTechTreeUI)
{
	m_select_node_item = nullptr;
	m_index = 0;
}

CHallTechTreeUI::~CHallTechTreeUI()
{
	unscheduleUpdate();
	m_select_node_item = nullptr;
	m_tree_panel->removeFromParent();
}

bool CHallTechTreeUI::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());

		Button *pBack_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "back_btn");
		BREAK_IF(pBack_btn==NULL);
		pBack_btn->setButtonSpriteGray();
		pBack_btn->addTouchEventListener(this, SEL_TouchEvent(&CHallTechTreeUI::clickBackButton));

		// 升级按钮
		m_upgrade_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "upgrade_btn");
		BREAK_IF(m_upgrade_btn==NULL);
		m_upgrade_btn->addTouchEventListener(this, SEL_TouchEvent(&CHallTechTreeUI::clickUpgradeButton));
		
		// 升级时间
		m_time_text = (Text*)Helper::seekWidgetByName(m_pWidget, "time_text");
		m_time_text->setVisible(false);

		m_name_text = (Text*)Helper::seekWidgetByName(m_pWidget, "name_text");
		m_des_text = (Text*)Helper::seekWidgetByName(m_pWidget, "des_text");
		m_need_text = (Text*)Helper::seekWidgetByName(m_pWidget, "need_font_text");

		Layout* tree_panel_ = (Layout*)Helper::seekWidgetByName(m_pWidget, "tree_panel");
		
		m_listView = (ListView*)Helper::seekWidgetByName(m_pWidget, "listView");
		m_listView->setItemsMargin(20);
		m_scrollView = (ScrollView*)Helper::seekWidgetByName(m_pWidget, "scrollView");
		m_tree_panel = (Layout*)tree_panel_->clone();
		m_tree_panel->setPosition(Point(tree_panel_->getPositionX(), 0));
		m_scrollView->getInnerContainer()->addChild(m_tree_panel);
		tree_panel_->removeFromParent();
			
		upgrade_btn_ = (Button*)Helper::seekWidgetByName(m_pWidget, "upgrade_btn");
		upgrade_btn_->addTouchEventListener(this, SEL_TouchEvent(&CHallTechTreeUI::clickUpgradeButton));
		upgrade_btn_->setButtonSpriteGray();

		//进度条背景
		m_bar_bg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWidget, "img_progress_bg"));
		m_bar_bg->setVisible(false);
		//进度条 
		m_bar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(m_pWidget, "progressBar"));
		m_bar->setPercent(0.0f);

		return true;
	} while (0);

	return false;
}

void CHallTechTreeUI::onOpen()
{
	UpdateAll();
}

void CHallTechTreeUI::UpdateAll()
{
	Widget* basic_icon_ = gCtrlAllocator->LoadCtrl("Panel_halltechtree_icon");

	for (int i = 1;i<=23;i++)
	{
		m_tree_panel->removeChildByTag(i);
	}

	m_select_node_item = nullptr;

	for(int i = 1;i<=23;i++)
	{
		HallTechCfg* temp_cfg_ =  HallTechData.get(i);

		ImageView* temp_img_ = (ImageView*)Helper::seekWidgetByName(m_pWidget,FORMAT_TO_STRING("img_%d",i));
		temp_img_->setVisible(false);
		Point temp_point_ = temp_img_->getPosition();

		Widget* temp_icon_ = basic_icon_->clone();
		temp_icon_->setPosition(temp_point_);
		temp_icon_->setTag(i);
		m_tree_panel->addChild(temp_icon_);

		Text* temp_name_ = (Text*)Helper::seekWidgetByName(temp_icon_,"label_name");
		Text* temp_level_ = (Text*)Helper::seekWidgetByName(temp_icon_,"label_level");

		temp_name_->setText(temp_cfg_->name);
		int cur_level_ = gHero->GetHallTechManager().GetLevelByCfgID(i);
		int max_level_ = temp_cfg_->max_lv;
		temp_level_->setText( FORMAT_TO_STRING("%d/%d",cur_level_,max_level_) );

		CheckBox* temp_checkbox_ = (CheckBox*)Helper::seekWidgetByName(temp_icon_,"checkbox");
		temp_checkbox_->setTag(i);
		temp_checkbox_->addTouchEventListener(this, SEL_TouchEvent(&CHallTechTreeUI::clickCheckBox));

		ImageView* temp_icon_bg_ = (ImageView*)Helper::seekWidgetByName(temp_icon_,"img_bg");
		ShaderSprite* temp_spr_ = ShaderSprite::create();

		if (isUnlockHallTech(i,cur_level_))
		{
			temp_spr_->setTexture("assets/ui/legion/ico_juntuanjianshetubiaotidai.png",1);
		}else
		{
			temp_spr_->setTexture("assets/ui/legion/ico_juntuanjianshetubiaotidai.png",0.5);
		}

		if (cur_level_>=max_level_)
		{
			temp_spr_->setGrayRate(1);
		}

		temp_spr_->setAnchorPoint(Point(0,0));
		temp_spr_->setPosition(temp_icon_bg_->getPosition());   
		temp_icon_->addChild(temp_spr_,-1);

		temp_icon_bg_->removeFromParent();

		if (m_index == 0)
		{
			if (i == 1)
			{
				temp_checkbox_->setSelectedState(true);
				clickCheckBox(temp_checkbox_,TOUCH_EVENT_ENDED);
			}
		}else
		{
			if (i == m_index)
			{
				temp_checkbox_->setSelectedState(true);
				clickCheckBox(temp_checkbox_,TOUCH_EVENT_ENDED);
			}
		}

		if (i!=1)
		{
			temp_icon_->setScale(0.8f);
		}

	}
}

void CHallTechTreeUI::onClose()
{

}

void CHallTechTreeUI::clickBackButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->destroyUI(this);
	}
}

void CHallTechTreeUI::clickUpgradeButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		int index_ = ((CheckBox*)pSender)->getTag();
		HallTechCfg* temp_cfg_ =  HallTechData.get(index_);
		
		int item_id_ = temp_cfg_->item;
		int need_item_number_ = GetHallItemNumberByLevel(index_,gHero->GetHallTechManager().GetLevelByCfgID(index_));
		int have_item_number_ = gGridsManager->getItemCountByDataID(emGrids_BagMaterial,item_id_);

		int need_gold = GetUpgradeGoldByLevel( index_, gHero->GetHallTechManager().GetLevelByCfgID(index_) );
		if (gHero->GetMoney() < need_gold)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_gold_not_enough);
			return;
		}
		if (have_item_number_ < need_item_number_)
		{
			gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_item_not_enough);
			return;
		}

		pk::C2GS_HallTechLvUp_Req cmd;
		cmd.id = index_;
		cmd.Send(gNetSocket);

	}
}

void CHallTechTreeUI::clickCheckBox(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		int index_ = ((CheckBox*)pSender)->getTag();	// 科技节点在列表中的index

		if (m_select_node_item != nullptr) 
		{
			m_select_node_item->setSelectedState(false); // 设置为不可点击的状态
		}

		if(m_select_node_item == (CheckBox*)pSender) // 点击的就是当前选择的科技节点
		{
			CCLOG("not update\n");
		}else
		{
			m_select_node_item =  ((CheckBox*)pSender);
			m_index = index_;
			updateRightPanel(index_);
			CCLOG("update\n");
		}
	}
}

void CHallTechTreeUI::update(float dt)
{
	if (gHero->GetHallTechManager().GetUpgradeTime(m_index) <=0)
	{
		upgrade_btn_->setVisible(true);
		m_time_text->setVisible(false);
		m_bar_bg->setVisible(false);
		unscheduleUpdate();
	}
	
	m_time_text->setText( SecondsToTime(gHero->GetHallTechManager().GetUpgradeTime(m_index),2) );
	m_bar->setPercent(gHero->GetHallTechManager().GetUpgradeTimePercent(m_index));
}

void CHallTechTreeUI::updateRightPanel(int index)
{
	unscheduleUpdate();
	m_listView->removeAllItems();
	HallTechCfg* temp_cfg_ =  HallTechData.get(index);

	Text *name_text_ = (Text*)Helper::seekWidgetByName(m_pWidget, "name_text");
	Text *des_text_ = (Text*)Helper::seekWidgetByName(m_pWidget, "des_text");
	upgrade_btn_->setTag(index);

	if (isUnlockHallTech(index,gHero->GetHallTechManager().GetLevelByCfgID(index)))
	{
		upgrade_btn_->setTouchEnabled(true);
		upgrade_btn_->setButtonShowType(Normal_TYPE);
	}else
	{
		upgrade_btn_->setTouchEnabled(false);
		upgrade_btn_->setButtonShowType(Disable_TYPE);
	}

	if(GetHallUpgradeState(index))
	{
		upgrade_btn_->setVisible(false);
		m_time_text->setVisible(true);
		m_time_text->setText( SecondsToTime(gHero->GetHallTechManager().GetUpgradeTime(index),2) );
		m_bar_bg->setVisible(true);
		m_bar->setPercent(gHero->GetHallTechManager().GetUpgradeTimePercent(m_index));
		scheduleUpdate();
	}else
	{
		upgrade_btn_->setVisible(true);
		m_time_text->setVisible(false);
		m_bar_bg->setVisible(false);
	}

	name_text_->setText(temp_cfg_->name);
	des_text_->setText(GetHallDesByLevel(index,gHero->GetHallTechManager().GetLevelByCfgID(index)));

	vector<Text*> temp_text_vec_ = GetUnlockHallTechText(index,gHero->GetHallTechManager().GetLevelByCfgID(index));
	for (size_t i = 0;i<temp_text_vec_.size();++i)
	{
		m_listView->pushBackCustomItem(temp_text_vec_[i]);
	}

	Widget* need_gold_ = gCtrlAllocator->LoadCtrl("Panel_halltechtree_need_gold");
	Widget* temp_need_gold_ = need_gold_->clone();

	Text *number_text_ = (Text*)Helper::seekWidgetByName(temp_need_gold_, "label_gold");
	int need_gold = GetUpgradeGoldByLevel( index, gHero->GetHallTechManager().GetLevelByCfgID(index) );
	number_text_->setText( FORMAT_TO_STRING("%d",need_gold));
	if (gHero->GetMoney() >= need_gold)
	{
		number_text_->setColor(Color3B(222,209,164));
	}else
	{
		number_text_->setColor(Color3B::RED);
	}
	
	m_listView->pushBackCustomItem(temp_need_gold_);

	Widget* need_item_ = gCtrlAllocator->LoadCtrl("Panel_halltechtree_need_item");
	Widget* temp_need_item_ = need_item_->clone();
	
	ImageView *item_img_bg_ = (ImageView*)Helper::seekWidgetByName(temp_need_item_, "img_item");

	Text *label_name_ = (Text*)Helper::seekWidgetByName(temp_need_item_, "label_name");
	Text *label_have_ = (Text*)Helper::seekWidgetByName(temp_need_item_, "label_have");
	Text *label_need_ = (Text*)Helper::seekWidgetByName(temp_need_item_, "label_need");
	
	int item_id_ = temp_cfg_->item;
	int need_item_number_ = GetHallItemNumberByLevel(index,gHero->GetHallTechManager().GetLevelByCfgID(index));
	int have_item_number_ = gGridsManager->getItemCountByDataID(emGrids_BagMaterial,item_id_);
	
	ImageView* item_img_ = ImageView::create(ICON_PATH_ITEM+ItemData.get(item_id_)->icon);
	item_img_bg_->addChild(item_img_);
	item_img_->setAnchorPoint(Point::ANCHOR_MIDDLE);
	item_img_->setScale(0.7);
	item_img_->setPosition(Point(item_img_bg_->getContentSize().width/2,item_img_bg_->getContentSize().height/2));

	label_name_->setText(ItemData.get(item_id_)->name);
	label_have_->setText(FORMAT_TO_STRING("%d",have_item_number_));
	label_need_->setText(FORMAT_TO_STRING("/%d",need_item_number_));
	label_need_->setPositionX(label_have_->getPositionX()+label_have_->getContentSize().width);

	if (have_item_number_>=need_item_number_)
	{
		label_have_->setColor(Color3B::WHITE);
		label_need_->setColor(Color3B::WHITE);
	}else
	{
		label_have_->setColor(Color3B::RED);
		label_need_->setColor(Color3B::RED);
	}

	m_listView->pushBackCustomItem(temp_need_item_);

}