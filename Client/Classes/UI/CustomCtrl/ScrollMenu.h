#pragma once
#include "GameDef.h"
#include "UI/CocosUI.h"
#include "RadioButtonSet.h"


class CScrollMenu : public ListView
{
public:
	CScrollMenu();
	~CScrollMenu();

	static CScrollMenu*		create(Size size);
	bool					init(Size size);
	class RadioButtonSet*	getRadioMenu() { return m_pRadioMenu; }
	void					addMenu(CheckBox* pBox);
	void					insertMenu(CheckBox* pBox,int nIndex);
	void					remMenu(int nIndex);
	void					remMenu(int nfrom,int nTo);
	void					updateInnerSize();
	void					clickButton(int nIndex);
	void					SetSelectEvent(Ref* target,SEL_SelectIndexEvent selector);
	void					setInterval(float fInterval);
	void					setExtraTurn(float fExtraTurn) { m_fExtraTurn = fExtraTurn; }
	void					setLeftBtn(Button* pBtn);
	void					setRightBtn(Button* pBtn);
	void					setButtonSize(Size size);
	void					scrollToMenu(int index);
	void					scrollOnePageLeft();
	void					scrollOnePageRight();
	size_t					GetButtonNum() { return m_pRadioMenu->GetButtonNum(); }
	vector<CheckBox*>&		GetButtons() { return m_pRadioMenu->GetButtons(); }
	int						GetSelIndex() { return m_pRadioMenu->GetSelIndex(); }
	void					Clear();

private:
	float					getScrollPecent();
	float					getTurningWidthLeft();
	float					getTurningWidthRight();
	void					scrollEvent(Ref*, ScrollviewEventType);
	void					clickLeftBtn(Ref* pSender, TouchEventType type);
	void					clickRightBtn(Ref* pSender, TouchEventType type);
	void					setLeftBright(bool bBright);
	void					setRightBright(bool bBright);

private:
	class RadioButtonSet*			m_pRadioMenu;
	float							m_fInterval;
	float							m_fExtraTurn;//Extra为了触发SCROLLVIEW_EVENT_SCROLL_TO_LEFT和right事件
	Size							m_sRadioSize;
	Button*							m_pLeftBtn;
	Button*							m_pRightBtn;
};