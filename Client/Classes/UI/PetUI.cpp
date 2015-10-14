#include "ReviveUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "GameScene/GameUILayer.h"
#include "Net/NetDispatcher.h"
#include "Common/DataPool.h"
#include "GameScene/MessageCenter.h"
#include "MessageBoxUI.h"
#include "GameScene/MessageCenter.h"
#include "GameScene/Hero.h"

CReviveUI::CReviveUI()
	:GameUI(IDU_ReviveUI,JsonFile_ReviveUI)
{

}

CReviveUI::~CReviveUI()
{

}

bool CReviveUI::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());

		Button *pGiveupBtn = (Button*)Helper::seekWidgetByName(m_pWidget, "giveup_btn");
		BREAK_IF(pGiveupBtn==NULL);
		pGiveupBtn->setButtonSpriteGray();
		pGiveupBtn->addTouchEventListener(this, SEL_TouchEvent(&CReviveUI::clickGiveupButton));

		Button *pReviveBtn = (Button*)Helper::seekWidgetByName(m_pWidget, "revive_btn");
		BREAK_IF(pReviveBtn==NULL);
		pReviveBtn->setButtonSpriteGray();
		pReviveBtn->addTouchEventListener(this, SEL_TouchEvent(&CReviveUI::clickReviveButton));

		m_title_text = (Text*)Helper::seekWidgetByName(m_pWidget, "title_text");
		m_timer_text = (Text*)Helper::seekWidgetByName(m_pWidget, "timer_text");
		
		ImageView* progressbar_img_ = (ImageView*)Helper::seekWidgetByName(m_pWidget, "progressbar_img");
		progressbar_img_->setVisible(false);
		Point progressbar_img_point = progressbar_img_->getPosition();
		m_progressBar =  ProgressTimer::create(Sprite::create("assets/ui/revive/img_ziwoshijiaodaojishijindu.png"));
		m_progressBar->setAnchorPoint(Point::ANCHOR_MIDDLE);
		m_progressBar->setPosition(progressbar_img_point);
		this->addChild(m_progressBar);

		return true;
	} while (0);

	return false;
}

void CReviveUI::onOpen()
{
	m_restPoint = gHero->GetDeadVirtualRestPoint();
	m_deadRestTime = (int)gHero->GetDeadVirtualDeadRestTime();
}

void CReviveUI::onClose()
{

}

void CReviveUI::update(float dt)
{
	if (gHero->GetDeadVirtualHelpNum()!=0)
	{
		if (gHero->GetDeadVirtualRestPoint()!=m_restPoint)
		{
			m_restPoint = gHero->GetDeadVirtualRestPoint();
			updateProgress();
		}
	}
	else
	{
		m_progressBar->setPercentage(0);
		if (((int)gHero->GetDeadVirtualDeadRestTime())!=m_deadRestTime)
		{
			m_deadRestTime = (int)gHero->GetDeadVirtualDeadRestTime();
			updateTimer();
		}
	}
}

//  倒计时更新函数
void CReviveUI::updateTimer()
{
	if (m_deadRestTime>0)   
	{  
		m_timer_text->setText(FORMAT_TO_STRING("%d",m_deadRestTime));
		m_title_text->setText(STR_REVIVE_DEADVIRTUAL);
	}else
	{
		m_timer_text->setText("");
		m_title_text->setText(STR_REVIVE_DEAD);
	}
}

// 假死状态结束
void CReviveUI::deadTimeOut()
{
	m_timer_text->setText("");
	m_title_text->setText(STR_REVIVE_DEAD);
}

//  进度条更新函数
void CReviveUI::updateProgress()
{
	m_progressBar->setPercentage( (10000 - m_restPoint)/10000.0f*100 );//更新进度   
}

void CReviveUI::clickGiveupButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
		pk::C2GS_PlayerLeaveCopyMap cmd;
		cmd.Send(gNetSocket);
	}
}

void CReviveUI::clickReviveButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		string tip_str_;
		m_need_gold = 20;
		if (gHero->GetData()->GetRecoverCount()>=MAX_FREE_REVIVE_COUNT)	// 免费次数用尽
		{
			tip_str_ = FORMAT_TO_STRING(STR_Text_Tip_gold_revive_tip,m_need_gold);
		}else
		{
			tip_str_ = FORMAT_TO_STRING(STR_Text_Tip_free_revive_tip,MAX_FREE_REVIVE_COUNT - gHero->GetData()->GetRecoverCount());
		}

		CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,tip_str_.c_str(),[&](bool type){
			if(type)
			{
				if (gHero->GetMoney() < m_need_gold)
				{
					gMessageCenter->SystemMessage(SystemMessage_Prompt,STR_Text_Tip_gold_not_enough);
					return;
				}
				// 点击了复活按钮
				pk::C2GS_RecoverLife_Req cmd;
				vector<int> ruleIdVec_;
				StringSplitToInt(gMap->getMapData()->recover_life_ids,";",ruleIdVec_);
				cmd.recoverRuleId = ruleIdVec_[0];
				cmd.Send(gNetSocket);
			}
		},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
			this,NULL,CMessageBoxUI::Scene_Game);
	}
}
