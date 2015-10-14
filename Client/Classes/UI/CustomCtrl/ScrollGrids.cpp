#include "ScrollGrids.h"
#include "GameScene/GridsManager.h"
#include "Net/NetDispatcher.h"
#include "UI/MessageBoxUI.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/Hero.h"
#include "UI/RoleAttriUI.h"

#define LONGTIME             1.f          //长按时间（秒）
#define DELAYTIME            300.f        //双击时间（毫秒）
#define PACKUPCNT            6            //最多可穿戴装备数

ScrollGrids_cl::ScrollGrids_cl():
	m_disX(0)
	,m_disY(0)
	,m_lineGrids(0)
	,m_totalGrids(0)
	,m_delayTime(0.f)
	,m_longTime(0.f)
	,m_recordcnt(0)
	,m_startPos(Point::ZERO)
	,m_gridType(emGrids_None)
	,m_blimit(false)
	,m_isLongTouch(false)
	,m_childnode(nullptr)
	,m_parent(nullptr)
	,m_pEquip(nullptr)
	,m_isOverEquip(false)
	,m_longTouched(false)
	,m_isdoubled(true)
	,m_OneSelected(false)
	,m_childrenCnt(0)
	,m_totalPrice(0)
	,m_curShowItemArr(nullptr)
{
	m_vSelectItem.clear();
	m_itemIconVec.clear();
	m_vEquipNode.clear();
	for (int i = 0; i < ITEMEVENT_MAX; i++)
	{
		m_func[i] = nullptr;
	}
}

ScrollGrids_cl::~ScrollGrids_cl()
{
	m_vSelectItem.clear();
	m_itemIconVec.clear();
	m_vEquipNode.clear();
	if(m_childnode)
	{
		m_childnode->release();
		m_childnode = nullptr;
	}
}


bool ScrollGrids_cl::init( emGridsType _gridType, int _totalGrid, int _lineGrid, ScrollView*  &_scroll,Node * _parent, bool _limit)
{
	if(!ScrollView::init() && !_scroll) return false;

	m_gridType    = _gridType;
	m_totalGrids  = _totalGrid;
	m_lineGrids   = _lineGrid;
	if(!_parent) m_parent = _scroll->getParent();
	else
	{
		m_parent = _parent;
	}
	m_blimit = _limit;
	Layout * inner = _scroll->getInnerContainer();
	int cnt = _scroll->getInnerContainer()->getChildrenCount();
	setSize(_scroll->getSize());
	this->setDirection(_scroll->getDirection());
	this->setClippingEnabled(true);
	//获取第一个节点的位置 startpos
	//计算横向间隔dis_X
	//获取竖向间隔dis_Y
	//分横纵向
	if(cnt <= 0) return false;
	Widget * childParent = dynamic_cast<Widget*>(inner->getChildren().at(0));
	m_startPos = childParent->getPosition();
	if(_scroll->getDirection() == SCROLLVIEW_DIR_VERTICAL)
	{
		m_disX   = inner->getChildren().at(1)->getPositionX() - m_startPos.x;
		m_disY   = m_startPos.y - inner->getChildren().at(2)->getPositionY();
	}
	else if(_scroll->getDirection() == SCROLLVIEW_DIR_HORIZONTAL)
	{
		m_disX   = inner->getChildren().at(1)->getPositionX() - m_startPos.x;
		m_disY   = m_startPos.y - inner->getChildren().at(2)->getPositionY();
	}
	m_childnode = childParent->clone();
	m_childnode->retain();
	_scroll->removeAllChildren();
	this->setEnabled(_scroll->isEnabled());
	this->setPosition(_scroll->getPosition());
	_scroll->getParent()->addChild(this);
	_scroll->removeFromParent();
	_scroll = this;
	
	//reset();  移植创建函数里面
	return true;
}

ScrollGrids_cl* ScrollGrids_cl::create( emGridsType _gridType, int _totalGrid, int _lineGrid, ScrollView* &_scroll,Node * _parent/* = nullptr */, bool _limit /*= true*/ )
{
	ScrollGrids_cl * ret = new ScrollGrids_cl();
	if(ret && ret->init(_gridType, _totalGrid, _lineGrid, _scroll, _parent, _limit))
	{
		ret->reset();
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;
}

ScrollGrids_cl* ScrollGrids_cl::createWithOutData(emGridsType _gridType, int _totalGrid, int _lineGrid, ScrollView* &_scroll, Node * _parent /* = nullptr */, bool _limit /*= true*/)
{
	ScrollGrids_cl * ret = new ScrollGrids_cl();
	if(ret && ret->init(_gridType, _totalGrid, _lineGrid, _scroll, _parent, _limit))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;
}


void ScrollGrids_cl::initCreateData()
{
	Size size = this->getSize();
	if(!m_blimit) //不限制格子数
	{
		if(m_curShowItemArr)
		{
			m_totalGrids = m_curShowItemArr->getItemGridsList().size();
		}
	}

	int page = ceil((float)m_totalGrids/m_lineGrids);
	if(page <= 1)
		page = 1;
	if(this->getDirection() == SCROLLVIEW_DIR_VERTICAL)
	{
		int height = m_disY * page > size.height?m_disY * page:size.height;
		size.setSize(size.width,   height);
		m_startPos.y = size.height - m_disY/2;
	}
	else if(this->getDirection() == SCROLLVIEW_DIR_HORIZONTAL)
	{
		int width = m_disX * page >size.width?m_disX*page:size.width;
		size.setSize(width,   size.height);
	}
	this->getInnerContainer()->setSize(size);
}

void ScrollGrids_cl::reset()
{
	CItemGridArray* pGridsData = gGridsManager->getGridsData(m_gridType);
	m_curShowItemArr = pGridsData;
	if(m_itemIconVec.size() == 0)
		resetByData(pGridsData);
	else
	{
		resetData(pGridsData);
	}
}


void ScrollGrids_cl::resetByData(CItemGridArray* pGridsData)
{
	if(!pGridsData) return;
	m_curShowItemArr = pGridsData;
	for (auto iter: m_itemIconVec)
	{
		iter.bgIcon->removeFromParent();
	}
	m_itemIconVec.clear();
	initCreateData();
	m_itemIconVec.resize(m_totalGrids);
	m_selectIndex = 0;
	m_childrenCnt = 0;
	m_totalPrice = 0;
	m_vSelectItem.clear();
	for (int i = 0; i < m_totalGrids; i++)
	{
		m_itemIconVec[i].bgIcon= m_childnode->clone();
		m_itemIconVec[i].bgIcon->removeAllChildren();
		if(this->getDirection() == SCROLLVIEW_DIR_VERTICAL)
		{
			m_itemIconVec[i].bgIcon->setPosition(Point(m_startPos.x + (i%m_lineGrids) * m_disX, m_startPos.y - (i/m_lineGrids) * m_disY));
		}
		else if(this->getDirection() == SCROLLVIEW_DIR_HORIZONTAL)
		{
			m_itemIconVec[i].bgIcon->setPosition(Point(m_startPos.x + (i/m_lineGrids) * m_disX, m_startPos.y - (i%m_lineGrids) * m_disY));
		}
		this->getInnerContainer()->addChild(m_itemIconVec[i].bgIcon);

		CItemGrid* pItemGrid = pGridsData->GetItemGrid(i);
		if(!pItemGrid || !pItemGrid->GetItem()) continue;
		CGridIcon* pGridIcon = CGridIcon::create(pItemGrid->GetItem(),pItemGrid->GetItem()->getIndex(),m_gridType);
		if (pGridIcon)
		{
			m_itemIconVec[i].bgIcon->addChild(pGridIcon);
			pGridIcon->setPosition(Point(m_itemIconVec[i].bgIcon->getSize().width/2,m_itemIconVec[i].bgIcon->getSize().height/2));	
			m_itemIconVec[i].gridIcon=pGridIcon;
			m_itemIconVec[i].gridIcon->setTouchEnabled(true);
			m_itemIconVec[i].gridIcon->setTag(i);
			m_itemIconVec[i].gridIcon->addTouchEventListener(this,toucheventselector(ScrollGrids_cl::clickGrid));
			m_childrenCnt += 1;
		}
	}
}


void ScrollGrids_cl::resetData(CItemGridArray* pGridsData)
{
	if(!pGridsData) return;
	m_curShowItemArr = pGridsData;
	m_selectIndex = 0;
	m_childrenCnt = 0;
	m_totalPrice = 0;
	initCreateData();
	m_vSelectItem.clear();
	if(!m_blimit)
	{
		int startcnd = (int)m_itemIconVec.size();
		if(m_totalGrids > (int)m_itemIconVec.size())
		{
			m_itemIconVec.resize(m_totalGrids);
			for (int i = startcnd; i < m_totalGrids; i++)
			{
				m_itemIconVec[i].bgIcon= m_childnode->clone();
				m_itemIconVec[i].bgIcon->removeAllChildren();
				if(this->getDirection() == SCROLLVIEW_DIR_VERTICAL)
				{
					m_itemIconVec[i].bgIcon->setPosition(Point(m_startPos.x + (i%m_lineGrids) * m_disX, m_startPos.y - (i/m_lineGrids) * m_disY));
				}
				else if(this->getDirection() == SCROLLVIEW_DIR_HORIZONTAL)
				{
					m_itemIconVec[i].bgIcon->setPosition(Point(m_startPos.x + (i/m_lineGrids) * m_disX, m_startPos.y - (i%m_lineGrids) * m_disY));
				}
				this->getInnerContainer()->addChild(m_itemIconVec[i].bgIcon);
			}
		}
		else if(m_totalGrids < (int)m_itemIconVec.size())
		{
			for(int i = (int)m_itemIconVec.size() - 1; i > m_totalGrids - 1; i--)
			{
				m_itemIconVec[i].bgIcon->removeFromParent();
			}
			m_itemIconVec.resize(m_totalGrids);
		}
	}
	for (int i = 0; i < m_totalGrids; i++)
	{
		if(!m_itemIconVec[i].bgIcon) return;
		m_itemIconVec[i].bgIcon->removeAllChildren();
		CItemGrid* pItemGrid = pGridsData->GetItemGrid(i);
		if(!pItemGrid || !pItemGrid->GetItem()) continue;
		CGridIcon* pGridIcon = CGridIcon::create(pItemGrid->GetItem(),pItemGrid->GetItem()->getIndex(),m_gridType);
		if (pGridIcon)
		{
			m_itemIconVec[i].bgIcon->addChild(pGridIcon);
			pGridIcon->setPosition(Point(m_itemIconVec[i].bgIcon->getSize().width/2,m_itemIconVec[i].bgIcon->getSize().height/2));	
			m_itemIconVec[i].gridIcon=pGridIcon;
			m_itemIconVec[i].gridIcon->setTouchEnabled(true);
			m_itemIconVec[i].gridIcon->setTag(i);
			m_itemIconVec[i].gridIcon->addTouchEventListener(this,toucheventselector(ScrollGrids_cl::clickGrid));
			m_childrenCnt += 1;
		}
	}
}


void ScrollGrids_cl::clickGrid( Ref * _ref, TouchEventType _type )
{
	if(_type == TOUCH_EVENT_BEGAN)
	{
		m_selectIndex = dynamic_cast<ImageView*>(_ref)->getTag();
		if(m_longTime == 0.f && m_longTouched)
		this->schedule(schedule_selector(ScrollGrids_cl::updateTime));
	}
	else if(_type == TOUCH_EVENT_MOVED)
	{
 		if(m_longTime < LONGTIME)
 		{
 			this->unschedule(schedule_selector(ScrollGrids_cl::updateTime));
 			m_longTime = 0.f;
 			m_isLongTouch = false;
 		}
		if(m_isLongTouch == true && m_pEquip)   //长按事件
		{
			Point point1 = dynamic_cast<ImageView*>(_ref)->getTouchMovePos(); 
			m_pEquip->setPosition(point1);
			checkIntersectsRect();
		}
	}
	else if(_type == TOUCH_EVENT_ENDED)
	{
		if(m_longTime >= 0.016f && m_longTouched)
		{
			this->unschedule(schedule_selector(ScrollGrids_cl::updateTime));
			m_longTime = 0.f;
			m_isLongTouch = false;
		}
		if(m_pEquip)
		{
			m_pEquip->removeFromParent();
			m_pEquip = nullptr;
			m_itemIconVec[m_selectIndex].gridIcon->setVisible(true);
		}

		//先处理单击事件
		//TODO:something
		if(m_func[ONE_TOUCH_EVENT]) //自定义单击事件
		{
			CItem * itemgrid = gGridsManager->getGridsData(m_gridType)->GetItemGrid(m_selectIndex)->GetItem();
			m_func[ONE_TOUCH_EVENT](itemgrid);
		}else  
		{

		}
		if(m_isdoubled)  //开启双击事件
		{
			//如果满足双击事件, 则关闭单击事件
			doubleEvent();
		}
	}
	else if(_type == TOUCH_EVENT_CANCELED)
	{
		m_delayTime = 0.f;
		m_isLongTouch = false;
		m_longTime = 0.f;
		if(m_isOverEquip)  //换装备事件
		{
			CCLOG("chang equip");
			gHero->Equip(m_selectIndex);
		}

		m_itemIconVec[m_selectIndex].gridIcon->setVisible(true);

		if(m_pEquip)
		{
			m_parent->removeChild(m_pEquip);
			m_pEquip = nullptr;
		}
	}
}


void ScrollGrids_cl::updateTime(float fd)
{
	m_longTime += fd;
	if(m_longTime >= LONGTIME)  //长按事件
	{
		CCLOG("long touch event");
		this->unschedule(schedule_selector(ScrollGrids_cl::updateTime));
		m_isLongTouch = true;
		this->setAcceptTouchEnable(false);
		if(m_pEquip == nullptr)
		{
			m_pEquip = ImageView::create();
			m_pEquip->loadTexture(m_itemIconVec[m_selectIndex].gridIcon->getIconPath());
			m_parent->addChild(m_pEquip);
			Point point1 = m_itemIconVec[m_selectIndex].gridIcon->getTouchStartPos(); 
			m_pEquip->setPosition(point1);
			m_itemIconVec[m_selectIndex].gridIcon->setVisible(false);
		}
	}
}


void ScrollGrids_cl::doubleEvent()
{
	float millTime = getMilliSecond();
	if(m_delayTime == 0.f)
	{
		m_delayTime = millTime; 
	}
	else if(millTime - m_delayTime <= DELAYTIME) //双击事件
	{
		CCLOG("double touch event");
		m_delayTime = 0.f;
		CItem * itemgrid = gGridsManager->getGridsData(m_gridType)->GetItemGrid(m_selectIndex)->GetItem();
		if(itemgrid)
		{
			if(m_func[DOUBLE_TOUCH_EVENT]) //外部自己注册双击事件
			{
				m_func[DOUBLE_TOUCH_EVENT](itemgrid);
				return ;
			}
			if(m_OneSelected)
			{
				if(m_vSelectItem.size()>0 && m_vSelectItem[0].index == m_selectIndex)
				{
					if(itemgrid->getItemPrice() != -1)
					{
						m_totalPrice -= itemgrid->getItemPrice();
					}
					m_itemIconVec[m_vSelectItem[0].index].gridIcon->ShowMaskManual(false);
					m_vSelectItem.clear();
				}
				else
				{
					m_vSelectItem.clear();
					pk::C2GS_NpcShopSell cmd;
					cmd.itemCnt = itemgrid->getCount();
					cmd.bagType = itemgrid->getType();
					cmd.itemId = itemgrid->getId();
					cmd.itemDataId = itemgrid->getDataID();
					SelectItem_st selectItem;
					selectItem.sell = cmd;
					selectItem.index = m_selectIndex;
					m_vSelectItem.push_back(selectItem);
					m_itemIconVec[m_selectIndex].gridIcon->ShowMaskManual(true);
					if(itemgrid->getItemPrice() != -1)
					{
						m_totalPrice += itemgrid->getItemPrice();
					}
				}
			}
			else
			{
				//检测是否含有此装备
				bool isexit = false;
				for(auto iter = m_vSelectItem.begin(); iter != m_vSelectItem.end(); iter++)
				{
					if((*iter).sell.itemDataId == itemgrid->getDataID())
					{
						isexit = true;
						m_vSelectItem.erase(iter);
						m_itemIconVec[m_selectIndex].gridIcon->ShowMaskManual(false);
						if(itemgrid->getItemPrice() != -1)
						{
							m_totalPrice -= itemgrid->getItemPrice();
						}
						break;
					}
				}
				if(!isexit)
				{
					if(itemgrid->getItemPrice() != -1)
					{
						m_totalPrice += itemgrid->getItemPrice();
					}
					pk::C2GS_NpcShopSell cmd;
					cmd.itemCnt = itemgrid->getCount();
					cmd.bagType = itemgrid->getType();
					cmd.itemId = itemgrid->getId();
					cmd.itemDataId = itemgrid->getDataID();
					SelectItem_st selectItem;
					selectItem.sell = cmd;
					selectItem.index = m_selectIndex;
					m_vSelectItem.push_back(selectItem);
				}
			}
		}
	}
	else
	{
		m_delayTime = 0.f;
	}
}


void ScrollGrids_cl::registerFunc( funct_s _func, ItemTouchEvent _event )
{
	m_func[_event] = _func;
}


void ScrollGrids_cl::addAreaEquip( EquipNode_V & _vec )
{
	m_vEquipNode.clear();
	for (size_t i = 0; i < _vec.size(); i++)
	{
		EquipNode_st temp = _vec[i];
		Point equippos = _vec[i].equipnode->getPosition();
		Size  esize = _vec[i].equipnode->getContentSize();
		equippos = _vec[i].equipnode->getParent()->convertToWorldSpace(equippos);
		equippos = m_parent->convertToNodeSpace(equippos);
		temp.rect = Rect(equippos.x - esize.width/2, equippos.y - esize.height/ 2, esize.width, esize.height);
		m_vEquipNode.push_back(temp);
	}
}

void ScrollGrids_cl::addAreaEquip( Widget* _widget)
{
	if(!_widget) return;
	for (auto iter: m_vEquipNode)
	{
		if(iter.equipnode == _widget)
			return ;
	}
	EquipNode_st temp;
	temp.equipnode = _widget;
	Point equippos = _widget->getPosition();
	equippos = _widget->getParent()->convertToWorldSpace(equippos);
	equippos = m_parent->convertToNodeSpace(equippos);
	Size  esize = _widget->getContentSize();
	temp.rect = Rect(equippos.x - esize.width/2, equippos.y - esize.height/ 2, esize.width, esize.height);
	m_vEquipNode.push_back(temp);

}

void ScrollGrids_cl::checkIntersectsRect()
{
	if(!m_parent) return;
	if(!m_pEquip) return;
	for (auto iter = m_vEquipNode.begin(); iter != m_vEquipNode.end(); iter++)
	{
		Point equippos = m_pEquip->getPosition();
		Size  esize = m_pEquip->getContentSize();
		Rect rect = Rect(equippos.x - esize.width/2, equippos.y - esize.height/ 2, esize.width, esize.height);
		if(rect.intersectsRect((*iter).rect)) 
		{
			CCLOG("xiangjiao");
			m_isOverEquip = true;
			m_changWidget = &(*iter);
			return;
		}
		else
		{
			m_changWidget = nullptr;
			m_isOverEquip = false;
		}
	}
}

void ScrollGrids_cl::saleSelectItem()
{
	bool isSell = false;
	if(m_vSelectItem.size() == 0)
	{
		CMessageBoxUI::Show(CMessageBoxUI::MBM_OK,STR_ROLEBAG_NOSELL, nullptr,STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
			this,NULL,CMessageBoxUI::Scene_Game);
		isSell = true;
		return;
	}
	for (auto iter: m_vSelectItem)
	{
		CItem * item = gGridsManager->getGridsData(m_gridType)->GetItemGrid(iter.sell.itemDataId)->GetItem();
		if(item && !item->isDoSell())
		{
			CMessageBoxUI::Show(CMessageBoxUI::MBM_OK,STR_ROLEBAG_HAVENOTSELL, nullptr,STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
				this,NULL,CMessageBoxUI::Scene_Game);
			isSell = true;
			break;
		}
	}
	if(!isSell)
	{
		CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,FORMAT_TO_STRING(STR_ROLEBAG_ADMINSELL, m_totalPrice), [=](bool val){
			if(val)
			{
				for (auto iter: m_vSelectItem)
				{
					iter.sell.Send(gNetSocket);
				}
			}
		},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
			this,NULL,CMessageBoxUI::Scene_Game);
	}
}

void ScrollGrids_cl::delwithItem( int _itemId )
{
	//暂时留着
}

void ScrollGrids_cl::packupSelectEquip(int _cnt)
{
	if(m_vSelectItem.size() == 0)
	{
		CMessageBoxUI::Show(CMessageBoxUI::MBM_OK,STR_ROLEBAG_NOPICK, nullptr,STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
			this,NULL,CMessageBoxUI::Scene_Game);	
	}
	else
	{
		gHero->Equip(m_selectIndex);
	}
}

void ScrollGrids_cl::removeItemByIndex( int index )
{
	if(m_itemIconVec.size() > index)
	{
		m_itemIconVec[index].gridIcon->removeFromParent();
		m_itemIconVec[index].gridIcon = nullptr;
	}
}

void ScrollGrids_cl::addItemByIndex( int index)
{
	if(m_itemIconVec.size() > index)
	{
		CItemGridArray* pGridsData = gGridsManager->getGridsData(m_gridType);
		if(pGridsData)
		{
			CItemGrid* pItemGrid = pGridsData->GetItemGrid(index);
			CGridIcon* pGridIcon = CGridIcon::create(pItemGrid->GetItem(),index,m_gridType);
			if (pGridIcon)
			{
				m_itemIconVec[index].bgIcon->addChild(pGridIcon);
				pGridIcon->setPosition(Point(m_itemIconVec[index].bgIcon->getSize().width/2,m_itemIconVec[index].bgIcon->getSize().height/2));	
				m_itemIconVec[index].gridIcon=pGridIcon;
				m_itemIconVec[index].gridIcon->setTouchEnabled(true);
				m_itemIconVec[index].gridIcon->setTag(index);
				m_itemIconVec[index].gridIcon->addTouchEventListener(this,toucheventselector(ScrollGrids_cl::clickGrid));	
			}
		}
	}
	else
	{
		CItemGridArray* pGridsData = gGridsManager->getGridsData(m_gridType);
		if(pGridsData)
		{
			CItemGrid* pItemGrid = pGridsData->GetItemGrid(index);
			CGridIcon* pGridIcon = CGridIcon::create(pItemGrid->GetItem(),index,m_gridType);
			if (pGridIcon)
			{
				m_itemIconVec.resize((int)index + 1);
				m_itemIconVec[index].bgIcon = m_childnode->clone();
				m_itemIconVec[index].bgIcon->removeAllChildren();
				if(this->getDirection() == SCROLLVIEW_DIR_VERTICAL)
				{
					m_itemIconVec[index].bgIcon->setPosition(Point(m_startPos.x + (index%m_lineGrids) * m_disX, m_startPos.y - (index/m_lineGrids) * m_disY));
				}
				else if(this->getDirection() == SCROLLVIEW_DIR_HORIZONTAL)
				{
					m_itemIconVec[index].bgIcon->setPosition(Point(m_startPos.x + (index/m_lineGrids) * m_disX, m_startPos.y - (index%m_lineGrids) * m_disY));
				}
				this->getInnerContainer()->addChild(m_itemIconVec[index].bgIcon);
				m_itemIconVec[index].bgIcon->addChild(pGridIcon);
				pGridIcon->setPosition(Point(m_itemIconVec[index].bgIcon->getSize().width/2,m_itemIconVec[index].bgIcon->getSize().height/2));	
				m_itemIconVec[index].gridIcon=pGridIcon;
				m_itemIconVec[index].gridIcon->setTouchEnabled(true);
				m_itemIconVec[index].gridIcon->setTag(index);
				m_itemIconVec[index].gridIcon->addTouchEventListener(this,toucheventselector(ScrollGrids_cl::clickGrid));	
			}
		}
	}
}

void ScrollGrids_cl::cleanBag()
{
	if(m_childrenCnt == 0)
		return;
	pk::C2GS_BagSort cmd;
	cmd.bagType = m_gridType;
	cmd.Send(gNetSocket);
}

void ScrollGrids_cl::freshRoleEquip(pk::GS2C_EquipExchangeRet* value)
{
	if(!value) return ;
	if(value->isEquip == 0) //卸下
	{
		m_vEquipNode[value->part - 1].equipnode->removeAllChildren();
	}
	else //穿上
	{
		CItemGrid * itemgrid = gGridsManager->getGridsData(m_gridType)->GetItemGrid(m_selectIndex);
		CGridIcon* pGridIcon = CGridIcon::create(itemgrid->GetItem(),itemgrid->GetItem()->getIndex(),emGrids_Role);
		if ( itemgrid->GetItem() )
		{
			CGridIcon* pGridIcon = CGridIcon::create(itemgrid->GetItem(),itemgrid->GetItem()->getIndex(),emGrids_Role);
			if (pGridIcon)
			{
				m_vEquipNode[value->part - 1].equipnode->removeAllChildren();
				m_vEquipNode[value->part - 1].equipnode->addChild(pGridIcon);
				pGridIcon->setPosition(Point(m_vEquipNode[value->part - 1].equipnode->getSize().width/2,m_vEquipNode[value->part - 1].equipnode->getSize().height/2));		
				pGridIcon->setTag(1);
				dynamic_cast<RoleAttriUI_cl*>(m_parent)->addEquipTouchEvent(pGridIcon);
			}
		}
	}
}