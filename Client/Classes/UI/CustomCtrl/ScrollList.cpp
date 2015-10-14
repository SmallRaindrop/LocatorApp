#include "ScrollList.h"
#include "ui/UIText.h"
#include "ui/UIButton.h"

CScrollList::CScrollList(void): m_bItemSelectable(), m_SelHandler(), m_SelListener(), m_SelHandlerI(), 
	m_SelListenerI(), m_nFontSize(20), m_nSelIndex(-1), m_pCurSel(), m_nRowInterval(), m_bDBClickEnabled(),
	m_fDBC1thClickLastTime(), m_bDBClick1thClicked(), m_textAlign(TextHAlignment::CENTER), m_nGroupBGID("Image_list_classify")
{
	m_clrTextNormal = _color;
	m_bGourpBGClickable = false;
}


CScrollList::~CScrollList(void)
{
}

Widget* CScrollList::AddItem(const char* strCaption, long long nUserData)
{
	Widget *pBox = NULL;

	pBox = gCtrlAllocator->LoadCtrl(m_nItemBGID);
	if (!pBox)
		return NULL;

	pBox->setSize(Size(_size.width, pBox->getSize().height));

	if (m_bItemSelectable)
	{
		((CheckBox*)pBox)->addEventListenerCheckBox(this, SEL_SelectedStateEvent(&CScrollList::ClickButton));
	}
	else
	{
		((Button*)pBox)->addTouchEventListener(this, SEL_TouchEvent(&CScrollList::ClickButton));
	}

	Text *pText = Text::create();
	pText->setFontSize(m_nFontSize);
	pText->setSize(Size(_size.width, pBox->getSize().height));
	pText->ignoreContentAdaptWithSize(false);
	pText->setTag(999);
	pText->setColor(m_clrTextNormal);
	pText->setText(strCaption);
	pText->setTextAreaSize(pText->getSize());
	pText->setTextHorizontalAlignment(m_textAlign);
	pText->setTextVerticalAlignment(TextVAlignment::CENTER);
	pText->setPosition(Point(getSize().width / 2, pBox->getSize().height / 2));
	if (!m_bTextShadow)((Label*)pText->getVirtualRenderer())->disableEffect();
	pBox->addChild(pText);
	pBox->setAnchorPoint(Point(0.0f, 1.0f));
	addChild(pBox);






	// 先将设定新行在组里面的信息
	int nGlobalIndex = m_vtrButtons.size();
	GroupInfo *pGroup = GetGroup(m_strCurGroup);
	if (pGroup)
	{
		if (pGroup->pStartItem == NULL)
		{
			pGroup->pStartItem = pBox;
		}
		else
		{
			nGlobalIndex = find(m_vtrButtons.begin(), m_vtrButtons.end(), pGroup->pStartItem) - m_vtrButtons.begin() + pGroup->nItemNum;
		}
		pGroup->nItemNum++;
	}
	
	// 再根据组的信息插入到该组最后一个位置
	//m_vtrButtons.insert(nGlobalIndex, pBox);
	m_vtrButtons.insert(m_vtrButtons.begin()+nGlobalIndex,pBox);
	m_vtrUserData.insert(m_vtrUserData.begin() + nGlobalIndex, nUserData);

	LayOut();

	return pBox;
}

void CScrollList::LayOut()
{
	int nItemHeight = (m_vtrButtons.size() ? m_vtrButtons.back()->getSize().height : 0);
	int nTitleHeight = (m_vtrGroupInfo.size() ? m_vtrGroupInfo.back().pGroupTitle->getSize().height : 0);

	float minHeight = 0;
	for (size_t i = 0; i < m_vtrGroupInfo.size(); i++)
	{
		if (m_vtrGroupInfo[i].bSpread && m_vtrGroupInfo[i].nItemNum)
			minHeight += (m_vtrGroupInfo[i].nItemNum * nItemHeight + (m_vtrGroupInfo[i].nItemNum - 1) * m_nRowInterval);
		minHeight += (nTitleHeight + m_nRowInterval);
	}
	if (minHeight == 0)
	{
		minHeight = m_vtrButtons.size() * nItemHeight + (nItemHeight ? (m_vtrButtons.size() - 1) * m_nRowInterval : 0);
	}

	float fRealHeight = MAX(minHeight, getContentSize().height);
	int nCurPlaceY = fRealHeight;

	// 计算全体成员的位置
	vector<GroupInfo> vtrGroupTemp = m_vtrGroupInfo;
	int nGroupIndex = -1;
	for (ssize_t i = 0; i < m_vtrButtons.size(); i++)
	{
		bool bSpreadItem = true;
		for (size_t j = 0; j < vtrGroupTemp.size(); j++)
		{
			if (vtrGroupTemp[j].pStartItem == m_vtrButtons.at(i))
			{
				// 排版没有列表项目的组标题栏
				for (size_t k = 1; k <= j - nGroupIndex; k++)
				{
					vtrGroupTemp[nGroupIndex + k].pGroupTitle->setPosition(Point(_size.width / 2, nCurPlaceY));
					nCurPlaceY -= (vtrGroupTemp[nGroupIndex + k].pGroupTitle->getSize().height + m_nRowInterval);
				}
				nGroupIndex = j;

				if (!vtrGroupTemp[j].bSpread)
				{
					// 隐藏折叠的项
					for (ssize_t k = 0; k < vtrGroupTemp[j].nItemNum; k++)
					{
						m_vtrButtons.at(i + k)->removeFromParentAndCleanup(false);
					}

					i += (vtrGroupTemp[j].nItemNum - 1);
					bSpreadItem = false;
				}
				else if (vtrGroupTemp[j].nItemNum && vtrGroupTemp[j].pStartItem->getParent() == NULL)
				{
					// 显示之前折叠的项
					for (ssize_t k = 0; k < vtrGroupTemp[j].nItemNum; k++)
					{
						addChild(m_vtrButtons.at(i + k));
					}
				}

				break;
				//vtrGroupTemp.erase(vtrGroupTemp.begin() + j);
			}
		}

		if (bSpreadItem)
		{
			m_vtrButtons.at(i)->setPosition(Point(0, nCurPlaceY));
			nCurPlaceY -= (nItemHeight + m_nRowInterval);
		}
	}

	// 排版剩下的没有列表项目的组标题栏
	for (size_t k = nGroupIndex + 1; k < vtrGroupTemp.size(); k++)
	{
		vtrGroupTemp[k].pGroupTitle->setPosition(Point(_size.width / 2, nCurPlaceY));
		nCurPlaceY -= (vtrGroupTemp[k].pGroupTitle->getSize().height + m_nRowInterval);
	}

	setInnerContainerSize(Size(getContentSize().width, fRealHeight));
}

Widget* CScrollList::GetItem(int nIndex)
{
	if (nIndex == -1)
		return (m_vtrButtons.size() ? m_vtrButtons.back() : NULL);
	if (nIndex < (int)m_vtrButtons.size() && nIndex > -1)
		return m_vtrButtons.at(nIndex);
	return NULL;
}

Widget* CScrollList::GetItemByUserDate(long long nUserData)
{
	for (size_t i=0; i<m_vtrUserData.size(); ++i)
	{
		if (nUserData == m_vtrUserData[i])
		{
			return GetItem(i);
		}
	}
	return NULL;
}

CScrollList::GroupInfo* CScrollList::GetGroup(string strGroupName)
{
	for (size_t i = 0; i < m_vtrGroupInfo.size(); i++)
	{
		if (m_vtrGroupInfo[i].strGroupName == strGroupName)
		{
			return &m_vtrGroupInfo[i];
		}
	}

	return NULL;
}

void CScrollList::SetCurGroup(string strGroupName)
{
	bool bExist = false;
	if (GetGroup(strGroupName) == NULL)
	{
		GroupInfo group = {strGroupName, NULL, NULL, 0, true};
		group.pGroupTitle = gCtrlAllocator->LoadCtrl(m_nGroupBGID);
		if (group.pGroupTitle)
		{
			Text *pText = Text::create(strGroupName, "Helvetica", m_nFontSize);
			Size szTitle = group.pGroupTitle->getSize();
			pText->setPosition(Point(szTitle.width / 2, szTitle.height / 2));
			pText->setColor(Color3B(0xEA, 0xC1, 0x84));
			group.pGroupTitle->addChild(pText);
			group.pGroupTitle->setAnchorPoint(Point(0.5, 1.f));
			group.pGroupTitle->setTag(m_vtrGroupInfo.size());
			group.pGroupTitle->setTouchEnabled(true);
			group.pGroupTitle->addTouchEventListener(m_bGourpBGClickable ? this : 0, SEL_TouchEvent(&CScrollList::ClickGroupTitle));
			addChild(group.pGroupTitle);
			m_vtrGroupInfo.push_back(group);
			m_strCurGroup = strGroupName;

			LayOut();
		}
	}
}

void CScrollList::ClickGroupTitle(Ref* pSender,TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		size_t nGroupIndex = ((Widget*)pSender)->getTag();
		if (m_vtrGroupInfo.size() > nGroupIndex)
		{
			m_vtrGroupInfo[nGroupIndex].bSpread = !m_vtrGroupInfo[nGroupIndex].bSpread;
			LayOut();
		}
	}
}

void CScrollList::ClickButton(Ref* pSender,CheckBoxEventType type)
{
	if (dynamic_cast<Widget*> (pSender) && type == CHECKBOX_STATE_EVENT_SELECTED)
	{
		if (m_bItemSelectable)
		{
			UnSelected();
			m_pCurSel = (CheckBox*)pSender;
			m_pCurSel->getChildByTag(999)->setColor(m_clrTextSelected);
			((CheckBox*)m_pCurSel)->setSelectedState(true);
		}

		if (m_SelHandler && m_SelListener)
		{
			(m_SelListener->*m_SelHandler)(pSender, TOUCH_EVENT_ENDED);
		}
		if (m_SelHandlerI && m_SelListenerI)
		{
			vector<Widget*>::iterator it = std::find(m_vtrButtons.begin(), m_vtrButtons.end(), pSender);
			m_nSelIndex = it - m_vtrButtons.begin();

			(m_SelListenerI->*m_SelHandlerI)(m_nSelIndex, m_vtrUserData[m_nSelIndex]);
		}
	}
}

void CScrollList::ClickButton(Ref* pSender,TouchEventType type)
{
	Button *pSel = dynamic_cast<Button*> (pSender);
	if (pSel == NULL)
		return;

	if(type == TOUCH_EVENT_ENDED)
	{
		m_pCurSel = pSel;
		pSel->getChildByTag(999)->setColor(m_clrTextNormal);

		// 双击
		if (m_bDBClickEnabled)
		{
			if (m_bDBClick1thClicked)
			{
				if (m_fDBC1thClickLastTime > 0.3f)
				{
					m_fDBC1thClickLastTime = 0;
					m_bDBClick1thClicked = true;
				}
				else
				{
					if (m_DBCHandlerI && m_DBCListenerI)
					{
						vector<Widget*>::iterator it = std::find(m_vtrButtons.begin(), m_vtrButtons.end(), pSender);
						int nIndex = it - m_vtrButtons.begin();

						(m_DBCListenerI->*m_DBCHandlerI)(nIndex, m_vtrUserData[nIndex]);

						m_fDBC1thClickLastTime = 0.f;
						m_bDBClick1thClicked = false;

						return;
					}
				}
			}
			else
			{
				m_bDBClick1thClicked = true;
				m_fDBC1thClickLastTime = 0.f;
			}
		}
		else
		{
			if (m_SelHandler && m_SelListener)
			{
				(m_SelListener->*m_SelHandler)(pSender, TOUCH_EVENT_ENDED);
			}
			if (m_SelHandlerI && m_SelListenerI)
			{
				vector<Widget*>::iterator it = std::find(m_vtrButtons.begin(), m_vtrButtons.end(), pSender);
				int nIndex = it - m_vtrButtons.begin();

					(m_SelListenerI->*m_SelHandlerI)(nIndex, m_vtrUserData[nIndex]);
			}
		}
	}
	else if (type == TOUCH_EVENT_BEGAN)
	{
		pSel->getChildByTag(999)->setColor(m_clrTextSelected);
	}
	else if (type == TOUCH_EVENT_CANCELED)
	{
		pSel->getChildByTag(999)->setColor(m_clrTextNormal);
	}
}

void CScrollList::ClickButton(int nIndex)
{
	if (nIndex < (int)m_vtrButtons.size())
	{
		if (m_bItemSelectable)
			ClickButton(m_vtrButtons.at(nIndex), CHECKBOX_STATE_EVENT_SELECTED);
		else
			ClickButton(m_vtrButtons.at(nIndex), TOUCH_EVENT_ENDED);
	}
}

void CScrollList::UnSelected()
{
	if (m_pCurSel)
	{
		m_pCurSel->getChildByTag(999)->setColor(m_clrTextNormal);
		((CheckBox*)m_pCurSel)->setSelectedState(false);
	}
}

void CScrollList::Clear()
{
	removeAllChildrenWithCleanup(true);
	m_vtrButtons.clear();
	m_vtrGroupInfo.clear();
	m_vtrUserData.clear();
	m_pCurSel = NULL;
}

void CScrollList::SetSelectEvent(Ref* target,SEL_TouchEvent selector)
{
	m_SelHandler = selector;
	m_SelListener = target;
}

void CScrollList::SetSelectEvent(Ref* target,SEL_SelListIndexEvent selector)
{
	m_SelHandlerI = selector;
	m_SelListenerI = target;
}

void CScrollList::SetDBClickEvent(Ref* target,SEL_SelListIndexEvent selector)
{
	m_DBCHandlerI = selector;
	m_DBCListenerI = target;
}

void CScrollList::update(float dt)
{
	ScrollView::update(dt);

	if (m_bDBClick1thClicked)
		m_fDBC1thClickLastTime += dt;

	if (m_fDBC1thClickLastTime > 0.3f)
	{
		if (std::find(m_vtrButtons.begin(), m_vtrButtons.end(), m_pCurSel) != m_vtrButtons.end())
		{
			if (m_SelHandler && m_SelListener)
			{
				(m_SelListener->*m_SelHandler)(m_pCurSel, TOUCH_EVENT_ENDED);
			}
			if (m_SelHandlerI && m_SelListenerI)
			{
				vector<Widget*>::iterator it = std::find(m_vtrButtons.begin(), m_vtrButtons.end(), m_pCurSel);
				int nIndex = it - m_vtrButtons.begin();

				(m_SelListenerI->*m_SelHandlerI)(nIndex, m_vtrUserData[nIndex]);
			}
		}
		m_fDBC1thClickLastTime = 0.f;
		m_bDBClick1thClicked = false;
	}
}


