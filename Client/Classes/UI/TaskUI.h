#pragma once

#include "GameDef.h"
#include "GameUI.h"
#include "CustomCtrl/RichTextEX.h"


class TaskUI : public GameUI
{
public:
	TaskUI();
	~TaskUI();

	bool			onInit();
	virtual void	onOpen();
	virtual void	onClose();
	virtual void	update(float dt);
	void			clickExit(Ref*, TouchEventType);
	void			clickGo(Ref*, TouchEventType);
	void			clickAccNPC(int, RichTextEx::Link_Data*);
	void			clickFinNPC(int, RichTextEx::Link_Data*);
	void			SelTask(int, long long);
	void			UpdateTask();	//
	void			updateTaskTrace();
	void			TraceTask(class Task* pTask);
	void			showTaskUI(bool bShowTask);
	void			clickTask(Ref *pSender, TouchEventType type);
	void			clickTaskBtn(Ref *pSender, CheckBoxEventType type);
	void			clickCancelTask(Ref*, TouchEventType);


private:
	int					m_nSelTaskID;
	int					m_nDetailPosX;

	Widget*				m_pTaskImg;
	CheckBox*			m_pTaskBtn;
	class RichTextEx *	m_pTaskTrace;
	class Task*			m_pTraceTask;

	Widget *			m_pListMain;
	class CScrollList*	m_pTaskList;
	class RichTextEx*	m_pTaskDes;
	Widget *			m_pAroundPanel;
	Widget *			m_pDetail;
	Button *			m_pCancelTask;
	Text *				m_pTaskAward;	
};

