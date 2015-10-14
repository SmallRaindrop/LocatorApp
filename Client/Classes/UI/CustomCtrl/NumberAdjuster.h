#pragma once
#include "GameDef.h"
#include "StringConverter.h"
#include "UI/CocosUI.h"


typedef void (Ref::*ValueChangeHandler)(Ref*);
typedef void (Ref::*ValueConfirmedHandler)(Ref*);
class CNumberAdjuster :public Widget
{
public:
	enum BUTTON_ALIGN
	{
		BA_LATERAL,
		BA_VERTICAL
	};
public:
	CNumberAdjuster(string strSubBtnID, string strAddBtnID, string strTextBGID, int nSpaceIn2Btn, int nFontSize, Point scaleOfBG = Point(1, 1), BUTTON_ALIGN align = BA_LATERAL);
	~CNumberAdjuster(void);
	
    static CNumberAdjuster* create(string strSubBtnID, string strAddBtnID, string strTextBGID, int nSpaceIn2Btn, int nFontSize = 20, Point scaleOfBG = Point(1, 1))
	{
		CNumberAdjuster* rw = new CNumberAdjuster(strSubBtnID, strAddBtnID, strTextBGID, nSpaceIn2Btn, nFontSize, scaleOfBG);
		if(rw && rw->init())
		{
			rw->autorelease();
			return rw;
		}
		CC_SAFE_DELETE(rw);
		return NULL;
	}
	bool	init();
	void	update(float dt);
	void	PushButton(Ref* pSender,TouchEventType type);
	void	ReleaseButton(Ref* pSender,TouchEventType type);
	void	ChangeNumber();
	const	Size& getContentSize();
	void	SetValueLimit(int nMinimum, int nMaximum)	{m_nMinimum = nMinimum; m_nMaximum = nMaximum; SetValue(clampf(GetValue(), nMinimum, nMaximum));}
	int		GetValue()									{return StringConverter::toInt(m_pTextNumber->getStringValue());}
	void	SetValue(int nValue);//						{m_pTextNumber->setText(StringConverter::toString(nValue).c_str());}
	void	SetStep(int nStep)							{m_nStep = nStep;}
	void	SetChangeInterval(float fChangeInterval)	{m_fChangeInterval = fChangeInterval;}
	void	SetValueChangedEvent(Ref*, ValueChangeHandler);
	void	SetValueConfirmedEvent(Ref*, ValueChangeHandler);
	Widget*	GetElement(int nIndex);	// 0, 1, 2 分别代表减按钮、输入框、加按钮
	
private:
	BUTTON_ALIGN		m_eBtnAlign;
	int					m_nFontSize;
	string				m_strSubBtnID;
	string 				m_strAddBtnID;
	string 				m_strTextBGID;
	int 				m_nSpaceIn2Btn;
	int					m_nStep;
	int					m_nMinimum;
	int					m_nMaximum;

	Text *				m_pTextNumber;
	Button *			m_pSubButton;
	Button *			m_pAddButton;
	int					m_nBtnState;
	float				m_StartTime;
	float				m_fChangeInterval;
	Point				m_scaleOfBG;

	ValueChangeHandler		m_pValueChangeHandler;
	Ref*					m_pValueListenner;
	ValueConfirmedHandler	m_pValueConfirmedHandler;
	Ref*				m_pValueListenner2;
};

