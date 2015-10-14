#include "ScrollBar.h"
#include "../ResMgr/CtrlAllocator.h"
CScrollBar::CScrollBar():
	m_pBarBottom(NULL),
	m_pBarTop(NULL),
	m_ScrollContainer(NULL),
	m_fContainerHeight(0.0f),
	m_fTopHeight(0.0f)
{

}

CScrollBar::~CScrollBar()
{
	m_pBarBottom = NULL;
	m_pBarTop = NULL;
	m_ScrollContainer = NULL;
}

CScrollBar* CScrollBar::create(ScrollView* listUI,std::string BottomID,std::string TopID)
{
	CScrollBar* widget = new CScrollBar;
	if (widget && widget->init(listUI,BottomID,TopID))
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return NULL;
}

CScrollBar* CScrollBar::createWithFile(ScrollView* listUI,std::string BottomID,std::string TopID, TextureResType _type)
{
	CScrollBar* widget = new CScrollBar;
	if (widget && widget->initWithFile(listUI,BottomID,TopID, _type))
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return NULL;
}

bool CScrollBar::init(ScrollView* listUI,std::string BottomID, std::string TopID)
{
	if (!listUI) return false;
	m_ScrollContainer = listUI->getInnerContainer();
	if (!m_ScrollContainer) return false;
	m_pBarBottom = (ImageView*)gCtrlAllocator->LoadCtrl(BottomID);
	m_pBarTop =(ImageView*)gCtrlAllocator->LoadCtrl(TopID);
	if (!m_pBarBottom || !m_pBarTop)
	{
		return false;
	}

	m_fPosY = m_ScrollContainer->getPositionY();

	float fHeight = listUI->getSize().height;
	float fDefaultWidth = m_pBarBottom->getSize().width;
	setSize(Size(fDefaultWidth,fHeight));

	Rect rect(3,10,m_pBarBottom->getSize().width/2,m_pBarBottom->getSize().height - 20);
	m_pBarBottom->setScale9Enabled(true);
	m_pBarBottom->setCapInsets(rect);
	addChild(m_pBarBottom);
	m_pBarBottom->setSize(_size);
	m_pBarBottom->setAnchorPoint(Point(0.5f,1));
	m_pBarBottom->setPosition(Point(fDefaultWidth/2,fHeight));

	rect.setRect(3,10,m_pBarTop->getSize().width/2,m_pBarTop->getSize().height - 20);
	m_pBarTop->setScale9Enabled(true);
	m_pBarTop->setCapInsets(rect);
	addChild(m_pBarTop);
	float fNewHeightPer = _size.height/m_ScrollContainer->getSize().height;
	m_pBarTop->setSize(Size(fDefaultWidth,fHeight*fNewHeightPer));
	m_pBarTop->setAnchorPoint(Point(0.5f,1));
	m_pBarTop->setPosition(Point(fDefaultWidth/2,fHeight));

	return true;
}

bool CScrollBar::initWithFile(ScrollView* listUI,std::string BottomID, std::string TopID, TextureResType _type)
{
	if (!listUI) return false;
	m_ScrollContainer = listUI->getInnerContainer();
	if (!m_ScrollContainer) return false;
	m_pBarBottom = ImageView::create(BottomID, _type);
	m_pBarTop =ImageView::create(TopID, _type);
	if (!m_pBarBottom || !m_pBarTop)
	{
		return false;
	}

	m_fPosY = m_ScrollContainer->getPositionY();

	float fHeight = listUI->getSize().height;
	float fDefaultWidth = m_pBarBottom->getSize().width;
	setSize(Size(fDefaultWidth,fHeight));

	Rect rect(8,5,m_pBarBottom->getSize().width/2,m_pBarBottom->getSize().height/2);
	//Rect rect(m_pBarBottom->getSize().width/2,m_pBarBottom->getSize().height, 1, 1);
	m_pBarBottom->setScale9Enabled(true);
	m_pBarBottom->setCapInsets(rect);
	addChild(m_pBarBottom);
	m_pBarBottom->setSize(_size);
	m_pBarBottom->setAnchorPoint(Point(0.5f,1));
	m_pBarBottom->setPosition(Point(fDefaultWidth/2,fHeight));

	rect.setRect(6,3,m_pBarTop->getSize().width/2,m_pBarTop->getSize().height/2);
	//rect.setRect(m_pBarTop->getSize().width/2,m_pBarTop->getSize().height, 1, 1);
	m_pBarTop->setScale9Enabled(true);
	m_pBarTop->setCapInsets(rect);
	addChild(m_pBarTop);
	float fNewHeightPer = _size.height/m_ScrollContainer->getSize().height;
	m_pBarTop->setSize(Size(fDefaultWidth,fHeight*fNewHeightPer));
	m_pBarTop->setAnchorPoint(Point(0.5f,1));
	m_pBarTop->setPosition(Point(fDefaultWidth/2,fHeight));

	return true;
}

void CScrollBar::setBarSize(float fPercent)
{
	m_fTopHeight = _size.height*fPercent;
	m_pBarTop->setSize(Size(m_pBarTop->getSize().width,m_fTopHeight));
}

void CScrollBar::setBarPosY(float pecent)
{
	pecent = clampf(pecent, 0.0f, 1.0f);

	float posY = (_size.height-m_fTopHeight)*pecent + m_fTopHeight;
	m_pBarTop->setPositionY(posY);
}

void CScrollBar::update(float delta)
{
	if (_size.height >= m_ScrollContainer->getSize().height || m_ScrollContainer->getChildrenCount() == 0)
	{
		setVisible(false);
	}
	else
	{
		setVisible(true);
	}

	float fNewHeight = m_ScrollContainer->getSize().height;
	if (m_fContainerHeight != fNewHeight)
	{
		float pecent = _size.height/fNewHeight;
		setBarSize(pecent);
		m_fContainerHeight = fNewHeight;
	}

	float NewPosY = m_ScrollContainer->getPositionY();
	if (m_fPosY != NewPosY)
	{
		float pecent = (-NewPosY)/(m_ScrollContainer->getSize().height-_size.height);
		setBarPosY(pecent);
		m_fPosY = NewPosY;
	}
}