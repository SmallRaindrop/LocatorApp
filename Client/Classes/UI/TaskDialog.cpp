#include "TaskDialog.h"
#include "Net/pk_task.h"
#include "Net/NetDispatcher.h"
#include "UIHelper.h"
#include "GameScene/Hero.h"
#include "GameScene/db.h"
#include "GameScene/GameDataManager.h"
#include "GameScene/TaskMgr.h"
#include "CustomCtrl/ScrollList.h"
#include "CustomCtrl/RichTextEX.h"
#include "CustomCtrl/GridArrayUI.h"
#include "GameScene/BeginnerGuide.h"
#include "GameScene/Robot.h"
#include "GameScene/GameProcess.h"


TaskDialog::TaskDialog() : 
	NpcUI(IDU_TASKDIALOG,JSONFILE_TASKDIALOG)
{
	m_nTaskID = 0;
	m_bTaskChain = false;
	m_nSelAwardIndx = -1;
	m_nTaskState = TS_ACCEPT;
}

TaskDialog:: ~TaskDialog()
{
	
}

bool TaskDialog::onInit()
{
	if (!GameUI::onInit())
	{
		return false;
	}

	Widget *pMain = Helper::seekWidgetByName(m_pWidget, "Panel_Boxes");
	Node* pParent = pMain->getParent();
	m_pPackUI = CGridArrayUI::create(emGrids_TaskAward,0,GRIDS_SIZE_TASK,pMain,true);
	gGridsManager->attachUI(m_pPackUI, emGrids_TaskAward);
	pParent->addChild(m_pPackUI);

	Button *pClose	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Exit");
			m_pTask	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Task");
	pClose->addTouchEventListener(this, SEL_TouchEvent(&TaskDialog::clickExit));
	m_pTask->setLocalZOrder(10);

	m_pTaskPanel	= Helper::seekWidgetByName(m_pWidget, "Panel_Task");
	m_pTaskName		= (Text*)Helper::seekWidgetByName(m_pWidget, "Label_TaskName");
	m_pTaskAward	= (Text*)Helper::seekWidgetByName(m_pWidget, "Label_Award");
	m_pTargetHead	= Helper::seekWidgetByName(m_pWidget, "Image_TargetHead");
	m_pAwardHead	= Helper::seekWidgetByName(m_pWidget, "Image_AwardHead");
	m_pSelMark		= Helper::seekWidgetByName(m_pWidget, "Image_Selected");
	m_pSelMarkTxt	= Helper::seekWidgetByName(m_pWidget, "Txt_Selected");
	((Label*)m_pTaskName->getVirtualRenderer())->disableEffect();
	((Label*)m_pTaskAward->getVirtualRenderer())->disableEffect();

	//for (int i = 0; true; i++)
	//{
	//	Widget *pI = Helper::seekWidgetByName(m_pWidget, CCString::createWithFormat("Image_Selected%d", i)->getCString());
	//}

	m_pTaskDes = RichTextEx::create();
	m_pTaskDes->ignoreContentAdaptWithSize(false);
	m_pTaskDes->setSize(Size(680, 10));
	m_pTaskDes->SetFontSize(32);
	m_pTaskDes->setColor(Color3B(0x6e, 0x50, 0x3c));
	m_pTaskDes->SetLinkColor(Color3B::GREEN);
	m_pTaskPanel->getParent()->addChild(m_pTaskDes);

	m_pTaskTarget = RichTextEx::create();
	m_pTaskTarget->ignoreContentAdaptWithSize(false);
	m_pTaskTarget->setSize(Size(600, 10));
	m_pTaskTarget->SetFontSize(32);
	m_pTaskTarget->setColor(Color3B(0x6e, 0x50, 0x3c));
	m_pTaskTarget->SetLinkColor(Color3B::GREEN);
	m_pTaskTarget->setPosition(Point(309, -35));
	m_pTargetHead->addChild(m_pTaskTarget);

	return true;
}

void TaskDialog::onOpen()
{
	// 抛出历程事件
	gGameProcess->PushEvent(GameProcEvent_TaskDialog);
	gRobot->SetRunning(false);
}

void TaskDialog::onClose()
{
	
}

// 用task初始化界面，一切属性来源于task
void TaskDialog::SetTask(Task *pTask)
{
	eTaskStage state = pTask->GetCurStage();	// 当前阶段

	m_nTaskID = pTask->GetID();
	m_nTaskState = state;

	const char*	   arrBtnText[3] = {GameString.get(233)->value.c_str(), GameString.get(234)->value.c_str(), GameString.get(234)->value.c_str()};
	SEL_TouchEvent arrHandler[3] = {SEL_TouchEvent(&TaskDialog::clickAcceptTask), 
									SEL_TouchEvent(&TaskDialog::clickOngoingTask),
									SEL_TouchEvent(&TaskDialog::clickFinishTask)};

	m_pTask->setTitleText(arrBtnText[m_nTaskState]);
	m_pTask->setBright(m_nTaskState != TS_DO);
	m_pTask->setTouchEnabled(m_nTaskState != TS_DO);
	m_pTask->addTouchEventListener(this, arrHandler[m_nTaskState]);

	TaskCfg *pTaskCfg = pTask->GetData();
	if (!pTaskCfg)
	{
		return;
	}
	m_bTaskChain = (pTaskCfg->type == 4);

	m_pTaskTarget->ParseAndLayout(pTask->GetManagedTargetString(state));
	m_pTaskTarget->formatText();
	m_pTaskTarget->setPosition(Point(m_pTaskTarget->getVirtualRendererSize().width / 2, -m_pTaskTarget->getVirtualRendererSize().height / 2 - 25));
	m_pAwardHead->setPositionY(m_pTargetHead->getPositionY() - m_pTaskTarget->getVirtualRendererSize().height - 80);
	m_pTargetHead->setVisible(TS_ACCEPT == m_nTaskState);

	m_pTaskDes->SetContent(pTask->GetManagedTalkString(state).c_str());
	m_pTaskDes->formatText();
	m_pTaskDes->setPosition(Point(47 + m_pTaskDes->getVirtualRendererSize().width / 2, 920 - m_pTaskDes->getVirtualRendererSize().height / 2));
	m_pTaskPanel->setPositionY(m_pTaskDes->getPositionY() - m_pTaskDes->getVirtualRendererSize().height / 2 - 100);
	m_pTaskPanel->setVisible(TS_DO != m_nTaskState);
	m_pTaskName->setText(CCString::createWithFormat(GameString.get(249)->value.c_str(), pTaskCfg->title.c_str())->getCString());

	// 奖励
	string strAwardText;
	TaskAward *pAward = pTask->GetAward();
	int arrAward[] = {pAward->nExp, pAward->nHonour, pAward->nCoin, pAward->nCoinB};
	const char* arrAwardType[] = {GameString.get(243)->value.c_str(), GameString.get(244)->value.c_str(), GameString.get(226)->value.c_str(), GameString.get(227)->value.c_str()};
	for (int i = 0; i < 4; i++)
	{
		if (arrAward[i])
		{
			strAwardText += (CCString::createWithFormat("%s %d   ", arrAwardType[i], arrAward[i])->getCString());
		}
	}
	m_pTaskAward->setText(strAwardText);
	m_pPackUI->setPositionY(m_pAwardHead->getPositionY() - 250);

	gGridsManager->removeAllGrids(emGrids_TaskAward);
	size_t j = 0;
	for (; j < pAward->vtrItems.size(); j++)
	{
		gGridsManager->insertGrid(emGrids_TaskAward, j, pAward->vtrItems[j].pItem->id, pAward->vtrItems[j].nNum);
		gGridsManager->getIcon(emGrids_TaskAward, j)->AddIconClickEvent(pAward->bSelectable && TS_TURNIN == m_nTaskState ? this : NULL, (IconClickEvent)&TaskDialog::SelAward);
	}

	// 随机道具
	if (pTask->GetData()->dropid != 0)
	{
		gGridsManager->insertGrid(emGrids_TaskAward, j, 6000008, 1);
	}

	m_nSelAwardIndx = -1;
	m_pSelMark->setVisible(false);
	m_pSelMarkTxt->setVisible(pAward->bSelectable);
	if (pAward->bSelectable)
	{
		SelAward(gGridsManager->getIcon(emGrids_TaskAward, 0));
		m_pSelMark->setVisible(TS_TURNIN == m_nTaskState);
	}
}

bool TaskDialog::SelAward(CGridIcon* pIcon)
{
	m_pSelMark->setPosition(pIcon->getParent()->getPosition());
	m_nSelAwardIndx = pIcon->GetIndex() + 1;

	return false;
}

void TaskDialog::clickExit(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		gGameUILayer->close(this);
	}
}

void TaskDialog::clickAcceptTask(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (m_bTaskChain)
		{
			pk::C2GS_AccpetTaskChain cmd = {m_nTaskID, CNpc::s_pCurOptNPC->GetDataID(), CNpc::s_pCurOptNPC->GetId()};
			cmd.Send(gNetSocket);
		}
		else
		{
			pk::C2GS_AccpetTask cmd = {m_nTaskID, CNpc::s_pCurOptNPC->GetDataID(), CNpc::s_pCurOptNPC->GetId()};
			cmd.Send(gNetSocket);
		}
		clickExit(NULL, TOUCH_EVENT_ENDED);
	}
}

void TaskDialog::clickOngoingTask(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		clickExit(NULL, TOUCH_EVENT_ENDED);
	}
}

void TaskDialog::clickFinishTask(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (m_bTaskChain)
		{
			pk::C2GS_SubmitTaskChain cmd = {m_nTaskID, CNpc::s_pCurOptNPC->GetDataID(), CNpc::s_pCurOptNPC->GetId()};
			cmd.Send(gNetSocket);
		}
		else
		{
			pk::C2GS_SubmitTask cmd = {m_nTaskID, CNpc::s_pCurOptNPC->GetDataID(), CNpc::s_pCurOptNPC->GetId(), (int8)m_nSelAwardIndx};
			cmd.Send(gNetSocket);
		}

		clickExit(NULL, TOUCH_EVENT_ENDED);
	}
}
