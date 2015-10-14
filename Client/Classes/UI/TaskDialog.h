#pragma once

#include "GameDef.h"
#include "GameUI.h"
#include "UI/ResMgr/CtrlAllocator.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/NPC.h"


class TaskDialog : public NpcUI
{
public:
	TaskDialog();
	~TaskDialog();

	bool			onInit();
	void			onClose();
	void			onOpen();
	//virtual void	update(float dt){};
	void			clickExit(Ref*, TouchEventType);
	void			clickAcceptTask(Ref*, TouchEventType);
	void			clickOngoingTask(Ref*, TouchEventType);
	void			clickFinishTask(Ref*, TouchEventType);
	void			SetTask(class Task *pTask);	//
	bool			SelAward(class CGridIcon* pIcon);

	static void		Open(class Task* pTask)
	{
		TaskDialog *pUI = (TaskDialog*)gGameUILayer->open(IDU_TASKDIALOG);
		pUI->SetTask(pTask);
	}


private:
	int					m_nTaskID;
	int					m_nTaskState;
	bool				m_bTaskChain;
	int					m_nSelAwardIndx;
	class RichTextEx*	m_pTaskDes;
	class RichTextEx*	m_pTaskTarget;
	class CGridArrayUI*	m_pPackUI;
	Button *			m_pTask;
	Widget *			m_pTaskPanel;
	Text *				m_pTaskName;
	Text *				m_pTaskAward;
	Widget *			m_pTargetHead;
	Widget *			m_pAwardHead;
	Widget *			m_pSelMark;
	Widget *			m_pSelMarkTxt;
};

