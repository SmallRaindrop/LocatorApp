#pragma once
#include "UI/CocosUI.h"
#include "UI/ResMgr/CtrlAllocator.h"

using std::vector;
using std::string;

#define path_bg_0	("assets/ui/common/null.png")
#define path_bg_1	("assets/ui/common/PopMenuBg.png")

typedef void (Ref::*SEL_SelectIndexEvent)(int);


class CMenu :public Widget
{
	friend class CComboBox;
	friend class CAlternateSelecter;
public:
	enum Item_Align
	{
		IA_VERTICAL,
		IA_LATERAL,
	};

public:
	CMenu(void);
	~CMenu(void);
	
    static CMenu* create(string nItemBGID = "Button_Menu", string nBGID = "Image_Menu_BG", int nInterval = 0);
	static void PopupMenu(Point pos, Ref* pListenner, SEL_SelectIndexEvent pHandler, const char* strItem1, ...);

	virtual void	AddItem(const char* strCaption, bool bDisabled = false);
	virtual void	ClickButton(Ref *pSender, TouchEventType type);
	virtual void	SetDynamicShow(bool bDynamic) { m_bDynamicShow = bDynamic; }
	void			ClickButton(int nIndex);
    void			SetSelectEvent(Ref *pSender, SEL_TouchEvent selector);
    void			SetSelectEvent(Ref *pSender, SEL_SelectIndexEvent selector);
	void			SetItemAlign(Item_Align align)	{m_eAlign = align;};
	virtual void	Clear();

    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);
	
	void	SetItemBGID(string nItemBGID)	{m_nItemBGID = nItemBGID;}
	void	SetBG(string path) { if(m_pBG){m_pBG->loadTexture(path);} }

	void	_setInterval(int interval)		{m_nInterval = interval;}
	void	_setBGID(string nBGID)			{if (m_pBG) m_pBG->removeFromParent(); m_pBG = (ImageView*)gCtrlAllocator->LoadCtrl(nBGID);
											 if (m_pBG)	{m_pBG->setLocalZOrder(-1); addChild(m_pBG);/* m_pBG->setVisible(false);*/}}

protected:
	Ref*					m_SelListener;
	SEL_TouchEvent			m_SelHandler;

	Ref*					m_SelListenerI;
	SEL_SelectIndexEvent	m_SelHandlerI;

	vector<Button*>			m_vtrButtons;
	int						m_nInterval;
	string					m_nItemBGID;
	string					m_nBGID;
	Item_Align				m_eAlign;

	ImageView *				m_pBG;
	bool					m_bDynamicShow;
};




class CComboBox :public Widget
{
public:
	CComboBox(void)	{};
	~CComboBox(void){};
    //virtual bool init();
    static CComboBox* create(string nTextBoxID = "90004", string nItemBGID = "90003", int nInterval = 40);
	void	AddItem(const char* strCaption);
	void	ItemClicked(int nIndex);
	void	TextBoxClicked(Ref* target);
    void	SetSelectEvent(Ref* target, SEL_SelectIndexEvent selector);
	void	Clear();

private:
	bool _loadTextBox(string nTextBoxID)	
	{
		if (m_pTextBox = (Button*)gCtrlAllocator->LoadCtrl(nTextBoxID))
		{
			m_pTextBox->setAnchorPoint(Point(0.0f, 1.0f));
			m_pTextBox->addTouchEventListener(this, toucheventselector(CComboBox::TextBoxClicked));
			addChild(m_pTextBox);
			return true;
		}
		return false;
	}

	Button*					m_pTextBox;
	CMenu*					m_pMenu;

	SEL_SelectIndexEvent	m_SelHandlerI;
	Ref*					m_SelListenerI;
};

class CAlternateSelecter :public Widget
{
public:
	CAlternateSelecter(void)	{m_nSelIndex = -1;};
	~CAlternateSelecter(void){};
    static CAlternateSelecter* create(int nInterval = 40);
	void	AddItem(const char* strItemBG);
	void	ItemClicked(int nIndex);
	void	RootBoxClicked(Ref* target, TouchEventType type);
    void	SetSelectItem(int nIndex);
    void	SetSelectEvent(Ref* target, SEL_SelectIndexEvent selector);
	void	SetItemAlign(CMenu::Item_Align align)	{m_pMenu->SetItemAlign(align);};
	void	LayOut(bool bSetMenu);
	void	Clear();

private:
	Button*					m_pRootBox;
	CMenu*					m_pMenu;

	vector<string>			m_vtrItemBG;
	SEL_SelectIndexEvent	m_SelHandlerI;
	Ref*					m_SelListenerI;
	int						m_nSelIndex;
};
