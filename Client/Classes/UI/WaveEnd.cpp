#include "WaveEnd.h"
#include "Net/NetDispatcher.h"
#include "TeamUI.h"

std::map<int,pk::GS2C_GiveSelectionToContinueCopy> CWaveEnd::s_waveRewards;

CWaveEnd::CWaveEnd()
	:GameUI(IDU_WaveEnd,JsonFile_WaveEnd)
{
	m_CountSeconds = 15;
}

CWaveEnd::~CWaveEnd()
{
	s_waveRewards.clear();
}

bool CWaveEnd::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());
		m_pMainUI = Helper::seekWidgetByName(m_pWidget, "Image_Main");
		Button *pRetreatPanel = (Button*)Helper::seekWidgetByName(m_pWidget, "RetreatPanel");
		Button *pContinuePanel = (Button*)Helper::seekWidgetByName(m_pWidget, "ContinuePanel");
		Widget *pUnselPanel = Helper::seekWidgetByName(m_pWidget, "UnselPanel");
		BREAK_IF(!(pRetreatPanel));
		pRetreatPanel->addTouchEventListener(this,toucheventselector(CWaveEnd::clickRetreat));
		pContinuePanel->addTouchEventListener(this,toucheventselector(CWaveEnd::clickContinue));

		m_pRetreatList = CScrollTable::create(false, "WavePlayerName");
		m_pRetreatList->setSize(Size(200, 314));
		m_pRetreatList->setPosition(Point(0,-157));
		m_pRetreatList->SetFontSize(20);
		m_pRetreatList->SetFormat(TCT_STRING, 100, 0.5, 0.5,TCT_NONE);
		m_pRetreatList->setTouchEnabled(false);
		pRetreatPanel->addChild(m_pRetreatList);

		m_pContinueList = CScrollTable::create(false, "WavePlayerName");
		m_pContinueList->setSize(Size(200, 314));
		m_pContinueList->setPosition(Point(0,-157));
		m_pContinueList->SetFontSize(20);
		m_pContinueList->SetFormat(TCT_STRING, 100, 0.5, 0.5,TCT_NONE);
		m_pContinueList->setTouchEnabled(false);
		pContinuePanel->addChild(m_pContinueList);

		m_pUnSelList = CScrollTable::create(false, "WavePlayerName");
		m_pUnSelList->setSize(Size(200, 150));
		m_pUnSelList->setPosition(Point(0,-75));
		m_pUnSelList->SetFontSize(20);
		m_pUnSelList->SetFormat(TCT_STRING, 100, 0.5, 0.5,TCT_NONE);
		m_pUnSelList->setTouchEnabled(false);
		pUnselPanel->addChild(m_pUnSelList);

		Widget* pListBg = Helper::seekWidgetByName(m_pWidget,"RewardList");
		Button* pLeft = (Button*)Helper::seekWidgetByName(m_pWidget,"TurnLeft");
		Button* pRight = (Button*)Helper::seekWidgetByName(m_pWidget,"TurnRight");
		m_pReWardMenu = CScrollMenu::create(pListBg->getSize());
		m_pReWardMenu->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
		m_pReWardMenu->setLeftBtn(pLeft);
		m_pReWardMenu->setRightBtn(pRight);
		m_pReWardMenu->setInterval(30.0f);
		m_pReWardMenu->setButtonSize(Size(120,180));
		//m_pRadioBtn = m_pGiftMenu->getRadioMenu();
		pListBg->addChild(m_pReWardMenu);

		m_pMagicNum = Label::createWithBMFont("assets/common/font/timer.fnt",CCString::createWithFormat("%d",m_CountSeconds)->getCString());
		m_pMagicNum->setPosition(Point(360,240));
		m_pMainUI->addChild(m_pMagicNum);

		return true;
	} while (0);
	return false;
}

void CWaveEnd::onOpen()
{
	m_CountSeconds = 15;
	m_pMagicNum->setString(CCString::createWithFormat("%d",m_CountSeconds)->getCString());

	unschedule(schedule_selector(CWaveEnd::CountSeconds));
	schedule(schedule_selector(CWaveEnd::CountSeconds),1.0f,m_CountSeconds+1,1.0f);
	UpdateSelection();
	UpdateRewards();
}

void CWaveEnd::clickRetreat(Ref* pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		pk::C2GS_ReplySelectionToContinueCopy cmd = {0};
		cmd.Send(gNetSocket);
	}
}

void CWaveEnd::clickContinue(Ref* pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		pk::C2GS_ReplySelectionToContinueCopy cmd = {1};
		cmd.Send(gNetSocket);
	}
}

void CWaveEnd::CountSeconds(float dt)
{
	m_CountSeconds--;
	if(m_CountSeconds<0)
	{
		unschedule(schedule_selector(CWaveEnd::CountSeconds));
	}
	else
	{
		m_pMagicNum->setString(CCString::createWithFormat("%d",m_CountSeconds)->getCString());
	}
}

void CWaveEnd::UpdateSelection()
{
	m_pRetreatList->Clear();
	m_pContinueList->Clear();
	m_pUnSelList->Clear();


	for (unsigned int i=0; i<CTeamUI::s_teamInfo.member_list.size();++i)
	{
		if (CTeamUI::s_teamInfo.member_list[i].isContinue == 1)
		{
			//继续
			m_pContinueList->AddRow(CTeamUI::s_teamInfo.member_list[i].id,CTeamUI::GetTeamMember(CTeamUI::s_teamInfo.member_list[i].id)->name.c_str());
		}
		else if (CTeamUI::s_teamInfo.member_list[i].isContinue == 0)
		{
			//离开
			m_pRetreatList->AddRow(CTeamUI::s_teamInfo.member_list[i].id,CTeamUI::GetTeamMember(CTeamUI::s_teamInfo.member_list[i].id)->name.c_str());
		}
		else
		{
			//未选择
			m_pUnSelList->AddRow(CTeamUI::s_teamInfo.member_list[i].id,CTeamUI::GetTeamMember(CTeamUI::s_teamInfo.member_list[i].id)->name.c_str());
		}
	}
}

void CWaveEnd::UpdateRewards()
{
	m_pReWardMenu->Clear();
	std::map<int,pk::GS2C_GiveSelectionToContinueCopy>::iterator itr = s_waveRewards.begin();
	unsigned int i=0;
	for (; itr!=s_waveRewards.end(); ++itr,++i)
	{
		CheckBox* pBox = (CheckBox*)gCtrlAllocator->LoadCtrl("RewardTest");
		Text* title = (Text*)pBox->getChildByName("Title");
		Text* nameAndCnt = (Text*)pBox->getChildByName("NameAndCnt");
		title->setText(CCString::createWithFormat(GameString.get(1200)->value.c_str(),itr->second.steps)->getCString());
		if(itr->second.itemInfos.empty()) continue;
		ItemCfg* pCfg = ItemData.get(itr->second.itemInfos[0].itemDataID);
		if(!pCfg) continue;
		nameAndCnt->setText(CCString::createWithFormat("%s X %d",pCfg->name.c_str(),itr->second.itemInfos[0].cnt)->getCString());
		m_pReWardMenu->addMenu(pBox);
	}
	//下一波奖励
	CheckBox* pBox = (CheckBox*)gCtrlAllocator->LoadCtrl("RewardTest");
	Text* title = (Text*)pBox->getChildByName("Title");
	Text* nameAndCnt = (Text*)pBox->getChildByName("NameAndCnt");

	title->setText(GameString.get(1201)->value);
	m_pReWardMenu->addMenu(pBox);

	if (i>3)
	{
		m_pReWardMenu->scrollToMenu(i-2);
	}
}