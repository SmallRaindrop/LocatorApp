#include "MissionUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "GameScene/GameUILayer.h"
#include "Net/NetDispatcher.h"
#include "Common/DataPool.h"
#include "GameScene/TaskMgr.h"

CMissionUI::CMissionUI()
	:GameUI(IDU_MissionlUI,JsonFile_MissionUI)
{
	m_select_type_item = nullptr;
	m_mission_vec.clear();
}

CMissionUI::~CMissionUI()
{
	m_select_type_item = nullptr;
	m_mission_vec.clear();
}

bool CMissionUI::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());

		Button *pCloseBtn = (Button*)Helper::seekWidgetByName(m_pWidget, "close_btn");
		BREAK_IF(pCloseBtn==NULL);
		pCloseBtn->setButtonSpriteGray();
		pCloseBtn->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickCloseButton));

		m_task_1_list = (ListView*)(Helper::seekWidgetByName(m_pWidget, "task_list_1"));
		m_pSlider[0] = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pWidget, "task_slider_1"));
		m_pSlider[0]->setList(m_task_1_list, Slider::ListType::LISTVIEW_TYPE);

		m_task_2_list = (ListView*)(Helper::seekWidgetByName(m_pWidget, "task_list_2"));
		m_pSlider[1] = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pWidget, "task_slider_2"));
		m_pSlider[1]->setList(m_task_2_list, Slider::ListType::LISTVIEW_TYPE);

		m_task_3_list = (ListView*)(Helper::seekWidgetByName(m_pWidget, "task_list_3"));
		m_pSlider[2] = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pWidget, "task_slider_3"));
		m_pSlider[2]->setList(m_task_3_list, Slider::ListType::LISTVIEW_TYPE);

		m_mission_type_1_item = (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "checkbox_1"));
		m_mission_type_1_item->setTag(1);
		m_mission_type_1_item->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickCheckBox));

		m_mission_type_2_item = (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "checkbox_2"));
		m_mission_type_2_item->setTag(2);
		m_mission_type_2_item->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickCheckBox));

		m_mission_type_3_item = (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "checkbox_3"));
		m_mission_type_3_item->setTag(3);
		m_mission_type_3_item->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickCheckBox));

		juqing_label = (Text*)Helper::seekWidgetByName(m_pWidget, "juqing_label");
		juqing_label->enableOutline(Color4B::BLACK,1);
		juqing_label->setColor(Color3B(112,128,144));
		
		shangjin_label = (Text*)Helper::seekWidgetByName(m_pWidget, "shangjin_label");
		shangjin_label->enableOutline(Color4B::BLACK,1);
		shangjin_label->setColor(Color3B(112,128,144));
		
		chongtu_label = (Text*)Helper::seekWidgetByName(m_pWidget, "chongtu_label");
		chongtu_label->enableOutline(Color4B::BLACK,1);
		chongtu_label->setColor(Color3B(112,128,144));

		m_mission_type_1_item->setSelectedState(true);
		clickCheckBox(m_mission_type_1_item,TOUCH_EVENT_ENDED);
		
		return true;
	} while (0);

	return false;
}

void CMissionUI::onOpen()
{
	m_mission_vec.clear();
	updateMissionList1();
	updateMissionList2();
	updateMissionList3();
	updateCheckBox();
}

// 点击任务分类选项卡
void CMissionUI::clickCheckBox(Ref* pSender, TouchEventType type) 
{
	if(TOUCH_EVENT_ENDED == type)
	{
		int type_id_ = ((CheckBox*)pSender)->getTag();	// 1剧情 2赏金 3冲突

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
			switch (type_id_)
			{
			case 1:
				m_task_1_list->setVisible(true);
				m_task_1_list->setEnabled(true);
				
				m_pSlider[0]->setVisible(true);
				m_pSlider[0]->setEnabled(true);

				juqing_label->setColor(Color3B(222,209,164));
				
				m_pSlider[1]->setVisible(false);
				m_pSlider[1]->setEnabled(false);
				
				m_task_2_list->setVisible(false);
				m_task_2_list->setEnabled(false);
				
				shangjin_label->setColor(Color3B(112,128,144));
				
				m_pSlider[2]->setVisible(false);
				m_pSlider[2]->setEnabled(false);
				
				m_task_3_list->setVisible(false);
				m_task_3_list->setEnabled(false);
				
				chongtu_label->setColor(Color3B(112,128,144));
				break;
			case 2:
				m_task_1_list->setVisible(false);
				m_task_1_list->setEnabled(false);

				m_pSlider[0]->setVisible(false);
				m_pSlider[0]->setEnabled(false);

				juqing_label->setColor(Color3B(112,128,144));

				m_task_2_list->setVisible(true);
				m_task_2_list->setEnabled(true);

				m_pSlider[1]->setVisible(true);
				m_pSlider[1]->setEnabled(true);

				shangjin_label->setColor(Color3B(222,209,164));

				m_task_3_list->setVisible(false);
				m_task_3_list->setEnabled(false);
				
				m_pSlider[2]->setVisible(false);
				m_pSlider[2]->setEnabled(false);

				chongtu_label->setColor(Color3B(112,128,144));
				break;
			case 3:
				m_task_1_list->setVisible(false);
				m_task_1_list->setEnabled(false);

				m_pSlider[0]->setVisible(false);
				m_pSlider[0]->setEnabled(false);

				juqing_label->setColor(Color3B(112,128,144));

				m_task_2_list->setVisible(false);
				m_task_2_list->setEnabled(false);
				
				m_pSlider[1]->setVisible(false);
				m_pSlider[1]->setEnabled(false);

				shangjin_label->setColor(Color3B(112,128,144));

				m_task_3_list->setVisible(true);
				m_task_3_list->setEnabled(true);
				
				m_pSlider[2]->setVisible(true);
				m_pSlider[2]->setEnabled(true);
				
				chongtu_label->setColor(Color3B(222,209,164));
				break;
			default:
				break;
			}
			CCLOG("update\n");
		}
	}
}

Widget*	CMissionUI::createMissionItem()
{
	auto node = GUIReader::getInstance()->widgetFromJsonFile("assets/ui/MissionItem.json");
	return node;
}

void CMissionUI::clickCloseButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

void CMissionUI::clickGoButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		// 点击了前往按钮
		int go_id_ = ((CheckBox*)pSender)->getTag();	// 前往的ID
		Task *pTask = gTaskManager->GetTask(go_id_);
		if (pTask!=NULL)
		{
			pTask->GoToTarget(TS_NOUSE);	// TS_NOUSE == 当前阶段目标
			clickCloseButton(NULL, TOUCH_EVENT_ENDED);
		}else
		{
			LOGE("gTaskManager->GetTask(%d)failed.",go_id_);
		}	
	}
}

void CMissionUI::clickGetButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		// 点击了领取按钮
		int get_id_ = ((CheckBox*)pSender)->getTag();	// 领取的任务ID
		pk::C2GS_SubmitTask cmd = {get_id_, 0, 0, -1};
		cmd.Send(gNetSocket);
	}
}

void CMissionUI::updateMissionList1()
{
	auto task_ = gTaskManager->GetAllTasksOngoing();
	m_task_1_list->removeAllItems();

	for (size_t i =0;i<task_.size();i++)
	{
		auto one_mission_ = task_[i];
		if (one_mission_->GetType() != 5 && one_mission_->GetType() != 2)
		{
			continue;
		}
		int mission_id_ = one_mission_->GetID();
		auto m_mission_item_temp_ = createMissionItem();
		m_mission_item_temp_->setTag(mission_id_);
		auto mission_title_label_ = (Text*)Helper::seekWidgetByName(m_mission_item_temp_, "title_label");
		mission_title_label_->setColor(Color3B(56,241,13));
		mission_title_label_->setText(one_mission_->GetData()->title);
		auto mission_content_label_ = (Text*)Helper::seekWidgetByName(m_mission_item_temp_, "content_label");
		mission_content_label_->setText(one_mission_->GetData()->targetcontext);

		auto mission_go_btn_ = (Button*)Helper::seekWidgetByName(m_mission_item_temp_, "go_btn");
		mission_go_btn_->setTag(mission_id_);
		if (one_mission_->GetCurStage() == TS_TURNIN)
		{
			mission_go_btn_->setTitleText(STR_Btn_Text_Get);
			mission_go_btn_->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickGetButton));
		}else
		{
			mission_go_btn_->setTitleText(STR_Btn_Text_Go);
			mission_go_btn_->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickGoButton));
		}

		m_task_1_list->pushBackCustomItem(m_mission_item_temp_);
		m_mission_vec.push_back(m_mission_item_temp_);
	}
}

void CMissionUI::updateMissionList2()
{
	auto task_ = gTaskManager->GetAllTasksOngoing();
	m_task_2_list->removeAllItems();

	for (size_t i =0;i<task_.size();i++)
	{
		auto one_mission_ = task_[i];
		if (one_mission_->GetType() != 6)
		{
			continue;
		}
		int mission_id_ = one_mission_->GetID();
		auto m_mission_item_temp_ = createMissionItem();
		m_mission_item_temp_->setTag(mission_id_);
		auto mission_title_label_ = (Text*)Helper::seekWidgetByName(m_mission_item_temp_, "title_label");
		mission_title_label_->setColor(Color3B(56,241,13));
		mission_title_label_->setText(one_mission_->GetData()->title);
		auto mission_content_label_ = (Text*)Helper::seekWidgetByName(m_mission_item_temp_, "content_label");
		mission_content_label_->setText(one_mission_->GetData()->targetcontext);

		auto mission_go_btn_ = (Button*)Helper::seekWidgetByName(m_mission_item_temp_, "go_btn");
		mission_go_btn_->setTag(mission_id_);
		if (one_mission_->GetCurStage() == TS_TURNIN)
		{
			mission_go_btn_->setTitleText(STR_Btn_Text_Get);
			mission_go_btn_->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickGetButton));
		}else
		{
			mission_go_btn_->setTitleText(STR_Btn_Text_Go);
			mission_go_btn_->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickGoButton));
		}

		m_task_2_list->pushBackCustomItem(m_mission_item_temp_);
		m_mission_vec.push_back(m_mission_item_temp_);
	}
}

void CMissionUI::updateMissionList3()
{
	auto task_ = gTaskManager->GetAllTasksOngoing();
	m_task_3_list->removeAllItems();

	for (size_t i =0;i<task_.size();i++)
	{
		auto one_mission_ = task_[i];
		if (one_mission_->GetType() != 7)
		{
			continue;
		}
		int mission_id_ = one_mission_->GetID();
		auto m_mission_item_temp_ = createMissionItem();
		m_mission_item_temp_->setTag(mission_id_);
		auto mission_title_label_ = (Text*)Helper::seekWidgetByName(m_mission_item_temp_, "title_label");
		mission_title_label_->setColor(Color3B(56,241,13));
		mission_title_label_->setText(one_mission_->GetData()->title);
		auto mission_content_label_ = (Text*)Helper::seekWidgetByName(m_mission_item_temp_, "content_label");
		mission_content_label_->setText(one_mission_->GetData()->targetcontext);

		auto mission_go_btn_ = (Button*)Helper::seekWidgetByName(m_mission_item_temp_, "go_btn");
		mission_go_btn_->setTag(mission_id_);
		if (one_mission_->GetCurStage() == TS_TURNIN)
		{
			mission_go_btn_->setTitleText(STR_Btn_Text_Get);
			mission_go_btn_->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickGetButton));
		}else
		{
			mission_go_btn_->setTitleText(STR_Btn_Text_Go);
			mission_go_btn_->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickGoButton));
		}

		m_task_3_list->pushBackCustomItem(m_mission_item_temp_);
		m_mission_vec.push_back(m_mission_item_temp_);
	}
}

void CMissionUI::updateCheckBox()
{

}

//  根据任务id更新单个任务的状态
void CMissionUI::updateMission(int mission_id)		
{
	for (size_t i = 0;i< m_mission_vec.size();i++)
	{
		if (m_mission_vec[i]->getTag() == mission_id)
		{
			auto mission_go_btn_ = (Button*)Helper::seekWidgetByName(m_mission_vec[i], "go_btn");
			auto task_ =  gTaskManager->GetTaskOngoing(mission_id);
			if (task_->GetCurStage() == TS_TURNIN)
			{
				mission_go_btn_->setTitleText(STR_Btn_Text_Get);
				mission_go_btn_->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickGetButton));
			}else
			{
				mission_go_btn_->setTitleText(STR_Btn_Text_Go);
				mission_go_btn_->addTouchEventListener(this, SEL_TouchEvent(&CMissionUI::clickGoButton));
			}
		}
	}
}
