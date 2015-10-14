/****************************************************************************
 任务系统UI
 李阳
 2015-8-24
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"

class CMissionUI : public GameUI
{
public:
	CMissionUI();
	~CMissionUI();

	bool			onInit();
	void			onOpen();

	CREATE_FUNC(CMissionUI);
public:
	Widget*			createMissionItem();						
	void			updateMissionList1();					 // 更新右侧任务列表1
	void			updateMissionList2();					 // 更新右侧任务列表2
	void			updateMissionList3();					 // 更新右侧任务列表3
	void			updateCheckBox();						 // 更新左侧任务分类选项卡
	void			updateMission(int mission_id);			//  根据任务id更新单个任务的状态


	void			clickCheckBox(Ref*, TouchEventType);	 // 点击任务的分类checkbox

	void			clickCloseButton(Ref*, TouchEventType);
	void			clickGoButton(Ref*, TouchEventType);     // 点击了前往按钮
	void			clickGetButton(Ref*, TouchEventType);     // 点击了领取按钮
private:
	ListView*					m_task_1_list;	// 类型1的任务列表
	ListView*					m_task_2_list;	// 类型2的任务列表
	ListView*					m_task_3_list;	// 类型3的任务列表
	Slider*					    m_pSlider[3];   //滑块

	CheckBox*					m_mission_type_1_item; // 任务类型1
	CheckBox*					m_mission_type_2_item; // 任务类型2
	CheckBox*					m_mission_type_3_item; // 任务类型3

	CheckBox*					m_select_type_item;    // 选择的任务类型

	Text*						juqing_label;
	Text*						shangjin_label;
	Text*						chongtu_label;

	vector<Widget*>				m_mission_vec;	// 所有已接的任务

public:
};

