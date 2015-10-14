#include "NumberAdjuster.h"
#include "UI/ResMgr/CtrlAllocator.h"


CNumberAdjuster::CNumberAdjuster(string strSubBtnID, string strAddBtnID, string strTextBGID, int nSpaceIn2Btn, int nFontSize, Point scaleOfBG, BUTTON_ALIGN align): 
	m_eBtnAlign(), m_strSubBtnID(strSubBtnID), m_strAddBtnID(strAddBtnID), m_strTextBGID(strTextBGID), m_nFontSize(nFontSize), m_scaleOfBG(scaleOfBG),
	m_nSpaceIn2Btn(nSpaceIn2Btn), m_nStep(1), m_pTextNumber(), m_nBtnState(), m_StartTime(0.f),m_fChangeInterval(0.05f), 
	m_nMinimum(0), m_nMaximum(0), m_pValueChangeHandler(), m_pValueListenner(), m_pValueConfirmedHandler(), m_pValueListenner2()
{
}


CNumberAdjuster::~CNumberAdjuster(void)
{
}

bool CNumberAdjuster::init()
{
	if (!Widget::init())
	{
		return false;
	}

	m_pSubButton = (Button*)gCtrlAllocator->LoadCtrl(m_strSubBtnID);
	if (!m_pSubButton)	return false;
	Size offset = m_pSubButton->getContentSize() / 2;
	m_pSubButton->addTouchEventListener(this, SEL_TouchEvent(&CNumberAdjuster::PushButton));
	m_pSubButton->setPosition(Point(offset.width, 0));

	m_pAddButton = (Button*)gCtrlAllocator->LoadCtrl(m_strAddBtnID);
	if (!m_pAddButton)	return false;
	m_pAddButton->setPosition(Point(m_nSpaceIn2Btn + offset.width, 0));
	m_pAddButton->addTouchEventListener(this, SEL_TouchEvent(&CNumberAdjuster::PushButton));

	ImageView *pTextBG = (ImageView*)gCtrlAllocator->LoadCtrl(m_strTextBGID);
	if (!pTextBG)	return false;
	m_pTextNumber = Text::create();
	m_pTextNumber->setText("0");
	m_pTextNumber->setFontSize(m_nFontSize);
	pTextBG->setScaleX(m_scaleOfBG.x);
	pTextBG->setScaleY(m_scaleOfBG.y);
	pTextBG->setLocalZOrder(0);
	pTextBG->setPosition(Point(m_nSpaceIn2Btn / 2 + offset.width, 0.f));
	m_pTextNumber->setPosition(pTextBG->getPosition());

	addChild(m_pSubButton);
	addChild(m_pAddButton);
	addChild(pTextBG);
	addChild(m_pTextNumber);

	return true;
}

void CNumberAdjuster::SetValueChangedEvent(Ref* pObj, ValueChangeHandler func)
{
	m_pValueChangeHandler = func;
	m_pValueListenner = pObj;
}

void CNumberAdjuster::SetValueConfirmedEvent(Ref* pObj, ValueChangeHandler func)
{
	m_pValueConfirmedHandler = func;
	m_pValueListenner2 = pObj;
}

void CNumberAdjuster::PushButton(Ref* pSender,TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		m_nBtnState = (pSender == m_pAddButton ? 1 : -1);
		ChangeNumber();
		m_StartTime = 0.f;
	}
	else if (type == TOUCH_EVENT_ENDED)
	{
		m_nBtnState = 0;

		if (m_pValueConfirmedHandler && m_pValueListenner2)
		{
			(m_pValueListenner2->*m_pValueConfirmedHandler)(this);
		}
	}
}

void CNumberAdjuster::SetValue(int nValue)
{
	if (nValue > m_nMaximum || nValue < m_nMinimum)
	{
		return;
	}

	m_pSubButton->setBright(nValue > m_nMinimum);
	m_pAddButton->setBright(nValue < m_nMaximum);
	m_pSubButton->setTouchEnabled(nValue > m_nMinimum);
	m_pAddButton->setTouchEnabled(nValue < m_nMaximum);
	m_pTextNumber->setText(StringConverter::toString(nValue).c_str());
}

void CNumberAdjuster::ChangeNumber()
{
	int nCurValue = StringConverter::toInt(m_pTextNumber->getStringValue());
	nCurValue += m_nBtnState * m_nStep;

	m_pSubButton->setBright(nCurValue > m_nMinimum);
	m_pAddButton->setBright(nCurValue < m_nMaximum);
	m_pSubButton->setTouchEnabled(nCurValue > m_nMinimum);
	m_pAddButton->setTouchEnabled(nCurValue < m_nMaximum);
	if (nCurValue > m_nMaximum)
	{
		return;
	}
	if (nCurValue < m_nMinimum)
	{
		return;
	}

	m_pTextNumber->setText(StringConverter::toString(nCurValue).c_str());

	if (m_pValueChangeHandler && m_pValueListenner)
	{
		(m_pValueListenner->*m_pValueChangeHandler)(this);
	}
}

void CNumberAdjuster::update(float dt)
{
	Widget::update(dt);

	if (m_nBtnState)
	{
		if (m_StartTime > 1.0f)
		{
			static float fInterval = 0.f;
			fInterval += dt;

			if (fInterval > m_fChangeInterval)
			{
				ChangeNumber();
				fInterval = 0.0f;
			}
		}
		m_StartTime += dt;
	}

}

const Size& CNumberAdjuster::getContentSize()
{
	Widget *pOneBtn = gCtrlAllocator->LoadCtrl(m_strSubBtnID);
	float height = max(pOneBtn->getContentSize().height, m_pTextNumber->getContentSize().height);
	float width  = m_nSpaceIn2Btn +  pOneBtn->getContentSize().width * 2;

	setContentSize(Size(width, height));
	return _contentSize;
}

Widget*	CNumberAdjuster::GetElement(int nIndex)
{
	Widget *arr[] = {m_pSubButton, m_pTextNumber, m_pAddButton};
	return arr[nIndex];
}