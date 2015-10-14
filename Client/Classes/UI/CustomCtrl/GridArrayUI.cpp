#include "GridArrayUI.h"
#include "GameScene/GameUILayer.h"
#include "../../cocos2d/cocos/editor-support/cocostudio/CCSGUIReader.h"
#include "GameScene/GridsManager.h"
#include "CdCtrol.h"
#include "UI/MessageBoxUI.h"
#include "Net/NetDispatcher.h"

using namespace cocostudio;

#define Tag_UnActive_ui		(100)
#define Path_UnActive_Img	("assets/ui/common/gridDisable.png")

CGridArrayUI::CGridArrayUI():m_nIndexOffset(0),m_nCapacity(0),m_pWidget(NULL),m_bShowMask(true),m_bCanMove(false),m_bDynamicShow(false)
{
	m_iconVec.resize(0);
}

CGridArrayUI::~CGridArrayUI()
{
	//gGridsManager->detachUI(m_gridType);
	//removeAllGridUIs();
	//m_iconVec.clear();
	//m_iconBGVec.clear();
}


CGridArrayUI* CGridArrayUI::create(emGridsType gridsType,int indexOffset,int capacity,Widget* pGridUI,bool bDynamicShow,bool bCanMove)
{
	CGridArrayUI* widget = new CGridArrayUI();
	if (widget&&widget->init(gridsType,indexOffset,capacity,pGridUI,bDynamicShow,bCanMove))
	{
		widget->autorelease();
		return widget;
	}

	CC_SAFE_DELETE(widget);
	return NULL;
}

CGridArrayUI* CGridArrayUI::create(emGridsType gridsType, int totalGrid, int linegrid, ScrollView * _scrollview)
{
	CGridArrayUI* widget = new CGridArrayUI();
	if(widget&&widget->init(gridsType, totalGrid, linegrid, _scrollview))
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return widget;
}


bool CGridArrayUI::init(emGridsType gridsType,int indexOffset,int capacity,Widget* pGridUI,bool bDynamicShow,bool bCanMove)
{
	if ( !Layout::init() || !pGridUI)
	{
		return false;
	}

	m_gridType = gridsType;
	m_nIndexOffset = indexOffset;
	m_nCapacity = capacity;

	//m_bShowMask = bShowMask;
	m_bDynamicShow = bDynamicShow;
	m_bCanMove = bCanMove;

	m_pWidget = pGridUI;
	setPosition(m_pWidget->getPosition());
	m_pWidget->removeFromParentAndCleanup(false);
	addChild(m_pWidget);
	m_pWidget->setPosition(Point::ZERO);
	setSize(m_pWidget->getSize());
	
	reset();

	return true;
}

bool CGridArrayUI::init(emGridsType gridsType, int totalGrid, int linegrid,ScrollView * _scrollview)
{
	if(!Layout::init() && _scrollview) return false;

	m_gridType = gridsType;
	m_nCapacity = totalGrid;
	m_pWidget = _scrollview->clone();

	m_nIndexOffset = linegrid;

	//设置容器层的大小
	Size size = _scrollview->getInnerContainerSize();
	int cnt = ceil(totalGrid/_scrollview->getInnerContainer()->getChildrenCount());
	setSize(Size(size.width, size.height * cnt));
	resetScroll();
	return true;
}

void CGridArrayUI::reset()
{
	m_iconVec.clear();
	m_iconBGVec.clear();
	m_iconVec.resize(m_nCapacity);
	m_iconBGVec.resize(m_nCapacity);

	char str[8] = {};
	CItemGridArray* pGridsData = gGridsManager->getGridsData(m_gridType);
	for (int i=0; i<m_nCapacity; ++i)
	{
		sprintf(str,"%d",i);
		Widget* pGridUI = Helper::seekWidgetByName(m_pWidget,str);
		pGridUI->removeChildByTag(Tag_UnActive_ui);
		m_iconBGVec[i]=pGridUI;

		CItemGrid* pItemGrid = pGridsData->GetItemGrid(m_nIndexOffset+i);
		if(!pItemGrid) continue;

		if (!pItemGrid->IsActive())
		{
			ImageView* pUnActiveUI = ImageView::create(Path_UnActive_Img);
			pUnActiveUI->setPosition(Point(66,66));
			pUnActiveUI->setTag(Tag_UnActive_ui);
			m_iconBGVec[i]->setTouchEnabled(true);
			m_iconBGVec[i]->addTouchEventListener(this,toucheventselector(CGridArrayUI::clickGridActive));
			m_iconBGVec[i]->addChild(pUnActiveUI);		
		} 
		else if(pItemGrid->IsActive()&&pItemGrid->GetItem())
		{
			CGridIcon* pGridIcon = CGridIcon::create(pItemGrid->GetItem(),m_nIndexOffset+i,m_gridType,m_bCanMove);
			if (pGridIcon)
			{
				pGridUI->addChild(pGridIcon);
				pGridIcon->setPosition(Point(pGridUI->getSize().width/2,pGridUI->getSize().height/2));	
				m_iconVec[i]=pGridIcon;
			}
		}

		if (m_bDynamicShow)
		{
			m_iconBGVec[i]->setVisible(NULL != m_iconVec[i]);
		}
	}
}

void CGridArrayUI::resetScroll()
{
	m_iconVec.clear();
	m_iconBGVec.clear();
	m_iconVec.resize(m_nCapacity);
	m_iconBGVec.resize(m_nCapacity);
	if(!m_pWidget) return ;
	auto inner = dynamic_cast<ScrollView*>(m_pWidget)->getInnerContainer();
	int childcnt  = inner->getChildrenCount();
	//获取第一个节点的位置 startpos
	//计算横向间隔dis_X
	//获取竖向间隔dis_Y
	if(childcnt <= 0) return;
	Widget * childParent = dynamic_cast<Widget*>(inner->getChildren().at(0));
	Point startpos = childParent->getPosition();
	int   dis_X    = inner->getChildren().at(1)->getPositionX() - startpos.x;
	int   dis_Y    = startpos.y - inner->getChildren().at(m_nIndexOffset)->getPositionY();
	if(childcnt > m_nCapacity) return ;
	CItemGridArray* pGridsData = gGridsManager->getGridsData(m_gridType);
	for (int i = 0; i < m_nCapacity; i++)
	{
		m_iconBGVec[i]= childParent->clone();
		m_iconBGVec[i]->removeAllChildren();
		CItemGrid* pItemGrid = pGridsData->GetItemGrid(i);
		if(!pItemGrid) continue;

		if (!pItemGrid->IsActive())
		{
			ImageView* pUnActiveUI = ImageView::create(Path_UnActive_Img);
			pUnActiveUI->setPosition(Point(66,66));
			pUnActiveUI->setTag(Tag_UnActive_ui);
			m_iconBGVec[i]->setTouchEnabled(true);
			m_iconBGVec[i]->addTouchEventListener(this,toucheventselector(CGridArrayUI::clickGridActive));
			m_iconBGVec[i]->addChild(pUnActiveUI);		
		} 
		else if(pItemGrid->IsActive()&&pItemGrid->GetItem())
		{
			CGridIcon* pGridIcon = CGridIcon::create(pItemGrid->GetItem(),i,m_gridType,m_bCanMove);
			if (pGridIcon)
			{
				m_iconBGVec[i]->addChild(pGridIcon);
				pGridIcon->setPosition(Point(m_iconBGVec[i]->getSize().width/2,m_iconBGVec[i]->getSize().height/2));	
				m_iconVec[i]=pGridIcon;
			}
		}
		m_iconBGVec[i]->setPosition(Point(startpos.x + (i%m_nIndexOffset) * dis_X, startpos.y - (i/m_nIndexOffset) * dis_Y));
		m_iconBGVec[i]->setVisible(true);
	}
}

void CGridArrayUI::ActiveOneLineUI(int pos)
{
	pos=pos%m_nCapacity;
	for (int i=pos; i<pos+4; i++)
	{
		m_iconBGVec[i]->removeChildByTag(Tag_UnActive_ui);
		m_iconBGVec[i]->setTouchEnabled(false);
		//m_iconBGVec[i]->addTouchEventListener(this,NULL);
	}
}

void CGridArrayUI::insertGridUI(int nPos,CItem* pItem, emGridsType gridsType)
{
	int index = nPos%m_nCapacity;
	CGridIcon* pGridIcon = CGridIcon::create(pItem,m_nIndexOffset+index,m_gridType,m_bCanMove);
	if (pGridIcon)
	{
		pGridIcon->setPosition(Point(66,66));
		m_iconBGVec[index]->addChild(pGridIcon);
		m_iconVec[index]=pGridIcon;
	}

	if(m_bDynamicShow)
	{
		m_iconBGVec[index]->setVisible(true);
	}
}

void CGridArrayUI::removeGridUI(int nPos)
{
	int index = nPos%m_nCapacity;

	if (m_iconVec[index])
	{
		m_iconVec[index]->removeFromParentAndCleanup(true);
		m_iconVec[index]=NULL;
	}

	if(m_bDynamicShow)
	{
		m_iconBGVec[index]->setVisible(false);
	}
}

void CGridArrayUI::removeAllGridUIs()
{
	for (int i=0; i<m_nCapacity; ++i)
	{
		if(m_iconVec[i])
		{
			m_iconVec[i]->removeFromParentAndCleanup(true);
			m_iconVec[i] = NULL;
		}

		if(m_bDynamicShow)
		{
			m_iconBGVec[i]->setVisible(false);
		}
	}
}

void CGridArrayUI::UpdateIconMask()
{
	for (size_t i=0; i<m_iconVec.size(); ++i)
	{
		if (m_iconVec[i])
		{
			m_iconVec[i]->ShowMask();
		}
	}
}

void CGridArrayUI::ShowMaskManual(bool bShow,ItemCfg* pMaskItemCfg)
{
	for (size_t i=0; i<m_iconVec.size(); ++i)
	{
		if (m_iconVec[i])
		{
			if (pMaskItemCfg)
			{
				CItem* pItem = m_iconVec[i]->GetItem();
				if (pItem)
				{
					ItemCfg* pCfg = pItem->getItemData();
					if (pCfg->subtype == pMaskItemCfg->subtype && pCfg->grade == pMaskItemCfg->grade && pCfg->quality == pMaskItemCfg->quality)
					{
						continue;
					}
				}
			}
			m_iconVec[i]->ShowMaskManual(bShow);
		}
	}
}

void CGridArrayUI::ShowCd(int cdType, float cdTime)
{
	for (auto& pIcon : m_iconVec)
	{
		if ( !pIcon )
		{
			continue;
		}

		CItem* pItem = pIcon->GetItem();
		if (pIcon&&pItem)
		{
			if (pItem->IsCding())
			{
				pIcon->ShowCd();
			}
		}
	}
}

void CGridArrayUI::ShowCd()
{
	for (auto& pIcon : m_iconVec)
	{		
		if (pIcon)
		{
			CItem* pItem = pIcon->GetItem();
			if (pItem->IsCding())
			{
				pIcon->ShowCd();
			}
		}
	}
}

void CGridArrayUI::RemoveCd()
{
	for (auto& pIcon : m_iconVec)
	{		
		if (pIcon)
		{
			CItem* pItem = pIcon->GetItem();
			if (pItem->IsCding())
			{
				pIcon->RemoveCd();
			}
		}
	}
}

void CGridArrayUI::clickGridActive(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		char str[128] = {};

		int nActive = gGridsManager->countAtive(m_gridType);
		BagGridCfg* pActiveCfg = BagGridData.get(m_gridType);
		int costMoney = pActiveCfg->a1 + pActiveCfg->a2*(((nActive - GetDefaultActiveGrids(m_gridType))/4)+1);

		sprintf(str,"%s %d %s",STR_MESSAGEBOX_COST.c_str(),costMoney,STR_MESSAGEBOX_ACTTIVEGRID.c_str());
		CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,str,STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),this,YESORNO_EVENT(&CGridArrayUI::activeCallFunc));
	}
}

void CGridArrayUI::activeCallFunc(bool yesOrNo)
{
	if (yesOrNo)
	{
		pk::C2GS_SetBagGrid cmd;
		cmd.bagType = m_gridType;
		cmd.Send(gNetSocket);
	} 
}

void CGridArrayUI::AddIconClickEvent(Ref* pSender,IconClickEvent event)
{
	for (auto& pIcon : m_iconVec)
	{
		if (pIcon)
		{
			pIcon->AddIconClickEvent(pSender,event);
		}
	}
}
