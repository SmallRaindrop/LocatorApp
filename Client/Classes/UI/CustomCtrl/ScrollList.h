#pragma once
#include "UI/CocosUI.h"
#include "UI/ResMgr/CtrlAllocator.h"

using std::vector;

typedef void (Ref::*SEL_SelListIndexEvent)(int, long long);


class CScrollList :public ScrollView
{
public:
	struct GroupInfo
	{
		string	strGroupName;
		Widget*	pStartItem;
		Widget*	pGroupTitle;
		int		nItemNum;
		bool	bSpread;
	};
public:
	CScrollList(void);
	~CScrollList(void);
    static CScrollList* create(bool bItemSelectable = false, string nItemBGID = "Button_Table")
	{
		CScrollList* rw = new CScrollList();
		if(rw && rw->init())
		{
			rw->m_bItemSelectable = bItemSelectable;
			rw->m_nItemBGID = nItemBGID;
			rw->autorelease();
			return rw;
		}
		CC_SAFE_DELETE(rw);
		return NULL;
	}
	Widget*		AddItem(const char* strCaption = "", long long nUserData = 0);
	void		LayOut();
	void		ClickButton(Ref* pSender,CheckBoxEventType type);
	void		ClickButton(Ref* pSender,TouchEventType type);
	void		ClickGroupTitle(Ref* pSender,TouchEventType type);
	void		ClickButton(int nIndex);
	void		UnSelected();
	void		EnableTextShadow(bool Enabled)		{m_bTextShadow = Enabled;}
    void		SetSelectEvent(Ref* target, SEL_TouchEvent selector);
    void		SetSelectEvent(Ref* target, SEL_SelListIndexEvent selector);
    void		SetDBClickEvent(Ref* target, SEL_SelListIndexEvent selector);
	void		SetFontSize(int size)				{m_nFontSize = size;}
	void		SetInterval(int nIn)				{m_nRowInterval = nIn;};
	void		SetTextAlign(TextHAlignment align)	{m_textAlign = align;};
	void		SetDBClickEnabled(bool bDBC)		{m_bDBClickEnabled = bDBC;}
	void		setColor(const Color3B& color)		{ScrollView::setColor(color); m_clrTextNormal = color; }
	void		SetSelTextColor(Color3B clrSel)		{m_clrTextSelected = clrSel;};
	void		SetItemBG(string strBG)				{m_nItemBGID = strBG;}
	void		SetGourpBGClickable(bool bClick)	{m_bGourpBGClickable = bClick;}
	void		SetGroupTitleBG(string strBG)		{m_nGroupBGID = strBG;}
	void		SetCurGroup(string strGroupName);
	GroupInfo*	GetGroup(string strGroupName);
	int			GetItemNum()						{return m_vtrButtons.size();};
	Widget*		GetItem(int nIndex = -1);
	Widget*		GetItemByUserDate(long long nUserData);
	int			GetSelItem(){return m_nSelIndex;};
	void		Clear();
	void		update(float dt);


protected:
    bool					m_bTextShadow;
	bool					m_bItemSelectable;
	bool					m_bGourpBGClickable;
	string					m_nItemBGID;
	string					m_nGroupBGID;
	int						m_nFontSize;
	int						m_nSelIndex;
	int						m_nRowInterval;
	bool					m_bDBClickEnabled;
	bool					m_bDBClick1thClicked;
	float					m_fDBC1thClickLastTime;
	TextHAlignment			m_textAlign;
	vector<GroupInfo>		m_vtrGroupInfo;
	string					m_strCurGroup;
	Color3B					m_clrTextNormal;
	Color3B					m_clrTextSelected;

	SEL_TouchEvent			m_SelHandler;
	Ref*					m_SelListener;
	SEL_SelListIndexEvent	m_SelHandlerI;
	Ref*					m_SelListenerI;
	SEL_SelListIndexEvent	m_DBCHandlerI;
	Ref*					m_DBCListenerI;
	vector<Widget*>			m_vtrButtons;
	vector<long long>		m_vtrUserData;
	Widget*					m_pCurSel;
};
