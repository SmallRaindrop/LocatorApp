#include "NpcDialog.h"
#include "CustomCtrl/UnderLinedText.h"
#include "CustomCtrl/RichTextEX.h"
#include "GameScene/NPC.h"
#include "GameScene/Hero.h"
#include "Net/pk_battle.h"
#include "Net/pk_map.h"
#include "Net/NetDispatcher.h"
#include "../GameScene/TaskMgr.h"
#include "TaskDialog.h"
#include "MessageBoxUI.h"
#include "TeamUI.h"

#define		Dialog_Height		(350)
#define		Fucntion_Height		(84)
#define		Leave_Tag			(100)

CNpcDialog::CNpcDialog()
	:NpcUI(IDU_NPCDIALOG,JSONFILE_NPCDIALOG)
	,m_pNpcName(NULL)
	,m_pTalkContent(NULL)
	,m_pDialogPanel(NULL)
	,m_pFuncsPanel(NULL)
	,m_pNpcCfg(NULL)
	,m_pDivImg(NULL)
{

}

CNpcDialog::~CNpcDialog()
{
	m_pNpcCfg = NULL; 
	m_pNpcFuncCfg.clear();
}

bool CNpcDialog::onInit()
{
	m_pDialogPanel = m_pWidget->getChildByName("DialogPanel");
	if ( !m_pDialogPanel )
	{
		return false;
	}

	m_pNpcName = (Text*)(m_pDialogPanel->getChildByName("Name"));
	m_pTalkContent = (Text*)(m_pDialogPanel->getChildByName("Talk"));
	m_pFuncsPanel = m_pDialogPanel->getChildByName("FuncsPanel");
	m_pDivImg = m_pDialogPanel->getChildByName("Div");
	m_pLeaveBtn = (Button*)m_pDialogPanel->getChildByName("LeaveBtn");
	if ( !m_pNpcName || !m_pTalkContent || !m_pFuncsPanel || !m_pDivImg)
	{
		return false;
	}

	m_pTaskList = CScrollTable::create(false, "NpcDialogSel");
	m_pTaskList->SetFontSize(FontSize36);
	m_pTaskList->setBounceEnabled(false);

	m_pTaskList->SetSelectEvent(this, SEL_SelListIndexEvent(&CNpcDialog::clickTaskItem));
	m_pTaskList->SetFormat(TCT_IMAGE, 300, 0.0, 0.5, TCT_NODE_PTR, 502, 0.5, 0.5,TCT_NONE);

	m_pFuncList = CScrollTable::create(false, "NpcDialogSel");
	m_pFuncList->SetFontSize(FontSize36);
	m_pFuncList->setBounceEnabled(false);
	m_pFuncList->SetSelectEvent(this, SEL_SelListIndexEvent(&CNpcDialog::clickFuncItem));
	m_pFuncList->SetFormat(TCT_STRING, 502, 0.5, 0.5,TCT_NONE);

	m_pFuncsPanel->addChild(m_pTaskList);
	m_pFuncsPanel->addChild(m_pFuncList);

	m_pLeaveBtn->addTouchEventListener(this,toucheventselector(CNpcDialog::clickBtnClose));
	return true;
}

void CNpcDialog::onOpen()
{
	NpcUI::onOpen();

	if (!CNpc::s_pCurOptNPC)
	{
		gGameUILayer->close(this);
		return;
	}

	m_pNpcCfg = CNpc::s_pCurOptNPC->GetData();
	if ( !m_pNpcCfg )
	{
		return;
	}

	m_pNpcName->setText(m_pNpcCfg->name);
	m_pTalkContent->setText(m_pNpcCfg->talk);

	InitFuncsPanel();
}

void CNpcDialog::onClose()
{
	m_pNpcCfg = NULL;
	m_pNpcFuncCfg.clear();
	m_taskids.clear();
	m_pTaskList->Clear();
	m_pFuncList->Clear();

	if (gHero->GetSelectTarget() == CNpc::s_pCurOptNPC)
		gHero->SelectTargetCancel();
}

void CNpcDialog::InitFuncsPanel()
{
	vector<int> TaskAcceptIds = CNpc::s_pCurOptNPC->GetTaskAcc();
	//string functions = m_pNpcCfg->task_accept;
	string functions = "";
	string_trim(functions);
	StringSplitToInt(functions,",",TaskAcceptIds);

	vector<int> TaskCompleteIds = CNpc::s_pCurOptNPC->GetTaskFin();
	//functions = m_pNpcCfg->task_complete;
	functions = "";
	string_trim(functions);
	StringSplitToInt(functions,",",TaskCompleteIds);

	vector<int> funcIds;
	functions = m_pNpcCfg->funcs;
	string_trim(functions);
	StringSplitToInt(functions,",",funcIds);

	FillTaskIds(TaskCompleteIds,TaskAcceptIds);

	size_t nFunsSize = m_taskids.size()+funcIds.size();
	AdaptSizeAndPos(nFunsSize);

	float fTaskHeight = m_taskids.size()*Fucntion_Height;
	float fFuncsHeight = funcIds.size()*Fucntion_Height;

	m_pTaskList->setSize(Size(980,fTaskHeight));
	m_pFuncList->setSize(Size(980,fFuncsHeight));

	for (size_t i=0; i<TaskCompleteIds.size(); ++i)
	{
		Task* pTask = gTaskManager->GetTaskOngoing(TaskCompleteIds[i]);
		if (!pTask) 
			continue;

		RichTextEx *pTaskName = RichTextEx::create();
		pTaskName->SetLinkColor(Color3B::RED);
		pTaskName->SetFontSize(FontSize36);

		if (pTask->GetType() == 3)
		{
			pTaskName->SetContent((pTask->GetName() + GameString.get(277)->value).c_str(), gTaskManager->GetTaskFinishedTimes(pTask->GetID()), pTask->GetData()->loopcnt);
		}
		else
		{
			string strExtension;
			if (pTask->GetCurTurn())
			{
				strExtension = GameString.get(283)->value;
			}
			pTaskName->SetContent((pTask->GetName() + strExtension).c_str(), pTask->GetCurTurn());
		}
		vector<Node*> pNodes = m_pTaskList->AddRow(i,gTaskManager->CanTaskBeFinished(TaskCompleteIds[i]) ? "SmallComplete" : "SmallNotComplete", pTaskName);
		((Text*)(pNodes[1]))->setColor(Color3B(110,80,60));
	}

	string arrTaskType[] = {GameString.get(221)->value, GameString.get(223)->value, GameString.get(224)->value, GameString.get(279)->value};

	for (size_t i=0; i<TaskAcceptIds.size(); ++i)
	{
		if (!gTaskManager->CanTaskBeAccepted(TaskAcceptIds[i]))
			continue;

		RichTextEx *pTaskName = RichTextEx::create();
		pTaskName->SetLinkColor(Color3B::RED);
		pTaskName->SetFontSize(FontSize36);

		Task *pTask = gTaskManager->GetTask(TaskAcceptIds[i]);
		TaskCfg *pTaskCfg = pTask->GetData();
		

		if (TaskData.get(TaskAcceptIds[i])->type == 3)
		{
			pTaskName->SetContent((arrTaskType[pTask->GetType() - 1] + pTask->GetName() + GameString.get(277)->value).c_str(), 
				gTaskManager->GetTaskFinishedTimes(pTaskCfg->id), pTaskCfg->loopcnt);
		}
		else
		{
			string strExtension;
			if (pTask->GetCurTurn())
			{
				strExtension = GameString.get(283)->value;
			}
			pTaskName->SetContent((arrTaskType[pTask->GetType() - 1] + pTask->GetName() + strExtension).c_str(), pTask->GetCurTurn());
		}
		vector<Node*> pNodes = m_pTaskList->AddRow(i,"SmallAccept",pTaskName);
		((Text*)(pNodes[1]))->setColor(Color3B(110,80,60));
	}

	for (size_t i=0; i<funcIds.size(); ++i)
	{
		Npc_functionCfg* pCfg = NpcFuncsData.get(funcIds[i]);
		if( !pCfg ) continue;

		m_pNpcFuncCfg.push_back(pCfg);
		vector<Node*> pNodes = m_pFuncList->AddRow(i,pCfg->name.c_str(), -1);
		((Text*)(pNodes[0]))->setColor(Color3B(110,80,60));
	}
	m_pTaskList->setPositionY(m_pFuncsPanel->getSize().height-fTaskHeight);
	m_pFuncList->setPositionY(m_pFuncsPanel->getSize().height-fTaskHeight-fFuncsHeight);
	m_pLeaveBtn->setPositionY(77.0f);
}

void CNpcDialog::FillTaskIds(vector<int>& completeVec, vector<int>& acceptVec)
{
	for (size_t i=0; i<completeVec.size(); ++i)
	{
		Task* pTask = gTaskManager->GetTaskOngoing(completeVec[i]);
		if (!pTask) continue;
		m_taskids.push_back(completeVec[i]);
	}

	for (size_t i=0; i<acceptVec.size(); ++i)
	{
		if (!gTaskManager->CanTaskBeAccepted(acceptVec[i]))
			continue;
		m_taskids.push_back(acceptVec[i]);
	}
}

void CNpcDialog::AdaptSizeAndPos(size_t nFunsSize)
{
	float fHeight = 0.0f;
	if (nFunsSize > 0)
	{
		fHeight = Dialog_Height + Fucntion_Height*nFunsSize;
	}
	else
	{
		fHeight = Dialog_Height;
	}

	m_pDialogPanel->setSize(Size(m_pDialogPanel->getSize().width,fHeight));
	m_pDialogPanel->setPositionY((GAME_UI_ORIG_SIZE.height-fHeight)/2);

	m_pNpcName->setPosition(Point(160+m_pNpcName->getVirtualRendererSize().width/2,fHeight-55.0f));
	m_pTalkContent->setPositionY(fHeight-153.0f);
	m_pDivImg->setPositionY(fHeight-213.0f);
	m_pFuncsPanel->setSize(Size(m_pFuncsPanel->getSize().width,Fucntion_Height*nFunsSize));
	m_pFuncsPanel->setPositionY(124.0f);
}

void CNpcDialog::EventByFuncName(size_t nIndex)
{
	if ( nIndex > m_pNpcFuncCfg.size()-1 )
	{
		return;
	}
	
	switch (m_pNpcFuncCfg[nIndex]->type)
	{
	case FuncEvent_Transfer:
		{

		}
		break;
	case FuncEvent_NpcStore:
		break;
	case FuncEvent_Strength:
		{

		}
		break;
	case FuncEvent_CopyMap:
		{
			string maplist = m_pNpcFuncCfg[nIndex]->param;
			vector<int> intVec;
			string_trim(maplist);
			StringSplitToInt(maplist,",",intVec);
			pk::C2GS_ReqEnterCopyMap cmd;
			cmd.npcId = CNpc::s_pCurOptNPC->GetId();
			cmd.npcDataID = CNpc::s_pCurOptNPC->GetDataID();
			cmd.enterType = intVec[0];
			cmd.enterMapDataId = intVec[1];
			cmd.Send(gNetSocket);

		}
		break;
	case FuncEvent_Battle:
		{
			if (CTeamUI::s_teamInfo.teamId == 0 || CTeamUI::s_teamInfo.member_list.size() == 1)
			{
				CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,GameString.get(285)->value.c_str(),STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),this,YESORNO_EVENT(&CNpcDialog::EnterBattleConfirm));
			}
			else if (CTeamUI::s_teamInfo.leadId == gHero->GetId())
			{
				pk::C2GS_TeamRequestEnterMap cmd = {CNpc::s_pCurOptNPC->GetId(), CNpc::s_pCurOptNPC->GetDataID()};
				cmd.Send(gNetSocket);
			}
			else
			{
				CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,GameString.get(286)->value.c_str(),STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),this,YESORNO_EVENT(&CNpcDialog::EnterBattleConfirm));
			}

		}
		break;
	case FuncEvent_BuffStore:
		{
		}
		break;
	}
	gGameUILayer->close(this);
}

void CNpcDialog::EnterBattleConfirm(bool yesOrNo)
{
	if (yesOrNo)
	{	
		pk::C2GS_SignalEnterBattleMap cmd = {CNpc::s_pCurOptNPC->GetId(), CNpc::s_pCurOptNPC->GetDataID()};
		cmd.Send(gNetSocket);
	}
}

void CNpcDialog::clickBtnClose(Ref *pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

void CNpcDialog::clickTaskItem(int nIndex, long long noused)
{
	if (nIndex>(int)(m_taskids.size()-1))
	{
		return;
	}

	TaskDialog::Open(gTaskManager->GetTask(m_taskids[nIndex]));
	clickBtnClose(NULL,TOUCH_EVENT_ENDED);
}

void CNpcDialog::clickFuncItem(int nIndex, long long noused)
{
	EventByFuncName(noused);
}