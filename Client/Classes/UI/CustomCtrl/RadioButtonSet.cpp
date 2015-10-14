#include "CommonDef.h"
#include "RadioButtonSet.h"
#include "CCLabel.h"


RadioButtonSet::RadioButtonSet(void): m_pCurSel(), m_SelHandler(), m_SelListener(), m_SelHandlerI(), m_SelListenerI(),
	m_eAlign(RBS_ALIGN_LATERAL), m_nInterval(20), m_bRelayout(false), m_OffsetBase(), m_nFontSize(20)
{
}


RadioButtonSet::~RadioButtonSet(void)
{
}

void RadioButtonSet::AddButton(CheckBox* pBox, const char* strCaption)
{
	InsertButton(pBox,m_vtrButtons.size(),strCaption);
}

void RadioButtonSet::InsertButton(CheckBox* pBox, int nIndex, const char* strCaption /* = NULL */)
{
	if (pBox->getParent())
		pBox->removeFromParentAndCleanup(false);

	addChild(pBox);

	Point pLastPoint;
	if (m_bRelayout)
	{
		pLastPoint.x = (m_vtrButtons.size() ? m_vtrButtons.back()->getPosition().x + (m_eAlign == RBS_ALIGN_LATERAL ?  m_buttonSize.width+m_nInterval : 0.0f) : m_buttonSize.width / 2);
		pLastPoint.y  = (m_vtrButtons.size() ? m_vtrButtons.back()->getPosition().y + (m_eAlign == RBS_ALIGN_VERTICAL ?  m_buttonSize.height+m_nInterval : 0.0f) : m_buttonSize.height / 2);
	}
	else
	{
		if (m_vtrButtons.size() == 0)
		{
			m_OffsetBase = pBox->getPosition();
		}
		pBox->setPosition(pBox->getPosition() - m_OffsetBase);
		setPosition(m_OffsetBase);
	}
	if (strCaption)
	{
		Label* lable = Label::create();
		lable->setString(strCaption);
		//lable->setFontSize(m_nFontSize);
		pBox->addChild(lable);
	}

	pBox->addEventListenerCheckBox(this, SEL_SelectedStateEvent(&RadioButtonSet::ClickButton));

	m_vtrButtons.insert(m_vtrButtons.begin()+nIndex,pBox);
	m_vtrPoints.push_back(pLastPoint);

	if(m_bRelayout) Layout();
}

void RadioButtonSet::RemButton(int nIndex)
{
	if (nIndex >= (int)m_vtrButtons.size() || nIndex < 0)
		return;

	removeChild(GetButton(nIndex));
	m_vtrButtons.erase(m_vtrButtons.begin()+nIndex);

	Layout();

	m_vtrPoints.resize(m_vtrPoints.size()-1);
}

void RadioButtonSet::RemButton(int nFrom, int nTo)
{
	if (nTo < nFrom) return;
	if (nFrom >= (int)m_vtrButtons.size() || nFrom < 0) return;
	if (nTo >= (int)m_vtrButtons.size() || nTo < 0) return;

	for (int i=nFrom; i<=nTo; ++i)
	{
		removeChild(GetButton(i));
		m_vtrButtons.erase(m_vtrButtons.begin()+i);
	}
	Layout();

	m_vtrPoints.resize(m_vtrPoints.size()-(nTo-nFrom+1));
}

void RadioButtonSet::Layout()
{
	for (unsigned int i=0; i<m_vtrButtons.size(); ++i)
	{
		m_vtrButtons[i]->setPosition(m_vtrPoints[i]);
	}
}

CheckBox* RadioButtonSet::GetButton(int nIndex)
{
	if (nIndex >= (int)m_vtrButtons.size())
		return NULL;

	return m_vtrButtons[nIndex];
}

void RadioButtonSet::ClickButton(Ref *pSender, CheckBoxEventType type)
{
	if (m_pCurSel)
	{
		m_pCurSel->setSelectedState(false);
		m_pCurSel->setBrightStyle(BRIGHT_NORMAL);
		gCocosAudio->PlayEffect(129);
	}

	((CheckBox*)pSender)->setSelectedState(true);
			
	if (m_pCurSel == pSender)
		return;

	m_pCurSel = (CheckBox*)pSender;

	if (m_SelHandler && m_SelListener)
	{
		(m_SelListener->*m_SelHandler)(pSender, type);
	}
	if (m_SelHandlerI && m_SelListenerI)
	{
		vector<CheckBox*>::iterator it = std::find(m_vtrButtons.begin(), m_vtrButtons.end(), pSender);
		(m_SelListenerI->*m_SelHandlerI)(it - m_vtrButtons.begin());
	}
}

void RadioButtonSet::ClickButton(int nIndex)
{
	if (nIndex < (int)m_vtrButtons.size())
	{
		ClickButton(m_vtrButtons[nIndex], CHECKBOX_STATE_EVENT_SELECTED);
	}
}

void RadioButtonSet::SetSelectButton(int nIndex)
{
	if (nIndex < (int)m_vtrButtons.size())
	{
		if (m_pCurSel == m_vtrButtons[nIndex])
			return;

		if (m_pCurSel)
		{
			//m_pCurSel->setTouchEnabled(true);
			m_pCurSel->setSelectedState(false);
		}
		if (nIndex < 0)
		{
			m_pCurSel = NULL;
			return;
		}

		m_pCurSel = m_vtrButtons[nIndex];
		//m_pCurSel->setTouchEnabled(false);
		m_pCurSel->setSelectedState(true);
	}
}

int RadioButtonSet::GetSelIndex()			
{
	vector<CheckBox*>::iterator it = std::find(m_vtrButtons.begin(), m_vtrButtons.end(), m_pCurSel);
	return (it == m_vtrButtons.end() ? -1 : (it - m_vtrButtons.begin()));
}

void RadioButtonSet::ClearSelState()
{
	if (m_pCurSel)
	{
		m_pCurSel->setSelectedState(false);
		m_pCurSel = NULL;
	}
}

void RadioButtonSet::Clear()
{
	removeAllChildrenWithCleanup(true);
	m_vtrButtons.clear();
	m_vtrPoints.clear();
	m_pCurSel = NULL;
}

void RadioButtonSet::SetSelectEvent(Ref *target, SEL_SelectedStateEvent selector)
{
	m_SelHandler = selector;
	m_SelListener = target;
}

void RadioButtonSet::SetSelectEvent(Ref* target,SEL_SelectIndexEvent selector)
{
	m_SelHandlerI = selector;
	m_SelListenerI = target;
}