#include "TaskUI.h"
#include "UIHelper.h"
#include "Net/pk_task.h"
#include "Net/NetDispatcher.h"
#include "GameScene/db.h"
#include "GameScene/Hero.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/GameDataManager.h"
#include "GameScene/TaskMgr.h"
#include "GameScene/GridsManager.h"
#include "CustomCtrl/ScrollList.h"



TaskUI:: TaskUI() : 
	GameUI(IDU_TASKUI,JSONFILE_TASKUI)
{
	m_nSelTaskID = 0;
}

TaskUI:: ~TaskUI()
{
}

bool TaskUI::onInit()
{
	if (!GameUI::onInit())
	{
		return false;
	}

	m_pListMain		= Helper::seekWidgetByName(m_pWidget, "Image_BG");
	m_pDetail		= Helper::seekWidgetByName(m_pWidget, "Image_Inner_Detail");
	Button *pClose	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Exit");
	Button *pGo		= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Go");
	m_nDetailPosX	= m_pDetail->getPositionX();
	m_pDetail->setPositionX(-10000);
	pClose->addTouchEventListener(this, SEL_TouchEvent(&TaskUI::clickExit));
	pGo->addTouchEventListener(this, SEL_TouchEvent(&TaskUI::clickGo));
	m_pCancelTask	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Task_Cancel");
	m_pCancelTask->addTouchEventListener(this, SEL_TouchEvent(&TaskUI::clickCancelTask));

	
	//Widget *pBoxesPanel = Helper::seekWidgetByName(m_pWidget, "Panel_Award");
	//Node *pParent = pBoxesPanel->getParent();
	//CGridArrayUI *pPackUI = CGridArrayUI::create(emGrids_TaskAward,0,GRIDS_SIZE_TASK,pBoxesPanel,true);
	//gGridsManager->attachUI(pPackUI, emGrids_TaskAward);
	//pParent->addChild(pPackUI);

	m_pTaskAward	= (Text*)Helper::seekWidgetByName(m_pWidget, "Label_Award");
	((Label*)m_pTaskAward->getVirtualRenderer())->disableEffect();
	Widget *pTargetHead= Helper::seekWidgetByName(m_pWidget, "Image_TargetHead");

	m_pTaskList = CScrollList::create(true, "CheckBox_2");
	m_pTaskList->setTouchEnabled(true);
	m_pTaskList->setSize(Size(180, 130));
	m_pTaskList->SetInterval(6);
	m_pTaskList->SetFontSize(18);
	m_pTaskList->SetTextAlign(TextHAlignment::LEFT);
	m_pTaskList->setPosition(Point(0, 0));
	m_pTaskList->setColor(Color3B(0xf6, 0xd7, 0xb1));
	m_pTaskList->SetSelTextColor(Color3B(0xff, 0xf9, 0xea));
	m_pTaskList->SetSelectEvent(this, SEL_SelListIndexEvent(&TaskUI::SelTask));
	m_pListMain->addChild(m_pTaskList);
	m_pListMain->setEnabled(false);

	m_pTaskDes = RichTextEx::create();
	m_pTaskDes->ignoreContentAdaptWithSize(false);
	m_pTaskDes->setSize(Size(660, 10));
	m_pTaskDes->SetFontSize(FontSize36);
	m_pTaskDes->setColor(Color3B(0x6e, 0x50, 0x3c));
	m_pTaskDes->SetLinkColor(Color3B::GREEN);
	m_pTaskDes->setPositionY(-66);
	pTargetHead->addChild(m_pTaskDes);

	m_pTaskBtn = (CheckBox*)Helper::seekWidgetByName(m_pWidget, "Task");
	m_pTaskTrace = RichTextEx::create();
	m_pTaskTrace->setPosition(Point(40, 145));
	m_pTaskTrace->setColor(Color3B(0xf6, 0xd7, 0xb1));
	m_pTaskTrace->SetLinkColor(Color3B::GREEN);
	m_pTaskTrace->SetFontSize(24);
	m_pListMain->addChild(m_pTaskTrace);
	m_pTaskTrace->addTouchEventListener(this, toucheventselector(TaskUI::clickTask));
	m_pTaskBtn->addEventListenerCheckBox(this, checkboxselectedeventselector(TaskUI::clickTaskBtn));

	return true;
}

void TaskUI::onOpen()
{
	updateTaskTrace();
	UpdateTask();
	clickExit(NULL, TOUCH_EVENT_ENDED);
}
void TaskUI::onClose()
{
	updateTaskTrace();
}

void TaskUI::clickExit(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		m_pDetail->setPositionX(-10000);
		m_pTaskList->UnSelected();
		m_nSelTaskID = 0;
	}
}

void TaskUI::clickTask(Ref *pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		if (m_pTraceTask)
		{
			m_pTraceTask->GoToTarget(TS_NOUSE);
		}
	}
}

void TaskUI::clickTaskBtn(Ref *pSender, CheckBoxEventType type)
{
	m_pListMain->setEnabled(CHECKBOX_STATE_EVENT_SELECTED == type);
}


void TaskUI::TraceTask(Task* pTask)
{
	m_pTraceTask = pTask;
	m_pTaskTrace->getParent()->setVisible(m_pTraceTask != NULL);

	if (m_pTraceTask == NULL)
	{
		return;
	}

	eTaskStage stage = TS_ACCEPT;
	if (pTask != gTaskManager->GetAcceptableMainTask())
	{
		stage = (gTaskManager->CanTaskBeFinished(pTask->GetID()) ? TS_TURNIN : TS_DO);
	}

	m_pTaskTrace->removeAllElements();
	/*
	if (stage == TS_DO)
	{
		m_pTaskTrace->ParseAndLayout(CCString::createWithFormat((pTask->GetName() + "(<C=255,0,80>%d</c>/<C=0,255,80>%d</c>)").c_str(), 
			pTask->GetTarget()->progress.curCnt, pTask->GetTarget()->progress.targetCnt)->getCString());
	}
	else
	{
		m_pTaskTrace->SetContent((pTask->GetName() + "%s").c_str(), arrText[stage]);
	}*/
	m_pTaskTrace->ParseAndLayout(pTask->GetName());

	m_pTaskTrace->formatText();
	m_pTaskTrace->setPositionX(m_pTaskTrace->getVirtualRendererSize().width / 2 + m_pTaskBtn->getSize().width/2 + 20);
}

void TaskUI::clickGo(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		Task *pTask = gTaskManager->GetTask(m_nSelTaskID);
		pTask->GoToTarget(TS_NOUSE);	// TS_NOUSE == 当前阶段目标

		clickExit(NULL, TOUCH_EVENT_ENDED);
		gCocosAudio->PlayEffect(108);
	}
}

void TaskUI::clickCancelTask(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		pk::C2GS_CannelTaskChain cmd = {gHero->GetId()};
		cmd.Send(gNetSocket);
		clickExit(NULL, TOUCH_EVENT_ENDED);
	}
}

void TaskUI::clickAccNPC(int nIndex, RichTextEx::Link_Data*)
{
	if (nIndex == 1)
	{
		// 寻路
		Task *pTask = gTaskManager->GetTaskOngoing(m_nSelTaskID);
		pTask->GoToTarget(TS_ACCEPT);
	}
}

void TaskUI::clickFinNPC(int nIndex, RichTextEx::Link_Data*)
{
	if (nIndex == 1)
	{
		// 寻路
		Task *pTask = gTaskManager->GetTaskOngoing(m_nSelTaskID);
		pTask->GoToTarget(TS_TURNIN);
	}
}

Color3B arrClr4TaskLink[] = {Color3B::RED, Color3B::BLUE, Color3B::GREEN, Color3B::YELLOW};

void TaskUI::SelTask(int nIndex, long long data)
{
	Task* pTask = gTaskManager->GetTask(int(data));

	if (pTask->GetCurStage() == TS_ACCEPT)
	{
		MapCfg *pMap1 = MapData.get(pTask->GetStage(TS_ACCEPT)->nMapID);
		m_pTaskDes->SetContent(GameString.get(220)->value.c_str(), pMap1->name.c_str(), pTask->GetStage(TS_ACCEPT)->strTargetName.c_str());
		m_pCancelTask->setEnabled(false);
	}
	else
	{
		m_pTaskDes->ParseAndLayout(pTask->GetManagedTargetString(pTask->GetCurStage()));
		m_pCancelTask->setEnabled(pTask->GetType() == 4);
	}
	m_pTaskDes->formatText();
	m_pTaskDes->setPositionX(m_pTaskDes->getVirtualRendererSize().width / 2);

	m_nSelTaskID = pTask->GetID();

	// 奖励
	string strAwardText;
	TaskAward *pAward = pTask->GetAward();
	int arrAward[] = {pAward->nExp, pAward->nHonour, pAward->nCoin, pAward->nCoinB};
	const char* arrAwardType[] = {GameString.get(243)->value.c_str(), GameString.get(244)->value.c_str(), GameString.get(226)->value.c_str(), GameString.get(227)->value.c_str()};
	for (int j = 0; j < 4; j++)
	{
		if (arrAward[j])
		{
			strAwardText += (CCString::createWithFormat("%s %d   ", arrAwardType[j], arrAward[j])->getCString());
		}
	}
	m_pTaskAward->setText(strAwardText);
	m_pDetail->setPositionX(m_nDetailPosX);

	//gGridsManager->removeAllGrids(emGrids_TaskAward);

	//size_t i = 0;
	//for (; i < pAward->vtrItems.size(); i++)
	//{
	//	gGridsManager->insertGrid(emGrids_TaskAward, i, pAward->vtrItems[i].pItem->id, pAward->vtrItems[i].nNum);
	//}

	//// 随机道具
	//if (pData->dropid != 0)
	//{
	//	gGridsManager->insertGrid(emGrids_TaskAward, i, 3000008, 1);
	//}
}

void TaskUI::UpdateTask()
{
	m_pTaskList->Clear();
	clickExit(NULL, TOUCH_EVENT_ENDED);

	string arrTaskType[] = {GameString.get(221)->value, GameString.get(223)->value, GameString.get(224)->value, GameString.get(279)->value};

	vector<Task*> vtrTasks = gTaskManager->GetAllTasksOngoing();
	vector<Task*> vtrTasksA = gTaskManager->GetAcceptableTask();
	Task *pAcceptableMain = gTaskManager->GetAcceptableMainTask();
	Task *pAcceptableChain = gTaskManager->GetAcceptableChain();
	if (pAcceptableChain)
		vtrTasksA.push_back(pAcceptableChain);

	if (pAcceptableMain)
	{
		//m_pTaskList->SetGroupTitleBG("TaskGroupTitle1");
		//m_pTaskList->SetCurGroup(" "); 
		m_pTaskList->AddItem(((arrTaskType[pAcceptableMain->GetType() - 1]) + pAcceptableMain->GetName()).c_str(), pAcceptableMain->GetID());

		if (pAcceptableMain->GetID() == m_nSelTaskID)
			m_pTaskList->ClickButton(0);
	}

	for (size_t i = 0; i < vtrTasks.size(); i++)
	{
		Task *pTask = vtrTasks[i];

		string strExtension;
		if (pTask->GetCurTurn())
		{
			strExtension = CCString::createWithFormat(GameString.get(283)->value.c_str(), pTask->GetCurTurn())->getCString();
		}
		
		//m_pTaskList->SetGroupTitleBG("TaskGroupTitle2");
		//m_pTaskList->SetCurGroup("  ");
		m_pTaskList->AddItem(((arrTaskType[pTask->GetType() - 1]) + pTask->GetName() + strExtension).c_str(), pTask->GetID());

		if (pTask->GetID() == m_nSelTaskID)
			m_pTaskList->ClickButton(pAcceptableMain ? i + 1 : i);
	}

	for (size_t i = 0; i < vtrTasksA.size(); i++)
	{
		Task *pTask = vtrTasksA[i];

		string strExtension;
		if (pTask->GetCurTurn())
		{
			strExtension = CCString::createWithFormat(GameString.get(283)->value.c_str(), pTask->GetCurTurn())->getCString();
		}

		//m_pTaskList->SetGroupTitleBG("TaskGroupTitle1");
		//m_pTaskList->SetCurGroup(" ");
		m_pTaskList->AddItem(((arrTaskType[pTask->GetType() - 1]) + pTask->GetName() + strExtension).c_str(), pTask->GetID());

		if (pTask->GetID() == m_nSelTaskID)
			m_pTaskList->ClickButton(pAcceptableMain ? i + 1 : i);
	}
}

void TaskUI::updateTaskTrace()
{
	Task* pTask = gTaskManager->GetMainTask();
	if (pTask == NULL)
	{
		pTask = gTaskManager->GetAcceptableMainTask();
	}
	TraceTask(pTask);
}

void TaskUI::update(float dt)
{
	if (gTaskManager->IsTaskChanged())
	{
		updateTaskTrace();
		UpdateTask();
	}
}