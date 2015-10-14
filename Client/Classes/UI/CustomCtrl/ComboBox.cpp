#include "ComboBox.h"
#include "GameScene/GameUILayer.h"



CMenu::CMenu(void): m_SelHandler(), m_SelListener(), m_SelHandlerI(), m_SelListenerI(),
	m_nInterval(), m_pBG(), m_eAlign(IA_VERTICAL)
{
	m_bDynamicShow = true;
}


CMenu::~CMenu(void)
{
}

CMenu* CMenu::create(string nItemBGID, string nBGID, int nInterval)
{
	CMenu* rw = new CMenu();
	if(rw && rw->init())
	{
		rw->SetItemBGID(nItemBGID);
		rw->_setBGID(nBGID);
		rw->_setInterval(nInterval);
		rw->setTouchEnabled(true);
		rw->Clear();

		//Size winsize = CCDirector:: getInstance()->getVisibleSize(); 
		//Size wigsize = Size(1920, 1080);
		//float fScale = MIN(winsize.width / wigsize.width, winsize.height / wigsize.height);
		//rw->setScale(fScale);
		rw->autorelease();
		return rw;
	}
	CC_SAFE_DELETE(rw);
	return NULL;
}

void CMenu::PopupMenu(Point pos, Ref* pListenner, SEL_SelectIndexEvent pHandler, const char* strItem1, ...)
{
	va_list va;
	va_start(va, strItem1);

	gMenuInst->Clear();
	gMenuInst->setPosition(pos);

	const char *pTmp = strItem1;
	do
	{
		gMenuInst->AddItem(pTmp);
	}
	while (pTmp = va_arg(va, const char*));

	gMenuInst->SetSelectEvent(pListenner, pHandler);
}

void CMenu::AddItem(const char* strCaption, bool bDisabled)
{
	Button *pBox = (Button*)gCtrlAllocator->LoadCtrl(m_nItemBGID);
	if (!pBox)
		return;

	if (pBox->getParent())
		pBox->removeFromParentAndCleanup(false);

	addChild(pBox);
	pBox->setBright(!bDisabled);
	//pBox->setTouchEnabled(!bDisabled);
	pBox->setAnchorPoint(m_eAlign == IA_VERTICAL ? Point(0.5f, 1.0f) : Point(0.0f, 0.5f));
	pBox->setTitleColor(Color3B(250, 235, 180));
	if (!bDisabled) pBox->addTouchEventListener(this, SEL_TouchEvent(&CMenu::ClickButton));

	if (m_eAlign == IA_VERTICAL)
	{
		float y = (m_vtrButtons.size() ? m_vtrButtons.back()->getPosition().y : pBox->getSize().height) - pBox->getSize().height - (m_vtrButtons.size() ? m_nInterval : 0);
		pBox->setPosition(Point(0, y));
	}
	else
	{
		float x = (m_vtrButtons.size() ? m_vtrButtons.back()->getPosition().x : -pBox->getSize().width) + pBox->getSize().width + (m_vtrButtons.size() ? m_nInterval : 0);
		pBox->setPosition(Point(x, 0));
	}

	if (strCaption)
	{
		//pBox->setTitleFontSize(40);
		pBox->setTitleText(strCaption);
	}


	m_vtrButtons.push_back(pBox);

	if (m_pBG)
	{
		float intervalSum = m_vtrButtons.size()>1?m_nInterval*(m_vtrButtons.size()-1):0;
		if (m_eAlign == IA_VERTICAL)
		{
			m_pBG->setSize(Size(pBox->getSize().width + 20, pBox->getSize().height * m_vtrButtons.size() + intervalSum + 20));
			m_pBG->setPositionY(-m_pBG->getSize().height / 2 + 10);
		}
		else
		{
			m_pBG->setSize(Size(pBox->getSize().width * m_vtrButtons.size() + intervalSum + 20, pBox->getSize().height + 20));
			m_pBG->setPositionX(m_pBG->getSize().width / 2 - 10);
		}
		m_pBG->setVisible(true);
	}
}

void CMenu::ClickButton(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (m_SelHandler && m_SelListener)
		{
			(m_SelListener->*m_SelHandler)(pSender, type);
		}
		if (m_SelHandlerI && m_SelListenerI)
		{
			vector<Button*>::iterator it = std::find(m_vtrButtons.begin(), m_vtrButtons.end(), pSender);
			(m_SelListenerI->*m_SelHandlerI)(it - m_vtrButtons.begin());
		}

		if(m_bDynamicShow)
		{
			pSender->retain();
			pSender->autorelease();	// 本次按钮事件执行完毕之前按钮不能被删除，否则本函数返回后发现按钮事件已经被撤销，点击事件会继续下去
			Clear();
		}
	}

}

void CMenu::ClickButton(int nIndex)
{
	if (nIndex < (int)m_vtrButtons.size())
	{
		ClickButton(m_vtrButtons[nIndex], TOUCH_EVENT_ENDED);
	}
}

void CMenu::Clear()
{
	//removeAllChildrenWithCleanup(true);
	for (size_t i = 0; i < m_vtrButtons.size(); i++)
	{
		m_vtrButtons[i]->removeFromParent();
	}
	if (m_pBG) m_pBG->setVisible(false);
	m_vtrButtons.clear();
}

void CMenu::SetSelectEvent(Ref* target,SEL_TouchEvent selector)
{
	m_SelHandler = selector;
	m_SelListener = target;
}

void CMenu::SetSelectEvent(Ref* target,SEL_SelectIndexEvent selector)
{
	m_SelHandlerI = selector;
	m_SelListenerI = target;
}

bool CMenu::onTouchBegan(Touch *touch, Event *unusedEvent)
{
	if(m_bDynamicShow)
	{
		Clear();
	}
	return false;
}







//-----------------------------------------------CComboBox----------------------------------------------------------

CComboBox* CComboBox::create(string nTextBoxID, string nItemBGID, int nInterval)
{
	CComboBox* rw = new CComboBox();
	if(rw && rw->init())
	{
		rw->m_pMenu = CMenu::create(nItemBGID, "", nInterval);
		if (rw->m_pMenu == NULL)
			return NULL;
		
		rw->m_pMenu->SetSelectEvent(rw, SEL_SelectIndexEvent(&CComboBox::ItemClicked));
		if (!rw->_loadTextBox(nTextBoxID))
		{
			return NULL;
		}
		rw->m_pMenu->setVisible(false);
		rw->m_pMenu->SetItemBGID(nItemBGID);
		rw->m_pMenu->_setInterval(nInterval);
		rw->m_pMenu->setPosition(Point(rw->m_pTextBox->getContentSize().width / 2, -rw->m_pTextBox->getContentSize().height));
		rw->m_pTextBox->addChild(rw->m_pMenu);
		return rw;
	}
	CC_SAFE_DELETE(rw);
	return NULL;
}

void CComboBox::AddItem(const char* strCaption)
{
	m_pMenu->AddItem(strCaption);
}

void CComboBox::Clear()
{
	m_pMenu->Clear();
	m_pTextBox->setTitleText("");
}

void CComboBox::SetSelectEvent(Ref* target,SEL_SelectIndexEvent selector)
{
	m_SelHandlerI = selector;
	m_SelListenerI = target;
}

void CComboBox::TextBoxClicked(Ref* pSender)
{
	m_pMenu->setVisible(!m_pMenu->isVisible());
}

void CComboBox::ItemClicked(int nIndex)
{
	m_pTextBox->setTitleText(m_pMenu->m_vtrButtons[nIndex]->getTitleText());
	if (m_SelHandlerI && m_SelListenerI)
		(m_SelListenerI->*m_SelHandlerI)(nIndex);

	m_pMenu->setVisible(false);
}







//----------------------------------------------------------------------------
CAlternateSelecter* CAlternateSelecter::create(int nInterval)
{
	CAlternateSelecter* rw = new CAlternateSelecter();
	if(rw && rw->init())
	{
		rw->m_pMenu = CMenu::create("", "", nInterval);
		if (rw->m_pMenu == NULL)
			return NULL;
		
		rw->m_pMenu->SetSelectEvent(rw, SEL_SelectIndexEvent(&CAlternateSelecter::ItemClicked));
		rw->m_pMenu->_setInterval(nInterval);
		rw->addChild(rw->m_pMenu);
		return rw;
	}
	CC_SAFE_DELETE(rw);
	return NULL;
}

void CAlternateSelecter::AddItem(const char* strItemBG)
{
	m_vtrItemBG.push_back(strItemBG);
	LayOut(false);
}

void CAlternateSelecter::Clear()
{
	m_pMenu->Clear();
	m_vtrItemBG.clear();
	m_nSelIndex = -1;
}

void CAlternateSelecter::LayOut(bool bSetMenu)
{
	if (m_nSelIndex == -1)
	{
		if (m_vtrItemBG.size())
		{
			m_pRootBox = (Button*)gCtrlAllocator->LoadCtrl(m_vtrItemBG[0]);
			m_nSelIndex = 0;
		}
	}
	else
	{
		if (m_pRootBox->getName() != m_vtrItemBG[m_nSelIndex])
		{
			m_pRootBox->removeFromParent();
			m_pRootBox = (Button*)gCtrlAllocator->LoadCtrl(m_vtrItemBG[m_nSelIndex]);
		}
	}

	if (m_pRootBox == NULL)
		return;

	if (m_pRootBox->getParent() == NULL)
	{
		m_pRootBox->addTouchEventListener(this, SEL_TouchEvent(&CAlternateSelecter::RootBoxClicked));
		addChild(m_pRootBox);
	}

	if (bSetMenu)
	for (size_t i = 0; i < m_vtrItemBG.size(); i++)
	{
		if (i != m_nSelIndex)
		{
			m_pMenu->SetItemBGID(m_vtrItemBG[i]);
			m_pMenu->AddItem("");
		}
	}

	if (m_pMenu->m_eAlign == CMenu::IA_VERTICAL)
	{
		m_pMenu->setPositionY(m_pRootBox->getSize().height);
	}
	else
	{
		m_pMenu->setPositionX(m_pRootBox->getSize().width);
	}
}

void CAlternateSelecter::SetSelectItem(int nIndex)
{
	if ((int)m_vtrItemBG.size() > nIndex)
	{
		m_nSelIndex = nIndex;
		LayOut(false);
	}
}

void CAlternateSelecter::SetSelectEvent(Ref* target,SEL_SelectIndexEvent selector)
{
	m_SelHandlerI = selector;
	m_SelListenerI = target;
}

void CAlternateSelecter::RootBoxClicked(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (m_pMenu->m_vtrButtons.size() == 0)
		{
			LayOut(true);
		}
		else
		{
			m_pMenu->Clear();
		}
	}
}

void CAlternateSelecter::ItemClicked(int nIndex)
{
	m_nSelIndex = nIndex < m_nSelIndex ? nIndex : nIndex + 1;

	LayOut(false);

	if (m_SelHandlerI && m_SelListenerI)
		(m_SelListenerI->*m_SelHandlerI)(m_nSelIndex);
}
