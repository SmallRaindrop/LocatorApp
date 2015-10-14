#include "PageNum.h"
#include "UILayout.h"
#include "RadioButtonSet.h"
#include "../ResMgr/CtrlAllocator.h"

PageNum::PageNum()
{

}

PageNum::~PageNum()
{

}

bool PageNum::init()
{
	setSize(Size(560,60));
	m_pPageSigns = RadioButtonSet::create();
	addChild(m_pPageSigns);
	m_pPageNum = Text::create();
	m_pPageNum->setSize(Size(150,46));
	m_pPageNum->setFontSize(36);
	m_pPageNum->ignoreContentAdaptWithSize(false);
	addChild(m_pPageNum);
	return true;
}


void PageNum::setPageNum(int nPageNum)
{
	m_pPageSigns->Clear();
	m_nPageSum = nPageNum;
	int signLen = (m_nPageSum-1)*60;
	for (int i=0; i<m_nPageSum; ++i)
	{
		CheckBox* pPageSign = (CheckBox*)gCtrlAllocator->LoadCtrl("PageSign");
		pPageSign->setTouchEnabled(false);
		pPageSign->setPosition(Point(-signLen/2+i*60,0));
		m_pPageSigns->AddButton(pPageSign);
	}
	m_pPageNum->setPosition(m_pPageSigns->GetButton(m_nPageSum-1)->getPosition()+Point(120,0));
	m_pPageNum->setText(CCString::createWithFormat("%d/%d",1,m_nPageSum)->getCString());
	m_pPageSigns->ClickButton(0);
}

void PageNum::turnToPage(int index)
{
	m_pPageNum->setText(CCString::createWithFormat("%d/%d",index+1,m_nPageSum)->getCString());
	m_pPageSigns->ClickButton(index);
}