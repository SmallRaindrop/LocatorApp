#include "RoleTitle.h"
#include "UI/ResMgr/CtrlAllocator.h"
#include "Hero.h"
#include "Net/NetDispatcher.h"
#include "Monster.h"
#include "UI/OneStroke.h"
#include "UI/OpenLock.h"
#include "BeyondMap.h"
#include "Chests.h"
#include "MessageCenter.h"

RoleTitle::RoleTitle(RoleFighter* pRole) : m_pRole(pRole), m_pName(nullptr),m_pHPBar(nullptr), 
	m_pTitle(nullptr), m_pGuildName(nullptr), m_pTeamLeader(nullptr), m_pVip(nullptr), 
	m_pTaskFlag(nullptr),m_pAutoFight(nullptr),m_pAutoMove(nullptr), m_pLock(nullptr)
{

}

RoleTitle::~RoleTitle()
{
}

RoleTitle* RoleTitle::createWithRole(RoleFighter* pRole)
{
	RoleTitle* ret = new RoleTitle(pRole);
	if ( ret && ret->init() )
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_RELEASE(ret);

	return NULL;
}

bool RoleTitle::init()
{
	if ( !m_pRole )
	{
		return false;
	}

	// 角色名称
	m_pName =  Text::create();
	m_pName->setFontSize(18);
	m_pName->setAnchorPoint(Point(0.5,0.5));
	m_pName->enableOutline(Color4B::BLACK,2);
	m_pName->setPositionY(48);

	m_pTitle = Text::create();
	m_pTitle->setFontSize(20);
	m_pTitle->setPositionY(24);

	m_pGuildName = Text::create();
	m_pGuildName->setFontSize(24);
	m_pGuildName->setPositionY(30);
	m_pGuildName->setColor(Color3B(228, 108, 10));

	addChild(m_pName);
	addChild(m_pTitle);
	addChild(m_pGuildName);

	// 复活面板
	m_revivePanel = gCtrlAllocator->LoadCtrl("Panel_Revive");
	m_revivePanel->setTouchEnabled(false);
	m_revivePanel->setScale(0.6f);
	m_progress_btn = (Button*)Helper::seekWidgetByName(m_revivePanel, "progress_btn");
	m_progress_btn->setAnchorPoint(Point::ANCHOR_MIDDLE);
	//progress_btn_->setButtonSpriteGray();
	m_progress_btn->addTouchEventListener(this, SEL_TouchEvent(&RoleTitle::clickReviveButton));
	m_progress_btn->setEnabled(false);
	m_timer_text = (Text*)Helper::seekWidgetByName(m_revivePanel, "timer_text");
	m_timer_text->setFontSize(76);

	ImageView* progressbar_img_ = (ImageView*)Helper::seekWidgetByName(m_revivePanel, "progress_img");
	progressbar_img_->setVisible(false);
	Point progressbar_img_point = progressbar_img_->getPosition();
	m_progressBar =  ProgressTimer::create(Sprite::create("assets/ui/revive/img_duiyoushijiaodaojishitiao.png"));
	m_progressBar->setAnchorPoint(Point::ANCHOR_MIDDLE);
	m_progressBar->setPosition(progressbar_img_point);
	m_revivePanel->addChild(m_progressBar);

	m_reviveTip = (ImageView*)Helper::seekWidgetByName(m_revivePanel, "tip_img");

	addChild(m_revivePanel);
	m_revivePanel->setPosition(Point(-60,30));
	m_revivePanel->setEnabled(false);

	m_restPoint = m_pRole->GetDeadVirtualRestPoint();
	m_deadRestTime = (int)m_pRole->GetDeadVirtualDeadRestTime();

	SetHPBar();

	return true;
}

void RoleTitle::SetRoleName(const string& str)
{
	m_pName->setText(str);
}

void RoleTitle::UpdateRoleNameCampColor()
{
	RoleCamp nCamp = RoleCamp(m_pRole->GetCamp());
	switch (nCamp)
	{
	case RoleCamp_None:
		break;
	case RoleCamp_Player:
		SetNameColor(CampColor_Player);
		break;
	case RoleCamp_Red:
		SetNameColor(CampColor_Red);
		break;
	case RoleCamp_Blue:
		SetNameColor(CampColor_Blue);
		break;
	default:
		break;
	}
}

void RoleTitle::SetHPBar()
{
	if ( m_pHPBar )
	{
		m_pHPBar->removeFromParent();
		m_pHPBar = NULL;
	}

	// 血条底
	ImageView* pImageBar = NULL;
	// 玩家显示绿条，与玩家同阵营的怪物显示黄条，其他怪物红条。
	if ( m_pRole->GetType() == mapObjectType_Monster )
	{
		if ( m_pRole->GetCamp() == RoleCamp_Player )
		{
			m_pHPBar = LoadingBar::create("assets/ui/MainUIFight/img_shouhuzhexuetiao.png");
			pImageBar = ImageView::create("assets/ui/MainUIFight/img_zhandouxuetiaodi.png");
		}
		else
		{
			m_pHPBar = LoadingBar::create("assets/ui/MainUIFight/img_zhandouxuetiaoguai.png");
			pImageBar = ImageView::create("assets/ui/MainUIFight/img_zhandouxuetiaodi2.png");
		}
	}
	else
	{
		m_pHPBar = LoadingBar::create("assets/ui/MainUIFight/img_zhandouxuetiaoren.png");
		pImageBar = ImageView::create("assets/ui/MainUIFight/img_zhandouxuetiaodi.png");
	}

	if ( m_pHPBar )
	{
		// 血条底
		pImageBar->setAnchorPoint(Point(0.5,0.5));
		pImageBar->setPosition(Point(m_pHPBar->getSize()/2));

		m_pHPBar->addChild(pImageBar);
		m_pHPBar->setPositionY(0);
		m_pHPBar->getChildren().back()->setLocalZOrder(-1);

		addChild(m_pHPBar);
	}
}

void RoleTitle::SetRoleTitle(const string& str)
{
	if ( !m_pTitle )
	{
		m_pTitle = Text::create();
		m_pTitle->setFontSize(20);
	}
	
	m_pTitle->setText(str);
}

void RoleTitle::SetNamePos(float x,float y)
{
	m_pName->setPosition(Point(x,y));
}

void RoleTitle::SetTitlePos(float x,float y)
{
	m_pTitle->setPosition(Point(x,y));
}

void RoleTitle::SetHPBarPos(float x,float y)
{
	m_pHPBar->setPosition(Point(x,y));
}

void RoleTitle::SetHPPercent(int nPercent)
{
	m_pHPBar->setPercent(nPercent);
}

void RoleTitle::SetShowHPBar(bool bShow)
{
	m_pHPBar->setVisible(bShow);
}

void RoleTitle::SetTeamLeader(bool leader)
{
	if ( leader )
	{
		if ( !m_pTeamLeader )
		{
			m_pTeamLeader = (ImageView*)gCtrlAllocator->LoadCtrl("flag_team");
			if (m_pTeamLeader)
			{
				m_pTeamLeader->setScale(0.6f);
				m_pTeamLeader->setPosition(Point(-m_pName->getSize().width / 2 - m_pTeamLeader->getSize().width * m_pTeamLeader->getScale() / 2,m_pName->getPositionY()));
				addChild(m_pTeamLeader);
			}
		}
	}
	else
	{
		if ( m_pTeamLeader )
		{
			m_pTeamLeader->removeFromParentAndCleanup(true);
			m_pTeamLeader = NULL;
		}
	}
}

void RoleTitle::SetVip(bool vip)
{
	if ( vip )
	{
		if ( !m_pVip )
		{
			m_pVip = (ImageView*)gCtrlAllocator->LoadCtrl("flag_vip");
			if (m_pVip)
			{
				m_pVip->setScale(0.6f);
				m_pVip->setPosition(Point(m_pName->getSize().width / 2 + m_pVip->getSize().width * m_pVip->getScale() / 2 + 5,m_pName->getPositionY()));
				addChild(m_pVip);
			}
		}
	}
	else
	{
		if ( m_pVip )
		{
			m_pVip->removeFromParentAndCleanup(true);
			m_pVip = NULL;
		}
	}
}

void RoleTitle::SetNPCTaskState(NPCTaskState state)
{
	const char* arrTaskState[4] = {"", "Image_Task_NCompleted", "Image_Task_Acceptable", "Image_Task_Completed"};

	// 移除老的
	removeChild(m_pTaskFlag);

	// 添加新的
	m_pTaskFlag = (ImageView*)gCtrlAllocator->LoadCtrl(arrTaskState[state]);
	if (m_pTaskFlag)
	{
		m_pTaskFlag->setScale(0.6f);
		m_pTaskFlag->setPositionY(60);
		addChild(m_pTaskFlag);
	}
}

void RoleTitle::SetNameColor(Color3B clr)
{
	m_pName->setColor(clr);
}

void RoleTitle::SetTitleColor(Color3B clr)
{
	m_pTitle->setColor(clr);
}

void RoleTitle::updateRevivePanel()
{ 
	if(GetRole()->GetType() != mapObjectType_Player)
		return;

	if (GetRole()->GetType() == mapObjectType_Player && gHero != GetRole() && GetRole()->HasStateFlag(RoleStateFlag_DeadVirtual))
	{
		int temp_int_ = gHero->GetDistanceTo(GetRole());
		bool temp_bool_ = gHero->IsEnemyTo(GetRole());
		LOGE("GetDistanceTo:%d",gHero->GetDistanceTo(GetRole()));
		LOGE("IsEnemyTo:%d",gHero->IsEnemyTo(GetRole()));
	}
	
	if( gHero->GetDistanceTo(GetRole()) > 2 || 
		gHero->IsEnemyTo(GetRole()) || 
		gHero == GetRole() || 
		GetRole()->GetType() != mapObjectType_Player || 
		!GetRole()->HasStateFlag(RoleStateFlag_DeadVirtual))
	{
		m_progress_btn->setEnabled(false);
		m_revivePanel->setEnabled(false);
		return;
	}

	m_progress_btn->setEnabled(true);
	m_revivePanel->setEnabled(true);

	if (m_pRole->GetDeadVirtualHelpNum()!=0)
	{
		if (m_pRole->GetDeadVirtualRestPoint()!=m_restPoint)
		{
			m_restPoint = m_pRole->GetDeadVirtualRestPoint();
			updateProgress();
		}
	}
	else
	{
		m_progressBar->setPercentage(0);
		if (((int)GetRole()->GetDeadVirtualDeadRestTime())!=m_deadRestTime)
		{
			m_deadRestTime = (int)m_pRole->GetDeadVirtualDeadRestTime();
			updateTimer();
		}
	}
}

void RoleTitle::clickReviveButton(Ref* pSender, TouchEventType type)
{
	Button* pTouchButton = (Button*)pSender;
	int64 roleId = m_pRole->GetId();
	pk::C2GS_HelpRecover_Req cmd;
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		m_reviveTip->setVisible(false);
		cmd.playerID = roleId;
		cmd.state = 0;
		cmd.Send(gNetSocket);
		break;
	case TOUCH_EVENT_MOVED:
		m_reviveTip->setVisible(false);
		break;
	case TOUCH_EVENT_ENDED:
		m_reviveTip->setVisible(true);
		cmd.playerID = roleId;
		cmd.state = 1;
		cmd.Send(gNetSocket);
		break;
	case TOUCH_EVENT_CANCELED:
		m_reviveTip->setVisible(true);
		cmd.playerID = roleId;
		cmd.state = 1;
		cmd.Send(gNetSocket);
		break;
	default:
		break;
	}
}

//  倒计时更新函数
void RoleTitle::updateTimer()
{
	if (m_deadRestTime>=0)   
	{  
		m_timer_text->setText(FORMAT_TO_STRING("%d",m_deadRestTime));
	}else
	{
		m_timer_text->setText("");
	} 
}

//  进度条更新函数
void RoleTitle::updateProgress()
{
	LOGE("GetDeadVirtualRestPoint:%f", m_pRole->GetDeadVirtualRestPoint());
	LOGE("m_restPoint:%f",m_restPoint);
	LOGE("m_progressBar->setPercentage:%f",(10000 - m_restPoint)/10000.0f);
	m_progressBar->setPercentage( (10000 - m_restPoint)/10000.0f*100 );//更新进度   
}

void RoleTitle::SetLock()
{
	CChests* pChests = dynamic_cast<CChests*>(GetRole());
	if(!pChests || !pChests->GetChestsData()) return;
	m_pLock = (Button*)gCtrlAllocator->LoadCtrl("TitleLock");
	if(m_pLock)
	{
		m_pLock->addTouchEventListener(this,toucheventselector(RoleTitle::clickLock));
		m_pLock->setPositionY(100+GetName()->getPositionY());
		addChild(m_pLock);
	}
}

void RoleTitle::clickLock(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		CChests* pChests = dynamic_cast<CChests*>(GetRole());
		if(!pChests) return;

		vector<int> lockType;
		StringSplitToInt(pChests->GetChestsData()->lock_type,",",lockType);
		if(lockType.size() != 2) return;

		std::function<void()> afterMoveFunc = nullptr;
		if (lockType[0] == 1)
		{
			//一笔画
			afterMoveFunc = [=]()
			{
				if(pChests->GetChestsStatus() == CChests::ChestsStatus_Opening)
				{
					MessagePrompt("It is being opened!");
					return;
				}

				COneStroke*		pOneStroke = (COneStroke*)gGameUILayer->open(IDU_OneStrokeUI);
				if(pOneStroke)
				{
					pOneStroke->InitStrokeInfo(lockType[1]);
					pOneStroke->SetItemBoxId(GetRole()->GetId());
					if(!pChests->GetDestroyLeftTime())//未激活不设时间
					{
						pOneStroke->SetLeftTime(pChests->GetDestroyLeftTime());
					}

					pk::C2GS_OPEN_TREAS_Req cmd;
					cmd.id = GetRole()->GetId();
					cmd.open_state = (int)CChests::ChestsStatus_Opening;
					cmd.Send(gNetSocket);
				}
			};
		}
		else if(lockType[0] == 2)
		{
			//开锁
			afterMoveFunc = [=]()
			{
				if(pChests->GetChestsStatus() == CChests::ChestsStatus_Opening)
				{
					MessagePrompt("It is being opened!");
					return;
				}

				COpenLock*		pOpenLockKey = (COpenLock*)gGameUILayer->open(IDU_OpenLock);
				if(pOpenLockKey)
				{
					pOpenLockKey->InitWithLockInfo(lockType[1]);
					pOpenLockKey->SetItemBoxId(GetRole()->GetId());
					if(!pChests->GetDestroyLeftTime())
					{
						pOpenLockKey->SetLeftTime(pChests->GetDestroyLeftTime());
					}

					pk::C2GS_OPEN_TREAS_Req cmd;
					cmd.id = GetRole()->GetId();
					cmd.open_state = (int)CChests::ChestsStatus_Opening;
					cmd.Send(gNetSocket);
				}
			};
		}
		CSuperMove::Start(gMap->getMapDataID(),pChests->GetCellX(),pChests->GetCellY(),afterMoveFunc,3);
	}
}
