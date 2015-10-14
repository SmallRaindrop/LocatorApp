#include "GamePrompt.h"
#include "GameScene/GameDataManager.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/MessageCenter.h"
#include "GameScene/GameTipsLayer.h"
#include "ChatMainUI.h"
#include "MessageBoxUI.h"
#include "Net/NetDispatcher.h"
#include "Net/pk_team.h"
#include "GameScene/GameUILayer.h"
#include "TeamUI.h"
#include "CustomCtrl/ScrollTable.h"
#include "CustomCtrl/RichTextEX.h"
#include "ResMgr/CtrlAllocator.h"
#include "UIHelper.h"
#include "../Net/pk_trade.h"
#include "MainUINormal.h"

GamePromptCenter::GamePromptCenter() : m_pNotice1(NULL),m_pNotice2(NULL),m_pPrompt(NULL), m_pNormal(NULL),m_pIconsFrame(NULL),
	m_pNotice1Frame(NULL),m_pScrollText(NULL)
{
	initialize();
}

GamePromptCenter::~GamePromptCenter()
{
	release();
}

bool GamePromptCenter::initSystemIcons()
{
	Button* pBtn = NULL;

	pBtn = (Button*)gCtrlAllocator->LoadCtrl("Team_Menu");
	m_Icons.push_back(make_pair(pBtn,false));
	setIconMailMsgNum(0);

	pBtn = (Button*)gCtrlAllocator->LoadCtrl("Team_Menu");
	m_Icons.push_back(make_pair(pBtn,false));

	pBtn = (Button*)gCtrlAllocator->LoadCtrl("Team_Menu");
	m_Icons.push_back(make_pair(pBtn,false));

	pBtn = (Button*)gCtrlAllocator->LoadCtrl("Team_Menu");
	m_Icons.push_back(make_pair(pBtn,false));

	GetIconTeam()->setPosition(Point(340,0));
	setIconTeamMsgNum(0);

	GetIconChat()->setVisible(false);
	GetIconMail()->setVisible(false);
	GetIconTrade()->setVisible(false);

	m_pIconsFrame->addChild(GetIconMail());
	m_pIconsFrame->addChild(GetIconChat());
	m_pIconsFrame->addChild(GetIconTeam());
	m_pIconsFrame->addChild(GetIconTrade());

	GetIconMail()->addTouchEventListener(this, SEL_TouchEvent(&GamePromptCenter::onIconMailClicked));
	GetIconChat()->addTouchEventListener(this, SEL_TouchEvent(&GamePromptCenter::onIconChatClicked));
	GetIconTeam()->addTouchEventListener(this, SEL_TouchEvent(&GamePromptCenter::onIconTeamClicked));
	GetIconTrade()->addTouchEventListener(this, SEL_TouchEvent(&GamePromptCenter::onIconTradeClicked));

	return true;
}

void GamePromptCenter::updatePositions()
{
	// 适配处理
	float fRatio = gDirector->getVisibleSize().height / gDirector->getVisibleSize().width;
	float fNewHeight = fRatio * 1334;
	float fOffsetY = 0.0f;
	if (fNewHeight > 750)
	{
		fOffsetY = fNewHeight - 750;
	}

	GetWidgetNotice1()->setPosition(Point(667, 590+fOffsetY));
	GetWidgetNotice1()->setGlobalZOrder(1);
	GetWidgetNotice1()->setOpacity(0);
	GetWidgetNotice1()->setTouchEnabled(false);
	GetWidgetPrompt()->setPosition(Point(0, 0));
	//GetWidgetIcons()->setPosition(Point(200,700+fOffsetY));
}

bool GamePromptCenter::initialize()
{
	m_pNotice1 = gCtrlAllocator->LoadCtrl("Notice1");
	m_pNotice2 = Layout::create();
	m_pPrompt = Layout::create();
	m_pNormal = Layout::create();
	m_pIconsFrame = Layout::create();

	if ( !m_pNotice1 || !m_pNotice2 || !m_pPrompt || !m_pNormal || !m_pIconsFrame )
	{
		return false;
	}

	m_pNotice1->retain();
	m_pNotice2->retain();
	m_pPrompt->retain();
	m_pNormal->retain();
	m_pIconsFrame->retain();
	m_pIconsFrame->setEnabled(false);

	m_pNotice1->setTouchEnabled(false);
	m_pIconsFrame->setTouchEnabled(false);

	initSystemIcons();

	updatePositions();

	m_pNotice1Frame = dynamic_cast<Layout*>(m_pNotice1->getChildByName("Panel_Clip"));
	if ( m_pNotice1Frame )
	{
		m_pNotice1Frame->setClippingEnabled(true);
	}

	return true;
}

void GamePromptCenter::release()
{
	CC_SAFE_RELEASE(m_pNotice1);
	CC_SAFE_RELEASE(m_pNotice2);
	CC_SAFE_RELEASE(m_pPrompt);
	CC_SAFE_RELEASE(m_pNormal);
	CC_SAFE_RELEASE(m_pIconsFrame);
	m_Icons.clear();
	m_Timers.clear();
}

void GamePromptCenter::addPromptText(const string& msg)
{
	RichTextEx* pText = NULL;
	if( m_promptTextCache.size() > 0 )
	{
		pText = m_promptTextCache.front();
		m_promptTextCache.pop();
	}
	else
	{
		pText = RichTextEx::create();
		pText->SetFontSize(24);
		pText->setColor(Color3B::YELLOW);
		m_pPrompt->addChild(pText);
	}

	if ( pText )
	{
		pText->setPosition(Point(667,400));
		pText->ParseAndLayout(msg);

		float deltaX = 0.0f;
		float deltaY = 100.0f;

		Size bgSize = pText->getSize();
		deltaY -= m_promptText.size()*bgSize.height;

		pText->runAction(FadeIn::create(0.5f));
		pText->runAction(MoveBy::create(0.5f,Point(deltaX,deltaY)));

		m_promptText.push_back(make_pair(pText,0.0f));
	}

	while (m_promptText.size() > 2)
	{
		popPromptText();
	}
}

void GamePromptCenter::popPromptText()
{
	if ( m_promptText.empty() )
	{
		return ;
	}

	RichTextEx* pText = m_promptText[0].first;
	if ( pText )
	{
		float deltaX = 0.0f;
		float deltaY = 100.0f;

		pText->runAction(FadeOut::create(0.5f));
		pText->runAction(Sequence::create(MoveBy::create(0.5f,Point(deltaX,deltaY)),CallFunc::create( CC_CALLBACK_0(GamePromptCenter::onPromptTextPoped,this,pText)),NULL));
	}

	m_promptText.erase(m_promptText.begin());

 	// 所有提示信息往上顶
 	for ( size_t i = 0; i<m_promptText.size(); ++i )
 	{
		RichTextEx* pTextReady = m_promptText[i].first;
		if ( pTextReady )
		{
			ActionInterval* pAction = MoveBy::create(0.2f,Point(0,pText->getSize().height+3));
			pTextReady->runAction(pAction);
		}
 	}
}

void GamePromptCenter::onPromptTextPoped(RichTextEx* pText)
{
	if ( pText )
	{
		m_promptTextCache.push(pText);
	}
}


void GamePromptCenter::addNormalText(const string& msg)
{
	Text* pText = NULL;
	if( m_normalTextCache.size() > 0 )
	{
		pText = m_normalTextCache.front();
		m_normalTextCache.pop();
	}
	else
	{
		pText = Text::create();
		if ( pText )
		{
			m_pNormal->addChild(pText);
		}
	}

	if ( pText )
	{
		pText->setAnchorPoint(Point(0,0));
		pText->setTextHorizontalAlignment(TextHAlignment::LEFT);
		pText->setFontSize(14);
		pText->setColor(Color3B(155,10,10));
		pText->setColor(Color3B::WHITE);
		pText->setText(msg);
		pText->setVisible(true);

		m_normalText.push_back(make_pair(pText,0.0f));

		// 所有提示信息往上顶
		for ( size_t i = 0; i<m_normalText.size(); ++i )
		{
			float deltaX = 0.0f;
			float deltaY = 0.0f;

			Size tsize = pText->getSize();
			deltaY = (m_normalText.size()-i-1)*tsize.height;

			Text* pTextReady = m_normalText[i].first;
			if ( pTextReady )
			{
				pTextReady->setPosition(Point(deltaX,deltaY));
			}
		}
	}

	while (m_normalText.size() > 5)
	{
		popNormalText();
	}
}

void GamePromptCenter::popNormalText()
{
	if ( m_normalText.empty() )
	{
		return ;
	}

	Text* pText = m_normalText[0].first;
	if ( pText )
	{
		pText->setVisible(false);
	}

	m_normalText.erase(m_normalText.begin());

	onNormalTextPoped(pText);
}

void GamePromptCenter::onNormalTextPoped(Text* pText)
{
	m_normalTextCache.push(pText);
}

void GamePromptCenter::addNotice1Text(const string& msg)
{
	if ( !m_pScrollText )
	{
		m_pScrollText = (Text*)m_pNotice1Frame->getChildByName("Label_ScrollText");
		m_pScrollText->setFontSize(Font_Size_Notice1);
	}
	
	if ( m_pScrollText )
	{
		m_pScrollText->setVisible(true);
		m_pScrollText->setText(msg);
		m_pScrollText->setPositionX(m_pNotice1Frame->getSize().width);
		m_pNotice1->stopAllActions();
		m_pNotice1->setOpacity(255);
	}
}

void GamePromptCenter::scrollNotice1Text(float dt)
{
	static const int NOTICE1_SCROLL_SPEED = 100;
	m_pScrollText->setPositionX(m_pScrollText->getPositionX() - dt * NOTICE1_SCROLL_SPEED);
	if (m_pScrollText->getPositionX() + m_pScrollText->getSize().width < 0)
	{
		m_pScrollText->setVisible(false);
		if ( gMessageCenter->GetMessageCache(SystemMessage_Notice1).length() == 0 )
			m_pNotice1->runAction(FadeOut::create(2.0f));
	}
}

void GamePromptCenter::flickIcon(Button* pBtn)
{
	pBtn->stopAllActions();
	pBtn->runAction(RepeatForever::create(Blink::create(1.0f, 1)));
}

void GamePromptCenter::flickIconMail()
{
	flickIcon(GetIconMail());
	SetIconMailFlicked();
}

void GamePromptCenter::flickIconChat()
{
	flickIcon(GetIconChat());
	SetIconChatFlicked();
}

void GamePromptCenter::flickIconTeam()
{
	flickIcon(GetIconTeam());
	SetIconTeamFlicked();
}

void GamePromptCenter::flickIconTrade()
{
	flickIcon(GetIconTrade());
	SetIconTradeFlicked();
}


void GamePromptCenter::stopIconMailFlick()
{
	gMessageCenter->GetMessageCache(SystemMessage_Mail).clear();
	SetIconMailFlicked(false);
	GetIconMail()->stopAllActions();
	GetIconMail()->setVisible(false);
}

void GamePromptCenter::stopIconChatFlick()
{
	gMessageCenter->GetMessageCache(SystemMessage_Chat).clear();
	SetIconChatFlicked(false);
	GetIconChat()->stopAllActions();
	GetIconChat()->setVisible(false);
	GetIconChat()->setTouchEnabled(false);
}

void GamePromptCenter::stopIconTeamFlick()
{
	gMessageCenter->GetMessageCache(SystemMessage_Team).clear();
	SetIconTeamFlicked(false);
	GetIconTeam()->stopAllActions();
}

void GamePromptCenter::stopIconTradeFlick()
{
	gMessageCenter->GetMessageCache(SystemMessage_Trade).clear();
	SetIconTradeFlicked(false);
	GetIconTrade()->stopAllActions();
	GetIconTrade()->setVisible(false);
	GetIconTrade()->setTouchEnabled(false);
}






void GamePromptCenter::setIconMailMsgNum(int nNum)
{
	Text *pText = (Text*)Helper::seekWidgetByName(m_Icons[0].first, "Label_Num");
	if (pText)
	{
		pText->setText(CCString::createWithFormat("%d", nNum)->getCString());
	}
}

void GamePromptCenter::setIconChatMsgNum(int nNum)
{
	if (nNum == 0)
	{
		stopIconChatFlick();
	}

	Text *pText = (Text*)Helper::seekWidgetByName(m_Icons[1].first, "Label_Num");
	if (pText)
		pText->setText(CCString::createWithFormat("%d", nNum)->getCString());
}

void GamePromptCenter::setIconTeamMsgNum(int nNum)
{
	if (nNum == 0)
	{
		stopIconTeamFlick();
	}

	Text *pText = (Text*)Helper::seekWidgetByName(m_Icons[2].first, "Label_Num");
	if (pText)
	{
		pText->setText(CCString::createWithFormat("%d", nNum)->getCString());
		pText->getParent()->setVisible(nNum>0);
		GetIconTeam()->setVisible(true);
	}
}

void GamePromptCenter::setIconTradeMsgNum(int nNum)
{
	if (nNum == 0)
	{
		stopIconTradeFlick();
	}

	Text *pText = (Text*)Helper::seekWidgetByName(m_Icons[3].first, "Label_Num");
	if (pText)
		pText->setText(CCString::createWithFormat("%d", nNum)->getCString());
}

void GamePromptCenter::onIconMailClicked(Ref *pSender, TouchEventType type)
{
	if (type != TOUCH_EVENT_ENDED)
		return;

	gCocosAudio->PlayEffect(90);
	//stopIconMailFlick();
}

void GamePromptCenter::onIconChatClicked(Ref *pSender, TouchEventType type)
{
	if (type != TOUCH_EVENT_ENDED)
		return;

	gCocosAudio->PlayEffect(90);
}

void GamePromptCenter::onIconTeamClicked(Ref *pSender, TouchEventType type)
{
	if (type != TOUCH_EVENT_ENDED)
		return;

	//gGameUILayer->open(IsIconTeamFlicked()?IDU_TEAMAPPLICATION:IDU_Social);
	gGameUILayer->open(IDU_TEAMAPPLICATION);

	gCocosAudio->PlayEffect(90);
	//stopIconTeamFlick();	// 无论如何组队图标只会存储一种消息，点击后停止闪烁
}

void GamePromptCenter::onIconTradeClicked(Ref *pSender, TouchEventType type)
{
	if (type != TOUCH_EVENT_ENDED)
		return;

	class TradeLogic :public Ref
	{
	public:
		void IsAcceptTrade(bool bAccepte)
		{
			pk::C2GS_ReponseTrade cmd;
			cmd.tradeId = m_nTradeId;
			if (bAccepte)
			{
				cmd.reponse = 1;
			}
			else
			{
				cmd.reponse = 0;
			}
			cmd.Send(gNetSocket);
		}

		int64	m_nTradeId;
		string	m_strTradeName;
	};

	static TradeLogic obj;
	obj.m_nTradeId = atof(gMessageCenter->GetMessageCache(SystemMessage_Trade).pop().c_str());
	obj.m_strTradeName = gMessageCenter->GetMessageCache(SystemMessage_Trade).pop();
	setIconTradeMsgNum(gMessageCenter->GetMessageCache(SystemMessage_Trade).length()/2);

	char str[256] = {0};
	sprintf(str,"%s %s %s",STR_MAIL_PLAYER.c_str(),obj.m_strTradeName.c_str(),STR_Trade_Message1.c_str());
	CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,str,STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),&obj,YESORNO_EVENT(&TradeLogic::IsAcceptTrade));
	//stopIconTradeFlick();
	gCocosAudio->PlayEffect(90);
}

void GamePromptCenter::refreshIconsPosition()
{
	static const float COL_SPACING = 120.0f;

	float offsetX = GetIconTeam()->getPositionX()-COL_SPACING;
	float offsetY = 0.0f;

	if ( IsIconChatFlicked() )
	{
		GetIconChat()->setPosition(Point(offsetX,offsetY));
		offsetX -= COL_SPACING;
	}
	if ( IsIconMailFlicked() )
	{
		GetIconMail()->setPosition(Point(offsetX,offsetY));
		offsetX -= COL_SPACING;
	}
	if ( IsIconTradeFlicked() )
	{
		GetIconTrade()->setPosition(Point(offsetX,offsetY));
	}
}

void GamePromptCenter::updateSystemMsg(float dt)
{
	if (gMessageCenter->GetMessageCache(SystemMessage_Msg).length() > 0)
	{
		string msg = gMessageCenter->GetMessageCache(SystemMessage_Msg).pop();

		pk::GS2C_Chat cmd = {5, 0, 0, "System", msg};
		MsgItem* pMsgItem = gChatDataMgr->AddMsg(ChannelType_System,cmd,false);
		ChatMainUI *pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
		if (pChatUI)
		{
			pChatUI->MsgArrive(pMsgItem);
		}
	}
}

void GamePromptCenter::updateSystemNotice1(float dt)
{
	if (m_pScrollText && m_pScrollText->isVisible())
	{
		scrollNotice1Text(dt);
	}
	else if (gMessageCenter->GetMessageCache(SystemMessage_Notice1).length() > 0)
	{
		string msg = gMessageCenter->GetMessageCache(SystemMessage_Notice1).pop();
		addNotice1Text(msg);
	}
}

void GamePromptCenter::updateSystemNotice2(float dt)
{

}

void GamePromptCenter::updateSystemPrompt(float dt)
{
	if (gMessageCenter->GetMessageCache(SystemMessage_Prompt).length() > 0)
	{
		string msg = gMessageCenter->GetMessageCache(SystemMessage_Prompt).pop();
		addPromptText(msg);
	}

	for ( size_t i = 0; i<m_promptText.size(); ++i )
	{
		m_promptText[i].second += dt;
		float deltaTime = m_promptText[i].second;

		if ( deltaTime > 1 )
		{
			popPromptText();
		}
	}
}

void GamePromptCenter::updateSystemNormal(float dt)
{
	if (gMessageCenter->GetMessageCache(SystemMessage_Normal).length() > 0)
	{
		string msg = gMessageCenter->GetMessageCache(SystemMessage_Normal).pop();
		addNormalText(msg);
	}

	for ( size_t i = 0; i<m_normalText.size(); ++i )
	{
		m_normalText[i].second += dt;
		float deltaTime = m_normalText[i].second;

		if ( deltaTime > 30 )
		{
			popNormalText();
		}
	}
}

void GamePromptCenter::updateCompMNMsg(float dt)
{
	if (gMessageCenter->GetMessageCache(SystemMessage_CompMN).length() > 0)
	{
		string msg = gMessageCenter->GetMessageCache(SystemMessage_CompMN).pop();

		pk::GS2C_Chat cmd = {5, 0, 0, "System", msg};
		MsgItem* pMsgItem = gChatDataMgr->AddMsg(ChannelType_System,cmd,false);
		ChatMainUI *pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
		if (pChatUI)
		{
			pChatUI->MsgArrive(pMsgItem);
		}

		addNotice1Text(msg);
	}
}

void GamePromptCenter::updateCompMPMsg(float dt)
{
	if (gMessageCenter->GetMessageCache(SystemMessage_CompMP).length() > 0)
	{
		string msg = gMessageCenter->GetMessageCache(SystemMessage_CompMP).pop();

		pk::GS2C_Chat cmd = {5, 0, 0, "System", msg};
		MsgItem* pMsgItem = gChatDataMgr->AddMsg(ChannelType_System,cmd,false);
		ChatMainUI *pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
		if (pChatUI)
		{
			pChatUI->MsgArrive(pMsgItem);
		}
		addPromptText(msg);
	}
}

void GamePromptCenter::updateSystemAlert(float dt)
{

}

void GamePromptCenter::updateSystemIcons(float dt)
{
	if (gMessageCenter->GetMessageCache(SystemMessage_Mail).length() > 0 && !IsIconMailFlicked() )
	{
		GetIconChat()->setVisible(true);
		GetIconChat()->setTouchEnabled(true);
		flickIconMail();
	}
	if (gMessageCenter->GetMessageCache(SystemMessage_Chat).length() > 0 && !IsIconChatFlicked())
	{
		GetIconChat()->setVisible(true);
		GetIconChat()->setTouchEnabled(true);
		flickIconChat();
	}
	if (gMessageCenter->GetMessageCache(SystemMessage_Team).length() > 0 && !IsIconTeamFlicked())
	{
		flickIconTeam();
	}
	if (gMessageCenter->GetMessageCache(SystemMessage_Trade).length() > 0 && !IsIconTradeFlicked())
	{
		GetIconTrade()->setVisible(true);
		GetIconTrade()->setTouchEnabled(true);
		flickIconTrade();
	}

	if ( gMessageCenter->GetMessageCache(SystemMessage_Mail).length() == 0 )
	{
		stopIconMailFlick();
	}

	if ( gMessageCenter->GetMessageCache(SystemMessage_Chat).length() == 0 )
	{
		stopIconChatFlick();
	}

	if ( gMessageCenter->GetMessageCache(SystemMessage_Team).length() == 0 )
	{
		stopIconTeamFlick();
	}

	if ( gMessageCenter->GetMessageCache(SystemMessage_Trade).length() == 0 )
	{
		stopIconTradeFlick();
	}

	refreshIconsPosition();
}

void GamePromptCenter::updateTimer(float dt)
{
	if(m_Timers.empty()) return;

	vector<SchedulerTimer>::iterator itr = m_Timers.begin();
	for (; itr<m_Timers.end(); ++itr)
	{
		itr->accumulativeTime += dt;
		if (itr->accumulativeTime >= itr->alarmTime)
		{
			if (itr->listener && itr->selector)
			{
				(itr->listener->*itr->selector)();
				m_Timers.erase(itr);
				return;
			}
		}
	}
}

void GamePromptCenter::update(float dt)
{
	updateCompMNMsg(dt);	// 需要放在前面，其内部控件逻辑共享updateSystemMsg + updateSystemNotice1
	updateCompMPMsg(dt);	// 需要放在前面，其内部控件逻辑共享updateSystemMsg + updateSystemPrompt
	updateSystemMsg(dt);
	updateSystemNotice1(dt);
	updateSystemNotice2(dt);
	updateSystemPrompt(dt);
	updateSystemNormal(dt);
	updateSystemAlert(dt);
	updateSystemIcons(dt);
	updateTimer(dt);
}

void GamePromptCenter::AddTimer(float alarmTime,Ref* pListener,SEL_SCHEDULECLEAR selector)
{
	SchedulerTimer timer;
	timer.accumulativeTime = 0.0f;
	timer.alarmTime = alarmTime;
	timer.listener = pListener;
	timer.selector = selector;
	m_Timers.push_back(timer);
}

void GamePromptCenter::ClearTrade()
{
	if ( gMessageCenter->GetMessageCache(SystemMessage_Trade).length() >= 2 )
	{
		gMessageCenter->GetMessageCache(SystemMessage_Trade).pop();
		gMessageCenter->GetMessageCache(SystemMessage_Trade).pop();
		setIconTradeMsgNum(gMessageCenter->GetMessageCache(SystemMessage_Trade).length()/2);
	}
}

void GamePromptCenter::Clear()
{
	while (m_promptText.size() > 0)
	{
		RichTextEx* pText = m_promptText[0].first;
		if ( pText )
		{
			pText->removeFromParent();
		}

		m_promptText.erase(m_promptText.begin());
	}
}