#include "DragCtrol.h"
#include "GameScene/GameUILayer.h"

#define DragTimePoint				(0.5f)
#define DragShadowTag				(10)

DragSlot gDragSlots[DragSlotType_Count];

CDragCtrol::CDragCtrol()
	:m_pDragIcon(NULL)
	,m_pCloneSrc(NULL)
	,m_fPressTimeStamp(0.0f)
	,m_nDragId(0)
	,m_slotType(DragSlotType_None)
	,_ClickEventListener(NULL)
	,_ClickEventSelector(NULL)
	,_DragEndListener(NULL)
	,_DragEndSelector(NULL)
	,m_pScrollOrPage(NULL)

{

}

CDragCtrol::~CDragCtrol()
{
	RemoveDragIcon();
}

CDragCtrol* CDragCtrol::create()
{
	CDragCtrol * ret = new CDragCtrol();
	if (ret)
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

CDragCtrol* CDragCtrol::create(Widget* pUICloneSrc,int64 data, DragSlotType slotDes,Ref* pClickEventListener, SEL_TouchEvent clickEventSelector,Widget* pScrollOrPage)
{
	CDragCtrol * ret = new CDragCtrol();
	if (ret && ret->init(pUICloneSrc,data,slotDes,pClickEventListener,clickEventSelector,pScrollOrPage))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool CDragCtrol::init(Widget* pUICloneSrc,int64 data, DragSlotType slotDes,Ref* pClickEventListener, SEL_TouchEvent clickEventSelector,Widget* pScrollOrPage)
{
	m_pCloneSrc = pUICloneSrc;
	m_nDragId = data;
	m_slotType = slotDes;
	m_pScrollOrPage = pScrollOrPage;
	_ClickEventListener = pClickEventListener;
	_ClickEventSelector = clickEventSelector;
	m_pCloneSrc->addTouchEventListener(this,toucheventselector(CDragCtrol::clickSrcUI));
	return Node::init();
}

void CDragCtrol::AddDragEndEvent(Ref* pClickEventListener, SEL_DragEndEvent clickEventSelector)
{
	_DragEndListener = pClickEventListener;
	_DragEndSelector = clickEventSelector;
}

void CDragCtrol::RemoveDragIcon()
{
	if (m_pDragIcon)
	{
		m_pDragIcon->removeFromParentAndCleanup(true);
		m_pDragIcon=NULL;
	}
	SlotScale(m_slotType,1.0f,255);
	for (size_t i=0; i<gDragSlots[m_slotType].slots.size(); ++i)
	{
		gDragSlots[m_slotType].slots[i]->removeChildByTag(DragShadowTag);
		//Widget* pIcon = gDragSlots[m_slotType].slots[i]->getChildByName("");
		//if(pIcon) pIcon->setVisible(true);
	}
}

void CDragCtrol::DragingIcon(Point pos)
{
	m_pDragIcon->setPosition(pos);
	for (size_t i=0; i<gDragSlots[m_slotType].slots.size(); ++i)
	{
		Point SlotPos = getPositionInUILayer(gDragSlots[m_slotType].slots[i]);
		Rect SlotRect = Rect(SlotPos.x-65,SlotPos.y-65,130,130);
		if (SlotRect.containsPoint(pos))
		{
			if (!gDragSlots[m_slotType].slots[i]->getChildByTag(DragShadowTag))
			{
				Widget* pShadow = m_pDragIcon->clone();
				pShadow->setTag(DragShadowTag);
				pShadow->setPosition(Point(gDragSlots[m_slotType].slots[i]->getSize().width/2,gDragSlots[m_slotType].slots[i]->getSize().height/2));
				gDragSlots[m_slotType].slots[i]->addChild(pShadow);
				//Widget* pIcon = gDragSlots[m_slotType].slots[i]->getChildByName(SlotIcon_Name);
				//if(pIcon) pIcon->setVisible(false);
			}
		}
		else
		{
			gDragSlots[m_slotType].slots[i]->removeChildByTag(DragShadowTag);
			//Widget* pIcon = gDragSlots[m_slotType].slots[i]->getChildByName(SlotIcon_Name);
			//if(pIcon) pIcon->setVisible(true);
		}
	}
}

void CDragCtrol::DragTimer(float dt)
{
	m_fPressTimeStamp+=dt;
	if (m_fPressTimeStamp>=DragTimePoint)
	{
		OnDragUp();
		this->unschedule(schedule_selector(CDragCtrol::DragTimer));
	}
}

void CDragCtrol::StartTimer()
{
	this->schedule(schedule_selector(CDragCtrol::DragTimer));
}

void CDragCtrol::StopTimer()
{
	this->unschedule(schedule_selector(CDragCtrol::DragTimer));
	m_fPressTimeStamp=0.0f;
	RemoveDragIcon();
}

void CDragCtrol::OnDragUp()
{
	if (m_pCloneSrc)
	{
		m_pDragIcon = m_pCloneSrc->clone();
		m_pDragIcon->runAction(Sequence::create(ScaleTo::create(0.2f,1.5f),ScaleTo::create(0.2f,1.0f),NULL));
		m_pDragIcon->setOpacity(255*0.7);
		m_pDragIcon->setPosition(getPositionInUILayer(m_pCloneSrc));
		m_pDragIcon->setLocalZOrder(Menu_Tag);
		gGameUILayer->addChild(m_pDragIcon);
	}

	if(m_slotType == DragSlotType_None) return;
	SlotScale(m_slotType,1.3f,77);
}

void CDragCtrol::OnDragEnd()
{
	if (!_DragEndListener || !_DragEndSelector)
	{
		_DragEndListener = gDragSlots[m_slotType].pListener;
		_DragEndSelector = gDragSlots[m_slotType].pSelector;
	}
	if (_DragEndListener&&_DragEndSelector&&m_pDragIcon)
	{
        (_DragEndListener->*_DragEndSelector)(m_pDragIcon,m_nDragId);
	}
	StopTimer();
}

void CDragCtrol::EnableScroll(bool bEnable)
{
	ScrollView* pScroll = (ScrollView*)(m_pScrollOrPage);
	PageView* pPage = (PageView*)(m_pScrollOrPage);
	if(pScroll)
		pScroll->setAcceptTouchEnable(bEnable);
	if(pPage)
		pPage->setAcceptTouchEnable(bEnable);
}

void CDragCtrol::clickSrcUI(Ref* pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		{
			StartTimer();
		}
		break;
	case TOUCH_EVENT_MOVED:
		{
			if (m_pDragIcon)
			{
				EnableScroll(false);
				DragingIcon(getPositionInUILayer(m_pCloneSrc->getTouchMovePos()));
			}
			else
			{
				StopTimer();
			}
		}
		break;
	case TOUCH_EVENT_ENDED:
		{
			StopTimer();
			EnableScroll(true);
			//不拖动，相应原始点击事件
			if (_ClickEventListener&&_ClickEventSelector)
			{
				(_ClickEventListener->*_ClickEventSelector)(m_pCloneSrc,TOUCH_EVENT_ENDED);
			}
		}
		break;
	case TOUCH_EVENT_CANCELED:
		{
			OnDragEnd();
			EnableScroll(true);
		}
		break;
	}
}

void CDragCtrol::SlotScale(DragSlotType type, float fScale, int fOpacity)
{
	for (size_t i=0; i<gDragSlots[type].slots.size(); ++i)
	{
		gDragSlots[type].slots[i]->runAction(ScaleTo::create(0.2f,fScale));
		gDragSlots[type].slots[i]->setOpacity(fOpacity);
	}
}