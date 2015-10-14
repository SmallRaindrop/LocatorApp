#include "ScrollMenu.h"
#include "RadioButtonSet.h"

CScrollMenu::CScrollMenu()
	:m_pRadioMenu(NULL)
	,m_fInterval(0.0f)
	,m_sRadioSize(Size::ZERO)
	,m_pLeftBtn(NULL)
	,m_pRightBtn(NULL)
	,m_fExtraTurn(10.0f)
{

}

CScrollMenu::~CScrollMenu()
{

}

CScrollMenu* CScrollMenu::create(Size size)
{
	CScrollMenu* widget = new CScrollMenu;
	if (widget && widget->init(size))
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return NULL;
}

bool CScrollMenu::init(Size size)
{
	if (!ListView::init())
	{
		return false;
	}
	setSize(size);
	setBounceEnabled(true);
	m_pRadioMenu = RadioButtonSet::create();
	m_sRadioSize = Size(0,size.height);
	m_pRadioMenu->setContentSize(m_sRadioSize);
	m_pRadioMenu->setAnchorPoint(Point::ZERO);
	m_pRadioMenu->SetRelayout(true);
	pushBackCustomItem(m_pRadioMenu);
	addEventListenerScrollView(this,scrollvieweventselector(CScrollMenu::scrollEvent));
	return true;
}

void CScrollMenu::setInterval(float fInterval)
{
	m_fInterval = fInterval;
	m_pRadioMenu->SetInterval(fInterval);
}

void CScrollMenu::setLeftBtn(Button* pBtn)
{
	m_pLeftBtn = pBtn;
	m_pLeftBtn->addTouchEventListener(this,toucheventselector(CScrollMenu::clickLeftBtn));
}

void CScrollMenu::setRightBtn(Button* pBtn)
{
	m_pRightBtn = pBtn;
	m_pRightBtn->addTouchEventListener(this,toucheventselector(CScrollMenu::clickRightBtn));
}

void CScrollMenu::addMenu(CheckBox* pBox)
{
	m_pRadioMenu->AddButton(pBox);
	updateInnerSize();
}

void CScrollMenu::insertMenu(CheckBox* pBox,int nIndex)
{
	m_pRadioMenu->InsertButton(pBox,nIndex,NULL);
	updateInnerSize();
}

void CScrollMenu::remMenu(int nIndex)
{
	m_pRadioMenu->RemButton(nIndex);
	updateInnerSize();
}

void CScrollMenu::remMenu(int nFrom, int nTo)
{
	m_pRadioMenu->RemButton(nFrom,nTo);
	updateInnerSize();
}

void CScrollMenu::updateInnerSize()
{
	m_sRadioSize = Size((m_pRadioMenu->GetButtonSize().width+m_fInterval)*m_pRadioMenu->GetButtonNum()+m_fInterval,m_sRadioSize.height);
	m_pRadioMenu->setContentSize(m_sRadioSize);
	setInnerContainerSize(m_sRadioSize);
}

void CScrollMenu::clickButton(int nIndex)
{
	m_pRadioMenu->ClickButton(nIndex);
}

void CScrollMenu::SetSelectEvent(Ref* target,SEL_SelectIndexEvent selector)
{
	m_pRadioMenu->SetSelectEvent(target,selector);
}

void CScrollMenu::setButtonSize(Size size)
{
	m_pRadioMenu->SetButtonSize(size);
}

void CScrollMenu::scrollToMenu(int index)
{
	m_pRadioMenu->ClickButton(index);
	if (m_sRadioSize.width == _size.width) return;
	Widget* pRadioItem = m_pRadioMenu->GetButton(index);
	float moveOffset = pRadioItem->getRightInParent()+m_fInterval-_size.width;
	if ((index+1) == m_pRadioMenu->GetButtonNum())
	{
		moveOffset += m_fExtraTurn;
	}
	moveOffset = moveOffset>0?moveOffset:0;
	float pecent = moveOffset*100/(m_sRadioSize.width-_size.width);
	scrollToPercentHorizontal(pecent,0.5f,true);
}

float CScrollMenu::getScrollPecent()
{
	if (m_sRadioSize.width == _size.width) return 0.0f;
	Point pos = getInnerContainer()->getPosition();
	float moveOffset = -pos.x;
	return moveOffset*100/(m_sRadioSize.width-_size.width);
}

float CScrollMenu::getTurningWidthLeft()
{
	Point pos = getInnerContainer()->getPosition();
	float leftWidth =(m_sRadioSize.width - (-pos.x + _size.width));
	if (leftWidth>_size.width)
	{
		return _size.width;
	}
	else
	{
		return leftWidth+m_fExtraTurn;
	}
}

float CScrollMenu::getTurningWidthRight()
{
	Point pos = getInnerContainer()->getPosition();
	float leftWidth = -pos.x;
	if (leftWidth > _size.width)
	{
		return _size.width;
	} 
	else
	{
		return leftWidth+m_fExtraTurn;
	}
}

void CScrollMenu::scrollOnePageLeft()
{
	if (m_sRadioSize.width == _size.width) return;
	float fOnePagePecent = getTurningWidthRight()*100/(m_sRadioSize.width-_size.width);
	fOnePagePecent = getScrollPecent()-fOnePagePecent;
	float extraPecent = -m_fExtraTurn*100/(m_sRadioSize.width-_size.width);
	scrollToPercentHorizontal(fOnePagePecent<=0?extraPecent:fOnePagePecent,0.5f,true);
}

void CScrollMenu::scrollOnePageRight()
{
	if (m_sRadioSize.width == _size.width) return;
	float fOnePagePecent = getTurningWidthLeft()*100/(m_sRadioSize.width-_size.width);
	scrollToPercentHorizontal(getScrollPecent()+fOnePagePecent,0.5f,true);
}

void CScrollMenu::scrollEvent(Ref* pSender,ScrollviewEventType type)
{
	if (SCROLLVIEW_EVENT_SCROLLING == type)
	{
		setRightBright(true);
		setLeftBright(true);
	}
	else if (SCROLLVIEW_EVENT_SCROLL_TO_LEFT == type)
	{
		setLeftBright(false);
	}
	else if ( SCROLLVIEW_EVENT_SCROLL_TO_RIGHT == type)
	{
		setRightBright(false);
	}
}

void CScrollMenu::clickLeftBtn(Ref* pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		scrollOnePageLeft();
	}
}

void CScrollMenu::clickRightBtn(Ref* pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		scrollOnePageRight();
	}
}

void CScrollMenu::setLeftBright(bool bBright)
{
	if (m_pLeftBtn)
	{
		m_pLeftBtn->setTouchEnabled(bBright);
		m_pLeftBtn->setBright(bBright);
	}
}

void CScrollMenu::setRightBright(bool bBright)
{
	if (m_pRightBtn)
	{
		m_pRightBtn->setTouchEnabled(bBright);
		m_pRightBtn->setBright(bBright);
	}
}

void CScrollMenu::Clear()
{
	if(m_pRadioMenu)
	{
		m_pRadioMenu->Clear();
	}
}