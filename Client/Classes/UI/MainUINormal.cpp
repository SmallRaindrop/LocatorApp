#include "MainUINormal.h"
#include "Net/pk_map.h"
#include "Net/NetDispatcher.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/Hero.h"
#include "ChatMainUI.h"
#include "GamePrompt.h"
#include "Net/pk_team.h"
#include "TeamUI.h"
#include "TeamApplicationUI.h"
#include "SysTipsMgr.h"
#include "UIWorldMap.h"
#include "OneStroke.h"
#include "OpenLock.h"
#include "DramaUi.h"
#include "GameScene/IndicatorLayer.h"
#include "WaveEnd.h"

HornContorller::HornContorller(Widget *pMainPanel) : m_bTextShowing(), m_pSenderName(), m_pHornText(), m_bTextNeedScrollLen()
{
	m_pMainWind = pMainPanel;
	m_pClipWind = Helper::seekWidgetByName(m_pMainWind, "Panel_Clip");
	((Layout*)m_pClipWind)->setClippingEnabled(true);
	m_pHornIcon = (Text*)Helper::seekWidgetByName(m_pMainWind, "Image_HornIcon");
	m_fTextOrgPosX = 0;
}

void HornContorller::PushMsg(const pk::GS2C_Chat *value)
{
	m_queHornWords.push(*value);
}

void HornContorller::ScrollText(float dt)
{
	if (m_bTextNeedScrollLen > 0)
	{
		m_pHornText->setPositionX(m_pHornText->getPositionX() - dt * 30);
	}
	else
	{
		if (m_queHornWords.size() == 0)
			m_pMainWind->runAction(Sequence::createWithTwoActions(FadeOut::create(2.f), CallFunc::create(CC_CALLBACK_0(HornContorller::MsgOver,this))));
		m_bTextShowing = false;			// 淡出开始时就表示已显示结束，可以被后续消息打断
	}
	m_bTextNeedScrollLen -= dt * 30;
}

void HornContorller::update(float dt)
{
	if (m_bTextShowing)
	{
		m_fCurHornLastTime += dt;
		if (m_fCurHornLastTime > 10.0)
		{
			ScrollText(dt);
		}
	}
	else
	{
		if (m_queHornWords.size())
		{
			m_pMainWind->removeChild(m_pSenderName);

			m_pSenderName = UnderlinedText::create(m_queHornWords.front().senderName.c_str());
			m_pSenderName->addTouchEventListener(m_pScrollWindDelegate, SEL_TouchEvent(&CScrollMsgWindow::ClickName));
			m_pSenderName->setColor(Color3B::RED);
			m_pSenderName->setAnchorPoint(Point(0, 0.5f));
			m_pSenderName->setFontSize(40);
			m_pSenderName->setPosition(Point(100, m_pMainWind->getSize().height / 2));
			Text *pColon = Text::create(" :", "Helvetica", 40);
			pColon->setColor(m_pSenderName->getColor());
			pColon->setPosition(Point(m_pSenderName->getSize().width, m_pSenderName->getSize().height / 2));
			m_pSenderName->addChild(pColon);
			m_pScrollWindDelegate->RecordNameLink(m_pSenderName, m_queHornWords.front().senderId);
			m_pMainWind->addChild(m_pSenderName);
			m_pMainWind->setVisible(true);
			m_pMainWind->setOpacity(255);

			if (m_pHornText) m_pHornText->removeFromParent();
			m_pHornText = RichTextEx::create();
			m_pHornText->ignoreContentAdaptWithSize(true);
			m_pClipWind->addChild(m_pHornText);
			vector<pair<Ref*, int64>> vtrLinks = MakeChatSentence(m_pScrollWindDelegate, m_pHornText, &m_queHornWords.front(),false);
			m_pHornText->removeElement(0);	// 频道需要固定显示，已经在外面设定好，richtext不需要显示
			m_pHornText->removeElement(0);	// 名字需要固定显示，已经在外面设定好，richtext不需要显示
			m_pHornText->removeElement(0);	// 冒号需要固定显示，已经在外面设定好，richtext不需要显示
			m_pHornText->formatText();
			for (size_t i = 1; i < vtrLinks.size(); i++)
			{
				m_pScrollWindDelegate->RecordItemLink(vtrLinks[i].first, vtrLinks[i].second);
			}

			m_pMainWind->stopAllActions();
			Size szText = m_pHornText->getVirtualRendererSize();
			m_bTextNeedScrollLen = szText.width - m_pClipWind->getSize().width;
			m_pHornText->setPosition(Point(m_fTextOrgPosX = szText.width / 2, m_pClipWind->getSize().height/ 2));
			m_pClipWind->setPositionX(m_pSenderName->getPositionX() + m_pSenderName->getContentSize().width + 20);

			m_queHornWords.pop();
			m_fCurHornLastTime = 0;
			m_bTextShowing = true;
		}
	}

	m_pHornIcon->setOpacity(m_pMainWind->getOpacity());
	if (m_pSenderName)	m_pSenderName->setOpacity(m_pMainWind->getOpacity());
	if (m_pHornIcon)	m_pHornIcon->setOpacity(m_pMainWind->getOpacity());
	if (m_pHornText)	m_pHornText->setOpacity(m_pMainWind->getOpacity());
}

void HornContorller::MsgOver()
{
	m_pHornText->removeFromParent();
	m_pSenderName->removeFromParent();
	m_pHornText = NULL;
	m_pSenderName = NULL;
}

HornContorller* HornContorller::Create(Widget *pMainPanel)
{
	HornContorller* pWind = new HornContorller(pMainPanel);
	if ( pWind )
	{
		pWind->autorelease();
		return pWind;
	}
	return NULL;
}

CMainUINormal::CMainUINormal() : MainUI(IDU_MainUINormal,JsonFile_MainUINormal)
{
	m_panelLT = NULL;
	m_panelLB = NULL;
	m_panelRT = NULL;
	m_panelRB = NULL;

	m_HeadIcon = NULL;
	m_HeroLv = NULL;
	m_HeroName = NULL;
	m_bIconInit = false;

	m_JoyStick = NULL;

	m_panelMenuB = NULL;
	m_BtnSwitchB = NULL;

	m_pHornWind = NULL;
	m_pMsgWind = NULL;
	m_pButtonChat = NULL;
	m_fChatBtnShowTime = 0.0f;
	m_bMsgWindScrolled = false;
	m_fMatchUIShowSeconds = 0.0f;
}

CMainUINormal::~CMainUINormal()
{
	CC_SAFE_RELEASE(m_pHornWind);
}

bool CMainUINormal::onInit()
{
	do 
	{
		BREAK_IF(!GameUIWithOutSideTouchEvent::onInit());
		//左上 左下 右上 右下 四个面板
		m_panelLT = (Layout*)Helper::seekWidgetByName(m_pWidget,"LeftTop");
		m_panelLB = (Layout*)Helper::seekWidgetByName(m_pWidget,"RightTop");
		m_panelRT = (Layout*)Helper::seekWidgetByName(m_pWidget,"LeftBottom");
		m_panelRB = (Layout*)Helper::seekWidgetByName(m_pWidget,"RightBottom");
		BREAK_IF( !(m_panelLT&&m_panelLB&&m_panelRT&&m_panelRB) );

		//修正上下左右panel位置
		//float fRatio = gDirector->getVisibleSize().height / gDirector->getVisibleSize().width;
		//float fNewHeight = fRatio * UI_ORIG_SIZE.width;
		//if (fNewHeight > UI_ORIG_SIZE.height)
		//{
		//	float fOffsetY = (fNewHeight -UI_ORIG_SIZE.height) / 2;
		//	m_panelLT->setPositionY(m_panelLT->getPositionY() + fOffsetY);
		//	m_panelRT->setPositionY(m_panelRT->getPositionY() + fOffsetY);
		//	m_panelLB->setPositionY(m_panelLB->getPositionY() - fOffsetY);
		//	m_panelRB->setPositionY(m_panelRB->getPositionY() - fOffsetY);
		//}

		//玩家头像
		m_HeadIcon = (ImageView*)Helper::seekWidgetByName(m_pWidget,"HeadBtn");
		m_HeroLv = (Text*)Helper::seekWidgetByName(m_pWidget,"Lv");
		m_HeroName = (Text*)Helper::seekWidgetByName(m_pWidget,"Name ");
		BREAK_IF( !(m_HeroLv&&m_HeadIcon&&m_HeroName) );
		m_HeadIcon->setTouchEnabled(true);
		m_HeadIcon->addTouchEventListener(this,toucheventselector(CMainUINormal::clickHead));

		//左上，副本入口 组队
		Button* pBtnCopyMap = (Button*)Helper::seekWidgetByName(m_pWidget,"BtnCopyMap");
		Button* pBtnTeam = (Button*)Helper::seekWidgetByName(m_pWidget,"ButtonTeam");
		BREAK_IF( !(pBtnCopyMap&&pBtnTeam) );
		pBtnCopyMap->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickCopyMap));
		pBtnTeam->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickTeam));
		Widget* pBtnTips = pBtnTeam->getChildByName("TeamTips");

		//任务按钮
		Button* pBtnTask = (Button*)Helper::seekWidgetByName(m_pWidget,"BtnTask");
		BREAK_IF( !pBtnTask );
		pBtnTask->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickTask));

		//摇杆
		m_JoyStick = (ImageView*)Helper::seekWidgetByName(m_pWidget,"JoyStick");
		BREAK_IF( !m_JoyStick );
		m_JoyStick->setTouchEnabled(true);
		m_JoyStick->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickJoyStick));

		//右下 菜单
		Layout* PanelClipedB = (Layout*)Helper::seekWidgetByName(m_pWidget,"ButtomCliped");
		m_panelMenuB = (Layout*)Helper::seekWidgetByName(m_pWidget,"ButtomMenus");
		m_BtnSwitchB = (Button*)Helper::seekWidgetByName(m_pWidget,"ButtomSwitch");
		for (int i=0;i<FunctionTypeRB_Max;++i)
		{
			Button* pBtn = (Button*)Helper::seekWidgetByName(m_panelRB,CCString::createWithFormat("%d",i)->getCString());
			BREAK_IF(!pBtn);
			pBtn->setTag(i);
			pBtn->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickMenuRB));
		}
		Button* pMailBtn = (Button*)Helper::seekWidgetByName(m_panelRB,"ButtonShop");
		Button* pManufactureBtn = (Button*)Helper::seekWidgetByName(m_panelRB,"ButtonRankingList");
		BREAK_IF( !(m_BtnSwitchB&&PanelClipedB&&m_panelMenuB&&pMailBtn&&pManufactureBtn) );
		m_panelMenuB->setPosition(Point(1200,0));
		PanelClipedB->setClippingEnabled(true);
		m_BtnSwitchB->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickSwitchB));
		pMailBtn->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickMail));
		pManufactureBtn->addTouchEventListener(this, toucheventselector(CMainUINormal::ClickManufacture));

		//右上 菜单
		Layout* PanelClipedT = (Layout*)Helper::seekWidgetByName(m_pWidget,"TopCliped");
		m_panelMenuT = (Layout*)Helper::seekWidgetByName(m_pWidget,"TopMenus");
		m_BtnSwitchT = (Button*)Helper::seekWidgetByName(m_pWidget,"ButtonSwitcher");
		Button* pBtnMap = (Button*)Helper::seekWidgetByName(m_pWidget,"BtnMap");
		m_mapName = (Text*)Helper::seekWidgetByName(m_pWidget,"LabelMapName");
		BREAK_IF( !(m_panelMenuT&&m_BtnSwitchT&&PanelClipedT&&m_mapName&&pBtnMap) );
		m_BtnSwitchT->setEnabled(false);
		m_panelMenuT->setEnabled(false);
		PanelClipedT->setClippingEnabled(true);
		m_panelMenuT->setPosition(Point(380,0));
		m_BtnSwitchT->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickSwitchT));
		pBtnMap->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickMap));

		//聊天
		m_pChatUI = (Layout*)Helper::seekWidgetByName(m_pWidget,"ChatLayout");
		m_pButtonChat =  (Button*)Helper::seekWidgetByName(m_pWidget,"ChatBtn");
		m_pButtonChat->addTouchEventListener(this,toucheventselector(CMainUINormal::clickChat));

		m_pMsgWind = CScrollMsgForMainUI::create();
		m_pMsgWind->setSize(m_pChatUI->getSize());
		m_pMsgWind->setTouchEnabled(false);
		m_pMsgWind->setOpacity(100);
		m_pMsgWind->SetMaxMsgNum(1);
		m_pMsgWind->setBackGroundColor(Color3B::GRAY);
		ChatMainUI *pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
		if (pChatUI)
		{
			m_pMsgWind->SetTouchNameListenner(gGameUILayer->getUI(IDU_CHATMAINUI), (SEL_TouchNameLinkEvent)&ChatMainUI::clickNameLink4MainUI);
			m_pMsgWind->SetTouchItemListenner(gGameUILayer->getUI(IDU_CHATMAINUI), (SEL_TouchItemLinkEvent)&ChatMainUI::clickItemLink4MainUI);
			m_pMsgWind->addTouchEventListener(this, (SEL_TouchEvent)&CMainUINormal::clickChatWind);
		}
		m_pChatUI->addChild(m_pMsgWind);
		m_pChatUI->setVisible(false);

		Widget *pHorn = Helper::seekWidgetByName(m_pWidget,"Image_Horn");
		m_pHornWind = HornContorller::Create(pHorn);
		m_pHornWind->SetDelegate(m_pMsgWind);
		CC_SAFE_RETAIN(m_pHornWind);
		m_pChatUI->addChild(gPromptCenter->GetWidgetNormal());

		//匹配副本
		m_pMatchStatusUI = Helper::seekWidgetByName(m_panelLT,"MatchStatusUI");
		Widget* pMatchBg = Helper::seekWidgetByName(m_panelLT,"MatchBg");
		m_pMatchSeconds = Label::createWithBMFont("assets/common/font/timer.fnt",CCString::createWithFormat("60")->getCString());
		m_pMatchSeconds->setPosition(Point(180,230));
		pMatchBg->addChild(m_pMatchSeconds);
		m_pBtnOpenMatchStatus = (Button*)Helper::seekWidgetByName(m_panelLT,"BtnOpenMatchStatus");
		m_pMatchSign = Helper::seekWidgetByName(m_panelLT,"MatchingSign");
		m_pMatchSign->setVisible(false);
		BREAK_IF(!(m_pMatchStatusUI&&m_pMatchSeconds&&m_pBtnOpenMatchStatus));
		m_pMatchCopyName = RichTextEx::create();
		m_pMatchCopyName->setPosition(Point(90,30));
		m_pMatchCopyName->SetFontSize(20.0f);
		m_pMatchStatusUI->addChild(m_pMatchCopyName);
		m_pBtnOpenMatchStatus->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickOpenMatch));
		m_pMatchStatusUI->setTouchEnabled(true);
		m_pMatchStatusUI->addTouchEventListener(this,toucheventselector(CMainUINormal::ClickGoToMatch));
		addOutSideTouchEventListener(this,OutSide_TouchEvent(&CMainUINormal::CloseMatchStatusUI));

		//系统功能提示
		gSysTipsMgr->SetWidget(systype_team,action_visible,pBtnTips);
		gSysTipsMgr->SetWidget(systype_chat,action_blink,m_pButtonChat);
		return true;
	} while (0);
	
	return false;
}

void CMainUINormal::onOpen()
{
	GameUIWithOutSideTouchEvent::onOpen();
	updateLv();
	updateHp();
	updateMp();
	updateMapName(gMap->getMapData()->name);
	addChild(gPromptCenter->GetWidgetIcons());
	ShowMatchStatus();
	gJoyStick->removeFromParent();
	m_JoyStick->addChild(gJoyStick);
	gIndicatorLayer->RemoveIndicators();
}

void CMainUINormal::onClose()
{
	GameUIWithOutSideTouchEvent::onClose();
}

void CMainUINormal::update(float dt)
{
	gJoyStick->update(dt);	
	m_pMsgWind->Update(dt);
	InitHeadIcon();
	if (gMacthMachine->IsMatchStarted())
	{
		if (m_pMatchStatusUI->isEnabled())
		{
			if (gMacthMachine->GetMatchCountSeconds()>=0.0f)
			{
				m_pMatchSeconds->setString(CCString::createWithFormat("%d",(int)gMacthMachine->GetMatchCountSeconds())->getCString());
				m_pMatchSeconds->setVisible(true);
				m_pMatchSign->setVisible(false);
			}
			else
			{
				m_pMatchSeconds->setVisible(false);
				m_pMatchSign->setVisible(gMacthMachine->GetMatchMode() == MatchMode_Match);
			}

			m_fMatchUIShowSeconds += dt;
			if (m_fMatchUIShowSeconds >= 3.0f)
			{
				CloseMatchStatusUI();
			}
		}
	}
	else
	{
		m_pMatchStatusUI->setEnabled(false);
		m_pBtnOpenMatchStatus->setEnabled(false);
	}
}


void CMainUINormal::updateLv()
{
	m_HeroLv->setText(CCString::createWithFormat("%d",gHero->GetLevel())->getCString());
}

void CMainUINormal::updateHp()
{

}

void CMainUINormal::updateMp()
{

}

void CMainUINormal::InitHeadIcon()
{
	if (!m_bIconInit && gHero->GetCareer() != 0)
	{
		m_HeadIcon->loadTexture(gHero->getHeadIcon());
		m_HeroName->setText(gHero->GetRoleName());
		m_bIconInit = true;
	}
}

void CMainUINormal::ClickTask(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		gGameUILayer->open(IDU_MissionlUI);
	}
}

void CMainUINormal::ClickCopyMap(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		gGameUILayer->open(IDU_WORLDMAPUI);
	}
}

void CMainUINormal::ClickTeamCopyMap(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		pk::C2GS_ReqEnterCopyMap cmd;
		cmd.npcId = 0;
		cmd.npcDataID = 0;
		cmd.enterType = 2;
		cmd.enterMapDataId = 1001;
		cmd.Send(gNetSocket);
	}
}

void CMainUINormal::ClickQuit(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		gHero->LeaveCopy();
		gGameUILayer->close(this);
		//gGameUILayer->open(IDU_MAIN);
	}
}

void CMainUINormal::ClickQuit0(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		gGameUILayer->close(this);
	}
}

void CMainUINormal::ClickSwitchB(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		if(getActionManager()->getNumberOfRunningActionsInTarget(m_panelMenuB)>0)
			return;

		Point pos = m_BtnSwitchB->isFlippedX()?Point(0,0):Point(1200,0);
		auto func = [this]()
		{
			m_BtnSwitchB->setFlippedX(!m_BtnSwitchB->isFlippedX());
		};
		m_panelMenuB->runAction(Sequence::create(EaseElasticInOut::create(MoveTo::create(0.5f,pos),0.5f),CallFunc::create(func),NULL));
	}
}

void CMainUINormal::ClickSwitchT(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		if(getActionManager()->getNumberOfRunningActionsInTarget(m_panelMenuT)>0)
			return;

		Point pos = m_BtnSwitchT->isFlippedX()?Point(0,0):Point(380,0);
		auto func = [this]()
		{
			m_BtnSwitchT->setFlippedX(!m_BtnSwitchT->isFlippedX());
		};
		m_panelMenuT->runAction(Sequence::create(EaseElasticInOut::create(MoveTo::create(0.5f,pos),0.5f),CallFunc::create(func),NULL));
	}
}

void CMainUINormal::ClickJoyStick(Ref *pSender, TouchEventType type)
{
	Widget* pTouchUI = (Widget*)pSender;
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		gJoyStick->TouchBegan(pTouchUI->getTouchStartPos());
		break;
	case TOUCH_EVENT_MOVED:
		gJoyStick->TouchMoved(pTouchUI->getTouchMovePos());
		break;
	case TOUCH_EVENT_ENDED:
		gJoyStick->TouchEnded(pTouchUI->getTouchEndPos());
		break;
	case TOUCH_EVENT_CANCELED:
		gJoyStick->TouchCancelled(pTouchUI->getTouchEndPos());
		break;
	default:
		break;
	}
}

void CMainUINormal::clickChat(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		GameUI* pUI = gGameUILayer->open(IDU_CHATMAINUI);
		if(pUI) pUI->setPosition(Point::ZERO);
	}
}

void CMainUINormal::clickChatWind(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		m_bMsgWindScrolled = false;
		break;
	case TOUCH_EVENT_MOVED:
		m_bMsgWindScrolled = true;
		break;
	case TOUCH_EVENT_ENDED:
		m_bMsgWindScrolled = false;
		break;
	}
}

void CMainUINormal::updateHornMsg(pk::GS2C_Chat *value)
{
	m_pHornWind->PushMsg(value);
}

void CMainUINormal::updateChatMsg(pk::GS2C_Chat *value)
{
	ChatMainUI* pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
	if (pChatUI->IsCurChannelMsg(value))
	{
		m_pMsgWind->PushMsg(value,value->senderId==gHero->GetId());
		m_pMsgWind->Flush(true);
	}
}

void CMainUINormal::ShowMatchStatus()
{
	//匹配未启动,不显示
	if (!gMacthMachine->IsMatchStarted())
	{
		m_pMatchStatusUI->setEnabled(false);
		m_pBtnOpenMatchStatus->setEnabled(false);
		return;
	}

	m_pMatchStatusUI->setEnabled(true);
	m_pBtnOpenMatchStatus->setEnabled(true);

	m_pMatchSeconds->setString(CCString::createWithFormat("%d",(int)gMacthMachine->GetMatchCountSeconds())->getCString());
	if (gMacthMachine->GetMatchCopyMapIdToEnter())
	{
		GameCopy* pGameCopy = gCopyDataMgr->GetGameCopy(gMacthMachine->GetMatchCopyMapIdToEnter());
		if(!pGameCopy) return;
		LocaleCfg* pLocaleCfg = LocaleTableData.get(pGameCopy->localeId);
		MapCfg* pMapCfg = MapData.get(pGameCopy->mapId);
		if(pLocaleCfg&&pMapCfg)
		{
			m_pMatchCopyName->ParseAndLayout(CCString::createWithFormat("%s-%s",pLocaleCfg->name.c_str(),pMapCfg->name.c_str())->getCString());
		}
	} 
	else
	{
		//随机副本
		m_pMatchCopyName->ParseAndLayout(STR_Match_randomCopy);
	}
	OpenMatchStatusUI();
}

void CMainUINormal::OpenMatchStatusUI()
{
	if (getActionManager()->getNumberOfRunningActionsInTarget(m_pMatchStatusUI)>0 || m_pMatchStatusUI->getPositionY() == 285)
	{
		return;
	}

	std::function<void()> func = [this]()
	{
		m_pBtnOpenMatchStatus->setEnabled(false);
		m_fMatchUIShowSeconds = -1.0f;
	};
	m_pMatchStatusUI->runAction(Sequence::create(CallFunc::create(func),MoveTo::create(1.0f,Point(m_pMatchStatusUI->getPositionX(),285)),NULL));
}

void CMainUINormal::CloseMatchStatusUI()
{
	if (getActionManager()->getNumberOfRunningActionsInTarget(m_pMatchStatusUI)>0 || m_pMatchStatusUI->getPositionY() == 410)
	{
		return;
	}

	std::function<void()> func = [this]()
	{
		m_pMatchStatusUI->stopAllActions();
		m_pBtnOpenMatchStatus->setEnabled(true);
	};
	m_pMatchStatusUI->runAction(Sequence::create(MoveTo::create(1.0f,Point(m_pMatchStatusUI->getPositionX(),410)),CallFunc::create(func),NULL));
}

void CMainUINormal::clickHead(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		gCocosAudio->PlayEffect(17);
		gGameUILayer->open(IDU_HeroInfo);
		/*
		pk::ItemDataIdAndCnt testItem;
		testItem.itemDataID = 1;
		testItem.cnt = 1;
		pk::GS2C_GiveSelectionToContinueCopy testValue;
		testValue.steps = 1;
		testValue.itemInfos.push_back(testItem);
		CWaveEnd::s_waveRewards[1] = testValue;
		CWaveEnd::s_waveRewards[2] = testValue;
		//队员初始未选择
		for (unsigned int i=0; i<CTeamUI::s_teamInfo.member_list.size(); ++i)
		{
			CTeamUI::s_teamInfo.member_list[i].isContinue = -1;
		}
		gGameUILayer->open(IDU_WaveEnd);
		*/
	}
}

void CMainUINormal::updateMapName(const std::string& name)
{
	m_mapName->setText(name);
}

void CMainUINormal::ClickTeam(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		openTeamUI(UiOpenType_FromMainUI);
	}
}

void openTeamUI(UiOpenType openType)
{
	gGameUILayer->close(IDU_TEAMAPPLICATION);
	gGameUILayer->close(IDU_Social);
	GameUI* pGameUI = nullptr;
	do 
	{
		//有队伍直接打开队伍
		if (!CTeamUI::s_teamInfo.member_list.empty())
		{
			pGameUI = gGameUILayer->open(IDU_Social);
			break;
		}
		//没有队伍,有邀请
		if (!TeamApplicationUI::s_Inviters.empty())
		{
			pGameUI = gGameUILayer->open(IDU_TEAMAPPLICATION);
			break;
		}
		//没有队伍,没有邀请,创建队伍
		pGameUI = gGameUILayer->open(IDU_Social);
		pk::C2GS_CreateTeam_Req cmd = { 3 };
		cmd.Send(gNetSocket);
	} while (0);

	if(pGameUI)
	{
		pGameUI->setPosition(openType == UiOpenType_FromMainUI ? Point::ZERO : Point(63.0f,-34.0f));
	}
}

void CMainUINormal::ClickMap(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		//COneStroke*		pOneStroke = (COneStroke*)gGameUILayer->open(IDU_OneStrokeUI);
		//if(pOneStroke) pOneStroke->InitStrokeInfo(1);
		//COpenLock*		pOpenLock = (COpenLock*)gGameUILayer->open(IDU_OpenLock);
		//if(pOpenLock) pOpenLock->InitWithLockInfo(1);
		//gIndicatorLayer->AddStaticIndicator(38,39,5,5);
		/*
		pk::GS2C_GiveSelectionToContinueCopy value;
		value.steps = 0;
		value.curAwardItemCnt = 1;
		value.curAwardItemDataId = 5000;
		value.preAwardItemCnt = 10;
		value.preAwardItemDataId = 5001;
		CWaveEnd::s_waveRewards[value.steps] = value;
		//队员初始未选择
		for (unsigned int i=0; i<CTeamUI::s_teamInfo.member_list.size(); ++i)
		{
			CTeamUI::s_teamInfo.member_list[i].isContinue = -1;
		}
		gGameUILayer->open(IDU_WaveEnd);
		*/
	}
}

void CMainUINormal::ClickMenuRB(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		int nTag = ((Widget*)pSender)->getTag();
		switch (nTag)
		{
		case FunctionTypeRB_SkyBook:
			gGameUILayer->open(IDU_SkyBookUI);
			break;
		case FunctionTypeRB_Friend:
			gGameUILayer->open(IDU_Friend);
			break;
		case FunctionTypeRB_GodDevice:
			gGameUILayer->open(IDU_GodDeviceUI);
			break;
		case FunctionTypeRB_Bag:
			gGameUILayer->open(IDU_RoleAttri);
			break;
		case FunctionTypeRB_Pet:
			break;
		case FunctionTypeRB_ArmyGroup:
			gGameUILayer->open(IDU_AddLegionUI);
			break;
		case FunctionTypeRB_Skill:
			break;
		case FunctionTypeRB_Produce:
			gGameUILayer->open(IDU_ManufactureUI);
			break;
		case FunctionTypeRB_Strength:
			gGameUILayer->open(IDU_HallTechTreeUI);
			break;
		case FunctionTypeRB_Expand3:
			gGameUILayer->open(IDU_HallTechUI);
			break;
		default:
			break;
		}
	}
}

void CMainUINormal::ClickMail(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		gGameUILayer->open(IDU_MailUI);
	}
}

void CMainUINormal::ClickManufacture(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		gGameUILayer->open(IDU_ManufactureUI);
	}
}

void CMainUINormal::ClickGoToMatch(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		gGameUILayer->open(IDU_WORLDMAPUI);
	}
}

void CMainUINormal::ClickOpenMatch(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		OpenMatchStatusUI();
	}
}

MainUI* MainUI::ShowMainUI(GameMapFuncType mapType)
{
	DramaUI* pDramaUI = (DramaUI*)gGameUILayer->getActiveUI(IDU_Drama);
	if(pDramaUI && !pDramaUI->getcurShowMode())
	{
		return nullptr;
	}

	MainUI* pUI = NULL;
	switch (mapType)
	{
	case GameMapFuncType_Normal:
		{
			pUI = dynamic_cast<MainUI*>(gGameUILayer->getActiveUI(IDU_MainUINormal));
			if( !pUI )
			{
				gGameUILayer->close(IDU_MainUIFight);
				//消息中心
				gPromptCenter->GetWidgetIcons()->removeFromParentAndCleanup(false);
				pUI = dynamic_cast<MainUI*>(gGameUILayer->open(IDU_MainUINormal));
			}
		}
		break;
	case GameMapFuncType_Fight:
		{
			pUI = dynamic_cast<MainUI*>(gGameUILayer->getActiveUI(IDU_MainUIFight));
			if( !pUI )
			{
				gGameUILayer->close(IDU_MainUINormal);
				//消息中心
				gPromptCenter->GetWidgetIcons()->removeFromParentAndCleanup(false);
				pUI = dynamic_cast<MainUI*>(gGameUILayer->open(IDU_MainUIFight));
			}
		}
		break;
	default:
		{
			LOGE("MainUI::ShowMainUI(errType) failed.");
		}
		break;
	}

	return pUI;
}

void MainUI::CloseMainUI()
{
	gGameUILayer->close(IDU_MainUINormal);
	gGameUILayer->close(IDU_MainUIFight);
}

MainUI* MainUI::GetActiveMainUI()
{
	if ( !gMap )
	{
		return NULL;
	}

	if ( gMap->isFightMap() )
	{
		return dynamic_cast<MainUI*>(gGameUILayer->getActiveUI(IDU_MainUIFight));
	}
	else
	{
		return dynamic_cast<MainUI*>(gGameUILayer->getActiveUI(IDU_MainUINormal));
	}
}

MainUI* MainUI::GetMainUI()
{
	if ( !gMap )
	{
		return NULL;
	}

	if ( gMap->isFightMap() )
	{
		return dynamic_cast<MainUI*>(gGameUILayer->getUI(IDU_MainUIFight));
	}
	else
	{
		return dynamic_cast<MainUI*>(gGameUILayer->getUI(IDU_MainUINormal));
	}
}

