#pragma once
#include "GameDef.h"
#include "UI/CocosUI.h"

using std::vector;

enum RBS_ALIGN
{
	RBS_ALIGN_VERTICAL,
	RBS_ALIGN_LATERAL,
};

typedef void (CCObject::*SEL_SelectIndexEvent)(int);

class RadioButtonSet :public Widget
{
public:
	RadioButtonSet(void);
	~RadioButtonSet(void);
	
    static RadioButtonSet* create()
	{
		RadioButtonSet* rw = new RadioButtonSet();
		if(rw && rw->init())
		{
			rw->autorelease();
			return rw;
		}
		CC_SAFE_DELETE(rw);
		return NULL;
	}
	void	AddButton(CheckBox*, const char* strCaption = NULL);
	void	InsertButton(CheckBox*, int nIndex, const char* strCaption);
	void	RemButton(int nIndex);
	//°üº¬fromºÍto
	void	RemButton(int nFrom, int nTo);
	void	Layout();
	void	ClickButton(Ref *pSender, CheckBoxEventType type);
	void	ClickButton(int nIndex);
	void	SetInterval(int interval)	{m_nInterval = interval;}

	void	SetSelectButton(int nIndex);
    void	SetSelectEvent(Ref *pSender, SEL_SelectedStateEvent selector);
    void	SetSelectEvent(Ref *pSender, SEL_SelectIndexEvent selector);
	void	SetAlign(RBS_ALIGN align)	{m_eAlign = align;}
	void	SetFontSize(int size)		{m_nFontSize = size;}
	void	SetRelayout(bool bRelayout)	{m_bRelayout = bRelayout;}
	void	SetButtonSize(Size size) { m_buttonSize = size; }

	Size		GetButtonSize() { return m_buttonSize; }
	CheckBox*	GetButton(int nIndex);
	CheckBox*	GetSelButton()			{return m_pCurSel;}
	int			GetSelIndex();
	size_t		GetButtonNum() { return m_vtrButtons.size(); }
	vector<CheckBox*>&	GetButtons() { return m_vtrButtons; }

	void	ClearSelState();
	void	Clear();
private:

	SEL_SelectedStateEvent	m_SelHandler;
	Ref*					m_SelListener;
	SEL_SelectIndexEvent	m_SelHandlerI;
	Ref*					m_SelListenerI;
	vector<CheckBox*>		m_vtrButtons;
	vector<Point>			m_vtrPoints;
	CheckBox*				m_pCurSel;
	RBS_ALIGN				m_eAlign;
	int						m_nFontSize;
	int						m_nInterval;
	bool					m_bRelayout;
	Point					m_OffsetBase;
	Size					m_buttonSize;
};

