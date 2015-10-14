#include "MainUIFight.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/Hero.h"
#include "Net/pk_map.h"
#include "Net/NetDispatcher.h"
#include "GameScene/TaskMgr.h"
#include "ChatMainUI.h"
#include "TeamUI.h"
#include "GamePrompt.h"
#include "GameScene/MessageCenter.h"
#include "copyMapUI.h"

static int test_time = 100;

BuffIcon::BuffIcon(RoleBuff* buff) : m_buffData(buff)
{
	m_img = nullptr;
	canStartBlink = true;
}

BuffIcon::~BuffIcon()
{
	m_img = nullptr;
	this->removeAllChildren();
}

BuffIcon* BuffIcon::create(RoleBuff* _buff)
{
	BuffIcon* img_ = new BuffIcon(_buff);

	//if (img_ && img_->init("assets/ui/_common/bg_shurukuang.png", _buff->GetDuration()))
	if (img_ && img_->init(_buff->GetIcon(), _buff->GetDuration()))
	{
		img_->setAnchorPoint(Point::ZERO);
		img_->setContentSize(Size(36,36));
		img_->autorelease();
		return img_;
	}
	CC_SAFE_DELETE(img_);
	return nullptr;
}

bool BuffIcon::init(const std::string& path,int tickTime)
{
	m_tickTime = tickTime/1000.0;
	bool bRet = true;
	do {
		if (!Widget::init()) {
			bRet = false;
			break;
		}

		m_img = ImageView::create(path);
		m_img->setAnchorPoint(Point::ZERO);
		this->addChild(m_img);

		schedule(schedule_selector(BuffIcon::update),1.0f);
	} while (0);
	return bRet;
}

void BuffIcon::update(float dt)
{
	m_tickTime-=dt;
	m_buffData->SetDuration(m_tickTime);

	if (m_tickTime <= 0.0)
	{
		m_img->stopAllActions();
		m_img->setVisible(false);
	}
	if(canStartBlink)
	{
		if (m_tickTime <= 5.0)
		{
			m_img->runAction(RepeatForever::create(Blink::create(1,1)));
			canStartBlink = false;
		}
	}
}

CMainUIFight::CMainUIFight() : MainUI(IDU_MainUIFight,JsonFile_MainUIFight),m_bNormalAtkPushed(false),m_fNormalAtkTimer(0.0f)
{
	m_panelLT = NULL;
	m_panelLB = NULL;
	m_panelRT = NULL;
	m_panelRB = NULL;

	m_HeadIcon = NULL;
	m_HeroLv = NULL;
	m_HeroHp = NULL;
	m_HeroMp = NULL;
	m_HeroHpBar = NULL;
	m_HeroMpBar = NULL;
	m_HeroHpSlot = NULL;
	m_HeroMpSlot = NULL;
	m_HeroName = NULL;
	m_bIconInit = false;
	m_buffListView = NULL;

	m_JoyStick = NULL;

	m_pHornWind = NULL;
	m_pMsgWind = NULL;
	m_pButtonChat = NULL;
	m_fChatBtnShowTime = 0.0f;
}

CMainUIFight::~CMainUIFight()
{

}

bool CMainUIFight::onInit()
{
	do 
	{
		BREAK_IF(!GameUIWithOutSideTouchEvent::onInit());
		//左上 左下 右上 右下 四个面板
		m_panelLT = (Layout*)Helper::seekWidgetByName(m_pWidget,"LeftTop");
		m_panelRT = (Layout*)Helper::seekWidgetByName(m_pWidget,"RightTop");
		m_panelLB = (Layout*)Helper::seekWidgetByName(m_pWidget,"LeftBottom");
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
		m_buffListView = (ListView*)Helper::seekWidgetByName(m_pWidget,"buffListView");
		BREAK_IF( !m_buffListView );
		//m_buffListView->setItemsMargin(0.1);

		//玩家头像
		m_HeadIcon = (ImageView*)Helper::seekWidgetByName(m_pWidget,"HeadBtn");
		m_HeroLv = (Text*)Helper::seekWidgetByName(m_pWidget,"Lv");
		m_HeroHp = (Text*)Helper::seekWidgetByName(m_pWidget,"HpValue");
		m_HeroMp = (Text*)Helper::seekWidgetByName(m_pWidget,"MpValue");
		m_HeroHpBar = (Layout*)Helper::seekWidgetByName(m_pWidget,"HpBarFrame");
		m_HeroMpBar = (Layout*)Helper::seekWidgetByName(m_pWidget,"MpBarFrame");
		m_HeroHpSlot = (ImageView*)Helper::seekWidgetByName(m_pWidget,"Img_hp");
		m_HeroMpSlot = (ImageView*)Helper::seekWidgetByName(m_pWidget,"Img_mp");
		m_HeroName = (Text*)Helper::seekWidgetByName(m_pWidget,"Name");
		BREAK_IF( !(m_HeroLv&&m_HeroHp&&m_HeroMp&&m_HeroHpBar&&m_HeroMpBar&&m_HeroHpSlot&&m_HeroMpSlot&&m_HeadIcon&&m_HeroName));
		m_HeroHpBar->setClippingEnabled(true);
		m_HeroMpBar->setClippingEnabled(true);
		m_HeadIcon->addTouchEventListener(this,toucheventselector(CMainUIFight::clickHead));

		CheckBox*	pCheckBox = (CheckBox*)(Helper::seekWidgetByName(m_pWidget,"PlayMode"));
		Text*	pMyScore = (Text*)(Helper::seekWidgetByName(m_pWidget,"Label_43"));
		Text*	pEnemyScore = (Text*)(Helper::seekWidgetByName(m_pWidget,"Label_43_0"));
		pCheckBox->setEnabled(false);
		pMyScore->setEnabled(false);
		pEnemyScore->setEnabled(false);

		//摇杆
		m_JoyStick = (ImageView*)Helper::seekWidgetByName(m_pWidget,"JoyStick");
		BREAK_IF( !m_JoyStick );
		m_JoyStick->setTouchEnabled(true);
		m_JoyStick->addTouchEventListener(this,toucheventselector(CMainUIFight::ClickJoyStick));

		//技能栏
		InitSkillBtns();

		//队伍
		for (int i=0; i<Team_Max_Num; ++i)
		{
			m_TeamHead[i].ui = Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("Team_%d",i)->getCString());
			m_TeamHead[i].ui->setEnabled(false);
			m_TeamHead[i].icon = (ImageView*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("TeamIcon_%d",i)->getCString());
			m_TeamHead[i].Txtleave = (Text*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("Leave_%d",i)->getCString());
			m_TeamHead[i].progress = ProgressTimer::create(Sprite::create(team_head_cd_path));
			BREAK_IF( !(m_TeamHead[i].ui&&m_TeamHead[i].icon&&m_TeamHead[i].progress&&m_TeamHead[i].Txtleave) );
			m_TeamHead[i].ui->addChild(m_TeamHead[i].progress);
			m_TeamHead[i].Txtleave->setLocalZOrder(100);
			m_TeamHead[i].Txtleave->setEnabled(false);
			Size size = m_TeamHead[i].ui->getContentSize();
			m_TeamHead[i].progress->setPosition(Point(size.width/2,size.height/2));
			m_TeamHead[i].progress->setReverseDirection(true);
		}

		//聊天
		m_pChatUI = (Layout*)Helper::seekWidgetByName(m_pWidget,"ChatLayout");
		m_pButtonChat =  (Button*)Helper::seekWidgetByName(m_pWidget,"ChatBtn");
		m_pButtonChat->addTouchEventListener(this,toucheventselector(CMainUIFight::clickChat));

		m_pMsgWind = CScrollMsgForMainUI::create();
		m_pMsgWind->setSize(m_pChatUI->getSize()); 	/*msgWind size 为300*i时，排版合适*/
		m_pMsgWind->setTouchEnabled(false);
		m_pMsgWind->setOpacity(0);
		m_pMsgWind->SetMaxMsgNum(1);
		ChatMainUI *pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
		if (pChatUI)
		{
			m_pMsgWind->SetTouchNameListenner(gGameUILayer->getUI(IDU_CHATMAINUI), (SEL_TouchNameLinkEvent)&ChatMainUI::clickNameLink4MainUI);
			m_pMsgWind->SetTouchItemListenner(gGameUILayer->getUI(IDU_CHATMAINUI), (SEL_TouchItemLinkEvent)&ChatMainUI::clickItemLink4MainUI);
		}
		m_pChatUI->addChild(m_pMsgWind);
		m_pChatUI->setVisible(false);

		//右上 副本
		m_pPvPSmallMap =  Helper::seekWidgetByName(m_panelRT,"PVP_Map");
		BREAK_IF(!(m_pPvPSmallMap));
		m_pPvPSmallMap->setEnabled(false);
		return true;
	} while (0);
	
	return false;
}

void CMainUIFight::onOpen()
{
	GameUIWithOutSideTouchEvent::onOpen();
	updateLv();
	updateHp();
	updateMp();
	updateSkillBtns();
	updateSkillCd();
	updateTeamHead();
	updateBuff();
	CCopyMapUI::OpenCopyMapUI();

	addChild(gPromptCenter->GetWidgetIcons());
	gJoyStick->removeFromParent();
	m_JoyStick->addChild(gJoyStick);
	gGameUILayer->open(IDU_TASKUI);
}

void CMainUIFight::onClose()
{
	GameUIWithOutSideTouchEvent::onClose();
	gGameUILayer->close(IDU_TASKUI);
	CCopyMapUI::CloseCopyMapUI();
}

void CMainUIFight::update(float dt)
{
	updateNormalAttack(dt);
	gJoyStick->update(dt);
	updateTeamHead();
	InitHeadIcon();
	m_pMsgWind->Update(dt);
}

void CMainUIFight::updateLv()
{
	m_HeroLv->setText(CCString::createWithFormat("%d",gHero->GetLevel())->getCString());
}

void CMainUIFight::updateHp()
{
	__int64 nHp,nHpMax;
	nHp = gHero->GetHP();
	nHpMax = gHero->GetHPMax();

	m_HeroHp->setText(CCString::createWithFormat("%lld",nHp)->getCString());

	float percent1 = (float)nHp/nHpMax;
	m_HeroHpBar->setSize(Size(m_HeroHpSlot->getSize().width*percent1,m_HeroHpSlot->getSize().height));
}

void CMainUIFight::updateMp()
{
	int nMp,nMpMax;
	nMp = gHero->GetMP();
	nMpMax = gHero->GetMPMax();

	m_HeroMp->setText(CCString::createWithFormat("%d",nMp)->getCString());

	float percent2 = (float)nMp/nMpMax;
	m_HeroMpBar->setSize(Size(m_HeroMpSlot->getSize().width*percent2,m_HeroMpSlot->getSize().height));
}

void CMainUIFight::updateMapName(const std::string& name)
{

}

void CMainUIFight::updateBuff()
{
	m_buffListView->removeAllItems();								// 初始化清空buff列表容器
	RoleBuffManager& buffManager_ = gHero->GetBuffManager();
	int buffNums_ = buffManager_.Count(); 					 	    // buff的数量
	auto buffList_ = buffManager_.GetBuffList();

	for (int i = buffNums_-1;i>=0 ;i--)
	{
		auto buff_ = buffList_[i];
		if ( i < (buffNums_-4) )
		{
			break;
		}

		BuffIcon* buffIcon_ =  BuffIcon::create(buff_);
		m_buffListView->pushBackCustomItem(buffIcon_);
	}
}

void CMainUIFight::InitHeadIcon()
{
	if (!m_bIconInit && gHero->GetCareer() != 0)
	{
		m_HeadIcon->loadTexture(gHero->getHeadIcon());
		m_HeroName->setText(gHero->GetRoleName());
		m_bIconInit = true;
	}
}

bool CMainUIFight::InitSkillBtns()
{
	m_NormalAtk.btn = (Button*)Helper::seekWidgetByName(m_pWidget,"NormalAtk");
	m_NormalAtk.btn->setTag(Normal_Attack_ID);
	m_NormalAtk.btn->addTouchEventListener(this,toucheventselector(CMainUIFight::ClickSkill));
	Size size = m_NormalAtk.btn->getSize();
	m_NormalAtk.cd = CdCtrol::create(skill_cd_path);
	m_NormalAtk.cd->setSize(size-Size(10,10));
	m_NormalAtk.cd->setPosition(Point(size.width/2,size.height/2));
	m_NormalAtk.btn->addChild(m_NormalAtk.cd);

	for (int i=0; i<Skill_Max_Num; ++i)
	{
		m_SkillBtns[i].btn = (Button*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("Skill_%d",i)->getCString());
		m_SkillBtns[i].lock = (ImageView*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("LockImg_%d",i)->getCString());
		m_SkillBtns[i].desc = (Text*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("UnlockDesc_%d",i)->getCString());
		m_SkillBtns[i].icon = (ImageView*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("Icon_%d",i)->getCString());

		m_SkillBtns[i].btn->addTouchEventListener(this,toucheventselector(CMainUIFight::ClickSkill));

		Size size = m_SkillBtns[i].icon->getSize();
		m_SkillBtns[i].cd = CdCtrol::create(skill_cd_path);
		m_SkillBtns[i].cd->setPosition(Point(size.width/2,size.height/2));
		m_SkillBtns[i].cd->setSize(size);
		m_SkillBtns[i].icon->addChild(m_SkillBtns[i].cd);

		m_SkillBtns[i].enable = false;
	}

	return true;
}

void CMainUIFight::updateSkillBtns()
{
	int skillIdx = 0;
	for ( int i = 0;i<gHero->GetSkillManager().Count();++i )
	{
		CSkill* pSkill = gHero->GetSkillManager().IndexBy(i);
		if ( pSkill )
		{
			if ( pSkill->IsNormalAttack() )
			{
				m_NormalAtk.skill = pSkill->GetData();
				m_NormalAtk.btn->setTag(pSkill->GetData()->id);
			}
			else if( !pSkill->IsPassive() )
			{
				m_SkillBtns[skillIdx].skill = pSkill->GetData();
				m_SkillBtns[skillIdx].btn->setTag(pSkill->GetData()->id);
				m_SkillBtns[skillIdx].desc->setEnabled(false);
				m_SkillBtns[skillIdx].lock->setEnabled(false);
				m_SkillBtns[skillIdx].enable = false;

				m_SkillBtns[skillIdx].icon->loadTexture(m_SkillBtns[skillIdx].skill->icon);
				//m_SkillBtns[skillIdx].desc->setText(CCString::createWithFormat("%d Lv open",m_SkillBtns[i].skill->studylevel)->getCString());
				if ( ++skillIdx >= Skill_Max_Num )
				{
					return;
				}
			}		
		}
	}
}

void CMainUIFight::updateSkillCd()
{
	if ( m_NormalAtk.skill )
	{
		CSkill* pSkill = gHero->GetSkillManager().Get(m_NormalAtk.skill->id);
		if (pSkill)
		{
			int nCdTotalTime = 0;
			if(pSkill->GetCDType() == CSkill::CdType_Skill)
			{
				nCdTotalTime = pSkill->GetData()->cdtime;
			}
			else
			{
				nCdTotalTime = pSkill->GetData()->globecooldown;
			}
			m_NormalAtk.cd->SetCd(pSkill->GetCDTime(),nCdTotalTime);
		}
	}

	for (int i=0; i<Skill_Max_Num; ++i)
	{
		if ( m_SkillBtns[i].skill )
		{
			CSkill* pSkill = gHero->GetSkillManager().Get(m_SkillBtns[i].skill->id);
			if(pSkill)
			{
				int nCdTotalTime = 0;
				if(pSkill->GetCDType() == CSkill::CdType_Skill)
				{
					nCdTotalTime = pSkill->GetData()->cdtime;
				}
				else
				{
					nCdTotalTime = pSkill->GetData()->globecooldown;
				}
				m_SkillBtns[i].cd->SetCd(pSkill->GetCDTime(),nCdTotalTime);
			}
		}
	}
}

void CMainUIFight::updateTeamHead()
{
	for (unsigned int i=0;i<Team_Max_Num; ++i)
	{
		m_TeamHead[i].ui->setEnabled(false);
	}
	for (unsigned int i=0,j=0; i<Team_Max_Num&&j<CTeamUI::s_teamInfo.member_list.size(); ++i,++j)
	{
		//跳过自己
		if (CTeamUI::s_teamInfo.member_list[j].id == gHero->GetId())
		{
			j++;
			if(j>=CTeamUI::s_teamInfo.member_list.size()) return;
		}
		//离线的
		if (CTeamUI::s_teamInfo.member_list[j].online == 1)
		{
			m_TeamHead[i].Txtleave->setEnabled(true);
			continue;
		}
		//死亡的
		if (CTeamUI::s_teamInfo.member_list[j].hp == 0)
		{
			m_TeamHead[i].icon->loadTexture(GetTeamIconDead(CTeamUI::s_teamInfo.member_list[j].career));
			m_TeamHead[i].progress->setPercentage(0);
			continue;
		}
		//活着的
		if(CTeamUI::s_teamInfo.member_list[j].maxhp<=0) continue;
		m_TeamHead[i].ui->setEnabled(true);
		float percent = CTeamUI::s_teamInfo.member_list[j].hp*100.0/CTeamUI::s_teamInfo.member_list[j].maxhp;
		m_TeamHead[i].progress->setPercentage(percent);
		m_TeamHead[i].icon->loadTexture(GetTeamIconAlive(CTeamUI::s_teamInfo.member_list[j].career));
		m_TeamHead[i].Txtleave->setEnabled(false);
	}
}

void CMainUIFight::ClickQuit(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		gHero->LeaveCopy();
	}
}

void CMainUIFight::updateNormalAttack(float dt)
{
	static const float NormalAttackInterval = 0.3f;
	if ( !m_bNormalAtkPushed )
	{
		return ;
	}

	if ( m_fNormalAtkTimer > NormalAttackInterval )
	{
		int skillId = m_NormalAtk.btn->getTag();
		gHero->Attack(skillId);
		m_fNormalAtkTimer = 0.0f;
	}
	else
	{
		m_fNormalAtkTimer += dt;
	}
}

void CMainUIFight::ClickSkill(Ref *pSender, TouchEventType type)
{
	if(!gHero->CanUseSkill())
		return;

	Button* pBtn = dynamic_cast<Button*>(pSender);
	if ( !pBtn )
	{
		return ;
	}

	if ( TOUCH_EVENT_BEGAN == type )
	{
		int skillId = pBtn->getTag();
		gHero->Attack(skillId);

		if ( pBtn == m_NormalAtk.btn )
		{
			m_bNormalAtkPushed = true;
			m_fNormalAtkTimer = 0.0f;
		}
	}
	else if ( TOUCH_EVENT_ENDED == type )
	{
		if ( pBtn == m_NormalAtk.btn )
		{
			m_bNormalAtkPushed = false;
			m_fNormalAtkTimer = 0.0f;
		}
	}
	else if ( TOUCH_EVENT_CANCELED == type )
	{
		if ( pBtn == m_NormalAtk.btn )
		{
			m_bNormalAtkPushed = false;
			m_fNormalAtkTimer = 0.0f;
		}
	}
}

void CMainUIFight::ClickJoyStick(Ref *pSender, TouchEventType type)
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

void CMainUIFight::clickHead(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		gGameUILayer->open(IDU_FightPause);
	}
}

void CMainUIFight::ContinueFight(bool yesOrNo)
{
	pk::C2GS_ReplySelectionToContinueCopy cmd;
	cmd.isContinue = yesOrNo?1:0;
	cmd.Send(gNetSocket);
	if(!yesOrNo)
	{
		gHero->LeaveCopy();
	}
}

void CMainUIFight::updateChatMsg(pk::GS2C_Chat *value)
{
	ChatMainUI* pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
	if (pChatUI->IsCurChannelMsg(value))
	{
		m_pMsgWind->PushMsg(value,value->senderId==gHero->GetId());
		m_pMsgWind->Flush(true);
	}
}

void CMainUIFight::clickChat(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		GameUI* pUI = gGameUILayer->open(IDU_CHATMAINUI);
		if(pUI) pUI->setPosition(Point::ZERO);
	}
}