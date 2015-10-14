#include "HallTechUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "GameScene/GameUILayer.h"
#include "Net/NetDispatcher.h"
#include "Common/DataPool.h"
#include "GameScene/MessageCenter.h"
#include "MessageBoxUI.h"
#include "GameScene/MessageCenter.h"
#include "GameScene/Hero.h"
#include "UI/ChatMainUI.h"
#include "UI/MainUINormal.h"

CHallTechUI::CHallTechUI()
	:GameUI(IDU_HallTechUI,JsonFile_HallTechUI)
{

}

CHallTechUI::~CHallTechUI()
{

}

bool CHallTechUI::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());

		Button *pBack_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "back_btn");
		BREAK_IF(pBack_btn==NULL);
		pBack_btn->setButtonSpriteGray();
		pBack_btn->addTouchEventListener(this, SEL_TouchEvent(&CHallTechUI::clickBackButton));

		// 制造入口按钮
		Button *p_btn_1 = (Button*)Helper::seekWidgetByName(m_pWidget, "entrance_btn_1");
		BREAK_IF(p_btn_1==NULL);
		p_btn_1->setTag(1);
		p_btn_1->addTouchEventListener(this, SEL_TouchEvent(&CHallTechUI::clickMapEnteranceButton));

		// 天书入口按钮
		Button *p_btn_2 = (Button*)Helper::seekWidgetByName(m_pWidget, "entrance_btn_2");
		BREAK_IF(p_btn_2==NULL);
		p_btn_2->setTag(2);
		p_btn_2->addTouchEventListener(this, SEL_TouchEvent(&CHallTechUI::clickMapEnteranceButton));

		// 神器入口按钮
		Button *p_btn_3 = (Button*)Helper::seekWidgetByName(m_pWidget, "entrance_btn_3");
		BREAK_IF(p_btn_3==NULL);
		p_btn_3->setTag(3);
		p_btn_3->addTouchEventListener(this, SEL_TouchEvent(&CHallTechUI::clickMapEnteranceButton));

		// 4 入口按钮
		Button *p_btn_4 = (Button*)Helper::seekWidgetByName(m_pWidget, "entrance_btn_4");
		BREAK_IF(p_btn_4==NULL);
		p_btn_4->setTag(4);
		p_btn_4->addTouchEventListener(this, SEL_TouchEvent(&CHallTechUI::clickMapEnteranceButton));

		// 5 入口按钮
		Button *p_btn_5 = (Button*)Helper::seekWidgetByName(m_pWidget, "entrance_btn_5");
		BREAK_IF(p_btn_5==NULL);
		p_btn_5->setTag(5);
		p_btn_5->addTouchEventListener(this, SEL_TouchEvent(&CHallTechUI::clickMapEnteranceButton));

		m_Lv = (Text*)Helper::seekWidgetByName(m_pWidget, "Lv");
		m_Lv->setText(FORMAT_TO_STRING("%d",gHero->GetLevel()));
		m_head_img = (ImageView*)Helper::seekWidgetByName(m_pWidget, "HeadBtn");

		ScrollView* scrollView_ = (ScrollView*)Helper::seekWidgetByName(m_pWidget,"scrollView");
		Layer* img_layer_ = (Layer*)Helper::seekWidgetByName(m_pWidget,"bg_panel");

		//聊天
		m_pChatUI = (Layout*)Helper::seekWidgetByName(m_pWidget,"ChatLayout");
		m_pButtonChat =  (Button*)Helper::seekWidgetByName(m_pWidget,"ChatBtn");
		m_pButtonChat->addTouchEventListener(this,toucheventselector(CHallTechUI::clickChat));

		m_pMsgWind = CScrollMsgWindow::create();
		m_pMsgWind->setSize(m_pChatUI->getSize()); 	/*msgWind size 为300*i时，排版合适*/
		m_pMsgWind->setTouchEnabled(false);
		m_pMsgWind->setOpacity(0);
		ChatMainUI *pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
		if (pChatUI)
		{
			m_pMsgWind->SetTouchNameListenner(gGameUILayer->getUI(IDU_CHATMAINUI), (SEL_TouchNameLinkEvent)&ChatMainUI::clickNameLink4MainUI);
			m_pMsgWind->SetTouchItemListenner(gGameUILayer->getUI(IDU_CHATMAINUI), (SEL_TouchItemLinkEvent)&ChatMainUI::clickItemLink4MainUI);
		}
		m_pChatUI->addChild(m_pMsgWind);

		//右下 菜单
		Layout* PanelClipedB = (Layout*)Helper::seekWidgetByName(m_pWidget,"ButtomCliped");
		m_panelMenuB = (Layout*)Helper::seekWidgetByName(m_pWidget,"ButtomMenus");
		m_BtnSwitchB = (Button*)Helper::seekWidgetByName(m_pWidget,"ButtomSwitch");
		for (int i=1;i<=2;++i)
		{
			Button* pBtn = (Button*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("%d",i)->getCString());
			BREAK_IF((pBtn)==NULL);
			pBtn->setTag(i);
			pBtn->addTouchEventListener(this,toucheventselector(CHallTechUI::clickEnteranceButton));
		}
		BREAK_IF( m_BtnSwitchB&&PanelClipedB);
		m_panelMenuB->setPosition(Point(700,0));
		PanelClipedB->setClippingEnabled(true);
		m_BtnSwitchB->addTouchEventListener(this,toucheventselector(CHallTechUI::ClickSwitchB));
		m_BtnSwitchB->setFlippedX(false);

		return true;
	} while (0);

	return false;
}

void CHallTechUI::ClickSwitchB(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		Point pos = m_BtnSwitchB->isFlippedX()?Point(700,0):Point(350,0);
		auto func = [this]()
		{
			m_BtnSwitchB->setFlippedX(!m_BtnSwitchB->isFlippedX());
		};
		m_panelMenuB->runAction(Sequence::create(EaseElasticInOut::create(MoveTo::create(0.5f,pos),0.5f),CallFunc::create(func),NULL));
	}
}


void CHallTechUI::updateChatMsg(pk::GS2C_Chat *value)
{
	ChatMainUI* pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
	if (pChatUI->IsCurChannelMsg(value))
	{
		m_pMsgWind->PushMsg(value,value->senderId==gHero->GetId());
		m_pMsgWind->Flush(true);
	}
}

void CHallTechUI::clickChat(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		GameUI* pUI = gGameUILayer->open(IDU_CHATMAINUI);
		if(pUI) pUI->setPosition(Point::ZERO);
	}
}

void CHallTechUI::onOpen()
{
	isUnlockHallTech(2,0);
}

void CHallTechUI::onClose()
{

}

void CHallTechUI::clickBackButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

void CHallTechUI::clickEnteranceButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		switch (((Button*)pSender)->getTag())
		{
		case 1:
			// 点击了背包
			gGameUILayer->open(IDU_RoleAttri);
			break;
		case 2:
			// 点击了好友
			gGameUILayer->open(IDU_Friend);
			break;
		default:
			break;
		}
	}
}

void CHallTechUI::clickMapEnteranceButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		switch (((Button*)pSender)->getTag())
		{
		case 1:
			// 点击了制造
			gGameUILayer->open(IDU_ManufactureUI);
			break;
		case 2:
			// 点击了天书
			gGameUILayer->open(IDU_SkyBookUI);
			break;
		case 3:
			// 点击了神器
			gGameUILayer->open(IDU_GodDeviceUI);
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}
	}
}